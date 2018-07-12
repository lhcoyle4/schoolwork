#ifndef UART_H
#define UART_H
#include "Common.h"

bool UART_PC_Initialize( unsigned int Baud );
void UART_PC_Receive( char* Destination, unsigned int Size );
void UART_PC_Send( const char * Source, unsigned int Size );
bool UART_Wireless_Initialize( unsigned int Baud );
void UART_Wireless_Receive( char* Destination, unsigned int Size );
void UART_Wireless_Send( const char * Source, unsigned int Size );

#endif
