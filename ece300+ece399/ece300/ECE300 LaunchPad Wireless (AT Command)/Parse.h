#ifndef PARSE_H
#define PARSE_H
#include "Common.h"
#include "PC_CMD.h"

COMMAND DataParse(char *Destination, unsigned int NumDataWritten);
int Tokenize(char * String, char ** TokenList, int TokenSize, const char * Delimiters );

void ExtractSerialName( char * CommandResp );
bool NumDetect( char * CommandValue );

#endif
