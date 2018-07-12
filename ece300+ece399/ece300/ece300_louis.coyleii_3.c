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

const char *mystr = "Hello, World!\r\n";

int main(void) {

	char* i, c;
	uint8_t buttonstate1 = 0;
	uint8_t buttonstate2 = 0;
	uint8_t prevbuttonstate1 = 1;
	uint8_t prevbuttonstate2 = 1;

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
	ROM_GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
	ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0,
						 GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	//initialize the buttonstates into their variables
	buttonstate1 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
	buttonstate2 = MAP_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);

	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

	MAP_UARTConfigSetExpClk(UART0_BASE, MAP_SysCtlClockGet(), 9600,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	MAP_UARTEnable(UART0_BASE);

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
