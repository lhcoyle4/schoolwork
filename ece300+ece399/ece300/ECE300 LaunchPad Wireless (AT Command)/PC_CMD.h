#ifndef PC_CMD_H
#define PC_CMD_H
#include "Common.h"

typedef enum {NODE_SEARCH, SEND_MESSAGE, MY_ADDRESS, SET_MY_NAME, GET_MY_NAME, ERROR}COMMAND;


#define COMMAND_NUM       5
#define COMMAND_STR_SIZE  11

typedef struct
{
  char String[COMMAND_STR_SIZE+1];
  COMMAND CMD_Code;
} CommandCode;

void PC_CMDInit( void );
COMMAND PC_GetCommand( char * Destination, unsigned int DestSize, unsigned int *NumDataWritten );
void PC_SendMsg( const char * Source, unsigned int Size );

#endif
