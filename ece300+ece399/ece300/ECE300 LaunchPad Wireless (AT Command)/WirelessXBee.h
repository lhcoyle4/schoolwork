#ifndef WIRELESS_XBEE_H
#define WIRELESS_XBEE_H
#include "Common.h"
bool XBee_Initialize( void );
void XBee_ATCommand(const char * Command, const char * CmdArg, char * RespDest, const char *RespDelimit);
void XBee_SendMsg( const char * Msg );
#endif
