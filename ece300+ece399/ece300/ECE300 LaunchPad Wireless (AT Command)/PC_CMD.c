#include "PC_CMD.h"
#include "Parse.h"
#include "HAL.h"

CommandCode CMDCodes[COMMAND_NUM] = {0};

void PC_CMDInit( void )
{
  UART_PC_Initialize(9600);
  
  strcpy(CMDCodes[0].String, "NODE SEARCH");
  CMDCodes[0].CMD_Code = NODE_SEARCH;
  strcpy(CMDCodes[1].String, "SEND");
  CMDCodes[1].CMD_Code = SEND_MESSAGE;
  strcpy(CMDCodes[2].String, "MY ADDRESS");
  CMDCodes[2].CMD_Code = MY_ADDRESS;
  strcpy(CMDCodes[3].String, "SET NAME");
  CMDCodes[3].CMD_Code = SET_MY_NAME;
  strcpy(CMDCodes[4].String, "GET NAME");
  CMDCodes[4].CMD_Code = GET_MY_NAME;

  return;
}


COMMAND PC_GetCommand( char * Destination, unsigned int DestSize, unsigned int * NumDataWritten )
{
  unsigned int i = 0;
  COMMAND CMD_Code = ERROR;
  
  *NumDataWritten = 0;
  
  for(i = 0; i < DestSize; i++ )
  {
    UART_PC_Receive( &Destination[i], 1 );
		
    if( Destination[i] == '\r' )
    {
      *NumDataWritten = i+1;
      CMD_Code = DataParse(Destination, *NumDataWritten);
      break;
    }
  }
  
  return CMD_Code;
}

void PC_SendMsg( const char * Source, unsigned int Size )
{
  UART_PC_Send(Source, Size);
}
