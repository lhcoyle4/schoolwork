/*************************************************************
**************************************************************
    ECE 300 – Spring 2014

    Louis Coyle
    Homework #: 06

    Copyright DigiPen (USA) Corporation
    All Rights Reserved
**************************************************************
*************************************************************/


#include "WirelessXBee.h"
#include "HAL.h"
#include "Timer.h"

#define COMMAND_MODE_ENTER_STRING "+++"
#define COMMAND_MODE_EXIT_STRING  "AT CN\r"

bool MessageDone( const char RecByte, const char * RespDelimit);
void ATCmdModeEnter( void );
void ATCmdModeExit( void );

bool XBee_Initialize( void )
{
  
  if(!GPIO_Pin_Initialize() || !UART_Wireless_Initialize(9600))
    return false;
  
  /*
  Wireless_ResetPin_Set(0); //Set reset pin to 0
  BlockingDelay(1);//Wait at least one millisecond
  Wireless_ResetPin_Set(1);//Set reset pin to 1
  BlockingDelay(1);//Wait another millisecond
  */
  return true;
}

void XBee_SendMsg( const char * Msg )
{
  UART_Wireless_Send( Msg, strlen(Msg) );
}

// make a XBee_APIPacket function to wrap around the ATCommand function

void XBee_APIPacket(const char * Command, const char * CmdArg, char * RespDest, const char * RespDelimit)
{
  char startDelimit = 0x7E;
  // to calculate checksum, add all bytes besides frame delims and length
  // and subtract the lowest 8 bits of the sum from 0xFF
  char checksum = 0xFF - (Command + CmdArg);
  // Length [Bytes] = API Identifier + Frame ID + AT Command + Parameter Value
  short length = 0;
  // use the API ID for sending AT Commands
  short API_ID = 0x08;
  // Frame ID is to allow the response to be read, will be set depending on the AT Command
  short Frame_ID = 0x00;

}

// modify AT command to send actual hex value, not ascii characters representing the hex
void XBee_ATCommand( const char * Command, const char * CmdArg, char * RespDest, const char *RespDelimit )
{
  char XBeeMsg [32] = {0};
  int i = 0;
  
  //we need a delay between AT commands
  BlockingDelay(1000);
  
  if( CmdArg )
	  sprintf( XBeeMsg, "AT%s%s\r",Command, CmdArg);
  else
	  sprintf( XBeeMsg, "AT%s\r",Command);
  
  RespDest[i] = 0;
  
  ATCmdModeEnter();
  
  UART_Wireless_Send(XBeeMsg, strlen(XBeeMsg));
  
  UART_Wireless_Receive(&RespDest[i], 1);
  
  while( !MessageDone(RespDest[i], RespDelimit) )
  {
    i++;
    UART_Wireless_Receive(&RespDest[i], 1);
  }
	
	RespDest[i] = 0;
  
	if( strcmp(Command, "DN") != 0 )
		ATCmdModeExit();
  
}

void ATCmdModeEnter( void )
{
  char CmdRecTemp = 0;
  int i;
  
  //send command +++ to enter command mode///////////
  UART_Wireless_Send( COMMAND_MODE_ENTER_STRING, strlen(COMMAND_MODE_ENTER_STRING) );
  ///////////////////////////////////////////////////
  
  UART_Wireless_Receive(&CmdRecTemp, 1);
  
  while( !MessageDone(CmdRecTemp, "OK") )
  {
    i++;
    UART_Wireless_Receive(&CmdRecTemp, 1);
  }
}

void ATCmdModeExit( void )
{
  char CmdRecTemp = 0;
  int i;
  
  //send command +++ to enter command mode///////////
  UART_Wireless_Send( COMMAND_MODE_EXIT_STRING, strlen(COMMAND_MODE_EXIT_STRING) );
  ///////////////////////////////////////////////////
  
  UART_Wireless_Receive(&CmdRecTemp, 1);
  
  while( !MessageDone(CmdRecTemp, "OK") )
  {
    i++;
    UART_Wireless_Receive(&CmdRecTemp, 1);
  }
}

bool MessageDone( const char RecByte, const char * RespDelimit)
{
  static char HistBuf[5] = {0};
  char * SubStr = 0;
    
  if( RecByte == 0 )
    return false;
  
  HistBuf[0] = HistBuf[1];
  HistBuf[1] = HistBuf[2];
  HistBuf[2] = RecByte;
  
  SubStr = strstr(HistBuf, RespDelimit);
  
  if( SubStr != 0 )
  {
    HistBuf[2] = 0;
    HistBuf[1] = 0;
    HistBuf[0] = 0;
    return true;
  }
  else
    return false;
}
