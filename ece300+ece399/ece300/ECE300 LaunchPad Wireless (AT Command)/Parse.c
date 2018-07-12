#include "Parse.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h> // sprintf
#include <stdlib.h> //calloc free atoi

#define NUM_OF_LINES_PER_USER 9
#define MAX_NUM_USERS         64

bool CharacterCompare( char Character, const char * CompareList );
void ExtractDataString( COMMAND CMD, char * Destination, char ** Tokens, unsigned int TokenCount );
extern CommandCode CMDCodes[COMMAND_NUM];

COMMAND DataParse(char *Destination, unsigned int NumDataWritten)
{
  char DataString[32] = {0};
  char * Tokens[32] = {0};
  unsigned int TokenCount = 0;
  int i = 0;
  COMMAND Ret = ERROR;
  
  TokenCount = Tokenize(Destination, Tokens, 32, ":;\r");
	
	for( i = 0; i < strlen(Tokens[0]); i++)
		Tokens[0][i] = toupper(Tokens[0][i]);
  
  for( i = 0; i < COMMAND_NUM; i++)
    if( strcmp(CMDCodes[i].String, Tokens[0]) == 0 )
      Ret = CMDCodes[i].CMD_Code;
    
  if( Ret != ERROR )
  {
    ExtractDataString(Ret, DataString, Tokens, TokenCount );
    strcpy(Destination, DataString);
  }
  
  return Ret;
}

void ExtractDataString( COMMAND CMD, char * Destination, char ** Tokens, unsigned int TokenCount )
{
  switch( CMD )
  {
    case NODE_SEARCH:
    {
      Destination[0] = 0;
      break;
    }
    
    case SEND_MESSAGE:
    {
      sprintf(Destination, "%s\n%s", Tokens[1], Tokens[2]);
			//                                        ^^^^^^^^^  Here is the message
			//                             ^^^^^^^^^  this is the address or name, depends on how we treat it later
      break;
    }
    
    case MY_ADDRESS:
    {
      Destination[0] = 0;
      break;
    }
    
    case SET_MY_NAME:
    {
			sprintf(Destination, "%s", Tokens[1]);
      break;
    }
    
    case GET_MY_NAME:
    {
      Destination[0] = 0;
      break;
    }
    
    default:
      break;
  }
  
}


// String : string to be tokenized
// TokenList : list of pointers to token strings
// TokenSize : number of max tokens to be found
// Delimiters : the list of characters to seperate the token strings
// Return : number of tokens found
int Tokenize(char * String, char ** TokenList, int TokenSize, const char * Delimiters )
{
	char * TokenWalk = String;
	int TokenIndex = 0;
	bool TokenStartFlag = false;
	bool DoneFlag = false;
	int TokensFound = 0;
	
	while( (*TokenWalk != 0) && !DoneFlag )
	{
		if( CharacterCompare( *TokenWalk, Delimiters ) )
		{
			*TokenWalk = 0;
			TokenStartFlag = false;
		}
		else
		{
			if( !TokenStartFlag )
			{
				TokenList[TokenIndex] = TokenWalk;
				TokenIndex++;
				TokenStartFlag = true;
				TokensFound++;
			}
			
			if( TokenIndex >= TokenSize )
				DoneFlag = true;
		}
		
		TokenWalk++;
	}


	return TokensFound;
}

//this assumes CompareList is null terminated
bool CharacterCompare( char Character, const char * CompareList )
{
	int index = 0;
	
	while( CompareList[index] != 0 )
	{
		if( CompareList[index] == Character )
			return true;
		index++;
	}
	
	return false;
}

void ExtractSerialName( char * String )
{
  int i;
  char * Tokens[64] = {0};
  char * ReconstructStringList[MAX_NUM_USERS] = {0};
  int TokenCount = 0;
  int UserNum = 0;
  
  TokenCount = Tokenize(String, Tokens, 64, "\r");
  
  UserNum = TokenCount / NUM_OF_LINES_PER_USER;
  
  for( i = 0; i < UserNum; i++)
  {
    int TokIndex = NUM_OF_LINES_PER_USER * i;
    ReconstructStringList[i] = (char *) calloc(64, sizeof(char));
    sprintf(ReconstructStringList[i], "Name: %s\rSerial Number:\r  H:%s\r  L:%s\r", Tokens[TokIndex+3], Tokens[TokIndex+1], Tokens[TokIndex+2]);
  }
  
  strcpy(String, ReconstructStringList[0]);
  
  for( i = 1; i < UserNum; i++)
  {
    strcat(String, ReconstructStringList[i]);
    free(ReconstructStringList[i]);
  }
  
  strcat(String, "\r");
}

bool NumDetect( char * String )
{
  int IntVal = atoi(String);
  
//  if( strcmp(String, "0x") == 0 )
//    i = 2;
//  
//  while( String[i] != 0 )
//  {
//    if( (String[i] < '0') || (String[i] > '9') )
//      return false;
//  }
  
  if( IntVal == 0 )
    return false;
  
  return true;
}
