/*************************************************************
**************************************************************
    ECE 300 – Spring 2014

    Louis Coyle
    Homework #: 04

    Copyright DigiPen (USA) Corporation
    All Rights Reserved
**************************************************************
*************************************************************/


// needed for driverlib rom stuff
#define TARGET_IS_BLIZZARD_RA1 1

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "utils/uartstdio.h"

int main(void) {

    uint8_t buttonstate1 = 0;
    //uint8_t buttonstate2 = 0;
    uint8_t prevbuttonstate1 = 1;
    //uint8_t prevbuttonstate2 = 1;
    uint32_t ADC0Value[1];
    double distance;
    double adcdouble;

    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL |
                       SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //enable port for user switches
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // unlock GPIO commit control register
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    //set port for user switches to input with pullup
    MAP_GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    MAP_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //initialize the buttonstates into their variables
    buttonstate1 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
    //buttonstate2 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);

    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

    MAP_UARTConfigSetExpClk(UART0_BASE, MAP_SysCtlClockGet(), 9600,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    MAP_UARTEnable(UART0_BASE);

    MAP_UARTFIFOEnable(UART0_BASE);

    UARTStdioConfig(0, 9600, MAP_SysCtlClockGet());

    //enable ADC0 peripheral
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    //enable port for ADC0
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //configure the pin as ADC
    MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    //enable sample sequence 3 with a processor signal trigger
    MAP_ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    //configure channel 0 in single-ended-input mode, enable interrupt flag
    //configure for a single conversion on sequence 3
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    //enable the configured sample sequence
    MAP_ADCSequenceEnable(ADC0_BASE, 3);

    //clear the interrupt flag before beginning sampling
    MAP_ADCIntClear(ADC0_BASE, 3);

    while (1) {
        // update the buttonstates variables
        buttonstate1 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        //buttonstate2 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);

        //on button press, use the reading for calibration
        if (!buttonstate1 && (buttonstate1 != prevbuttonstate1))
        {

        }

        MAP_ADCProcessorTrigger(ADC0_BASE, 3);

        //wait for the conversion to be completed.
        while (!MAP_ADCIntStatus(ADC0_BASE, 3, false)) {
        } // end while

        //clear the interrupt
        MAP_ADCIntClear(ADC0_BASE, 3);

        //read the value
        MAP_ADCSequenceDataGet(ADC0_BASE, 3, ADC0Value);

        adcdouble = (double)ADC0Value[0];

        //calculate the distance from the ADC code
        //distance = .00003*(pow(adcdouble, 2)) - 0.1209*adcdouble + 125.55;

        //display the value
        UARTprintf("%f\n", adcdouble);

        //delay about half a second
        MAP_SysCtlDelay(MAP_SysCtlClockGet() / 6);

        //save the most recent buttonstate
        prevbuttonstate1 = buttonstate1;
        //prevbuttonstate2 = buttonstate2;
    } // end while

    return 0;
} //end main
