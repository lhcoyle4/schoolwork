#include "UART.h"
#include "driverlib/uart.h"

bool UART_PC_Initialize( unsigned int Baud )
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, (GPIO_PIN_0 | GPIO_PIN_1));
	UARTConfigSetExpClk(UART0_BASE, MAP_SysCtlClockGet(), 9600,
						(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	UARTFIFOEnable(UART0_BASE);
	UARTEnable(UART0_BASE);
    return true;
}

void UART_PC_Receive( char* Destination, unsigned int Size )
{
	int i;
	for( i = 0; i < Size; i++)
	{
		while( !UARTCharsAvail(UART0_BASE) )
		{ }
		Destination[i] = UARTCharGet( UART0_BASE );
	}
}


void UART_PC_Send( const char * Source, unsigned int Size )
{
	int i;
	for( i = 0; i < Size; i++)
	{
		while( !UARTSpaceAvail(UART0_BASE) )
		{ }
		UARTCharPut( UART0_BASE, Source[i]);
	}
}



bool UART_Wireless_Initialize( unsigned int Baud )
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
	GPIOPinConfigure(GPIO_PC6_U3RX);
	GPIOPinConfigure(GPIO_PC7_U3TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE, (GPIO_PIN_6 | GPIO_PIN_7)); //rx / tx
	UARTConfigSetExpClk(UART3_BASE, MAP_SysCtlClockGet(), 9600,
						(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	UARTFIFOEnable(UART3_BASE);
	UARTEnable(UART3_BASE);

	return true;
}

void UART_Wireless_Receive( char* Destination, unsigned int Size )
{
	int i;
	for( i = 0; i < Size; i++)
	{
		while( !UARTCharsAvail(UART3_BASE) )
		{ }
		Destination[i] = UARTCharGet( UART3_BASE );
	}
}

void UART_Wireless_Send( const char * Source, unsigned int Size )
{
	int i;
	for( i = 0; i < Size; i++)
	{
		while( !UARTSpaceAvail(UART3_BASE) )
		{ }
		UARTCharPut( UART3_BASE, Source[i]);
	}
}

