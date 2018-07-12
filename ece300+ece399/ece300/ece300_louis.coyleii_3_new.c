// needed for driverlib rom stuff
#define TARGET_IS_BLIZZARD_RA1 1

#include <stdint.h>
#include <stdbool.h>
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

#define CONFIGPORTS() \
	do { \
	MAP_GPIOPinConfigure(GPIO_PB0_U1RX); \
	MAP_GPIOPinConfigure(GPIO_PB1_U1TX); \
	} while (0)

const char *mystr = "Hello, World!\r\n";

// copied from example file in tivaware folder
void UARTIntHandler(void) {
    uint32_t ui32Status;

    // Get the interrupt status.
    ui32Status = ROM_UARTIntStatus(UART1_BASE, true);

    // Clear the asserted interrupts.
    ROM_UARTIntClear(UART1_BASE, ui32Status);

    // Loop while there are characters in the receive FIFO.
    while (ROM_UARTCharsAvail(UART1_BASE)) {
        // Read the next character from the UART and write it back to the UART.
        ROM_UARTCharPutNonBlocking(UART1_BASE,
        		ROM_UARTCharGetNonBlocking(UART1_BASE));
    }
}

int main(void) {

    char* i, c;
    uint8_t buttonstate1 = 0;
    uint8_t buttonstate2 = 0;
    uint8_t prevbuttonstate1 = 1;
    uint8_t prevbuttonstate2 = 1;

    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL |
                       SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //MAP_GPIOPinConfigure(GPIO_PB0_U1RX);
    //MAP_GPIOPinConfigure(GPIO_PB1_U1TX);
    CONFIGPORTS();

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
    buttonstate2 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);

    MAP_IntMasterEnable();

    MAP_GPIOPinTypeUART(GPIO_PORTB_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

    MAP_UARTConfigSetExpClk(UART1_BASE, MAP_SysCtlClockGet(), 9600,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    MAP_UARTConfigSetExpClk(UART0_BASE, MAP_SysCtlClockGet(), 9600,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    MAP_UARTEnable(UART1_BASE);

    MAP_UARTEnable(UART0_BASE);

    MAP_UARTFIFOEnable(UART1_BASE);

    MAP_UARTFIFOEnable(UART0_BASE);

    while (1) {
        i = (char *)mystr;
        while ( ((c = *i) != '\0')) {
            // update the buttonstates variables
            buttonstate1 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
            buttonstate2 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
            //only output a char when the buttonstate changed from unpressed to pressed
            if((!buttonstate1 && (buttonstate1 != prevbuttonstate1)) ||
               (!buttonstate2 && (buttonstate2 != prevbuttonstate2)))
            {
                MAP_UARTCharPut(UART1_BASE, c);
                MAP_UARTCharPut(UART0_BASE, c);
                *i++;
            }

            //account for weirdness due to speed of clock/button bouncing with a delay
            MAP_SysCtlDelay(2000000);

            //save the most recent buttonstate
            prevbuttonstate1 = buttonstate1;
            prevbuttonstate2 = buttonstate2;
        } // end while
    } // end while

    return 0;
} //end main
