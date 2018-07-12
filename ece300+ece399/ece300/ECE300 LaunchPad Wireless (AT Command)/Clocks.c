#include "Clocks.h"
#define WAIT_ITERATIONS 100000
// this file is not used on the Mbed
static volatile unsigned int i = 0;

void SystemClocksInitialize( void )
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	for(i = 0; i < WAIT_ITERATIONS; i++)
			;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	for(i = 0; i < WAIT_ITERATIONS; i++)
		;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	for(i = 0; i < WAIT_ITERATIONS; i++)
			;

	return;
}
