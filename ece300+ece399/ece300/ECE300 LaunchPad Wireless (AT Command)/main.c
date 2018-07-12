/*************************************************************
**************************************************************
    ECE 300 – Spring 2014

    Louis Coyle
    Homework #: 06

    Copyright DigiPen (USA) Corporation
    All Rights Reserved
**************************************************************
*************************************************************/


#include "PC_CMD.h"
#include "WirelessXBee.h"
#include "Parse.h"
#include "Timer.h"
#include "Clocks.h"
#include "Common.h"
#include "UART.h"

//below must be defined in Build -> ARM Compiler -> Advanced Options -> Predefined Symbols
//DEBUG
//PART_TM4C123GH6PM
//TARGET_IS_BLIZZARD_RB1

int main() 
{
    char CommandValue[64] = {0};
    char CommandResp[256] = {0};
    unsigned int ByteCount = 0;
  
    SystemClocksInitialize();
    PC_CMDInit();
    XBee_Initialize();

    /*
    while(true)
    {
    	UART_Wireless_Send("U", strlen("U") );
    	BlockingDelay(1000);
    }
    */

    // enable the RF module to operate using the frame-based API mode
    XBee_ATCommand("AP", 1, CommandResp, "\r");

    while ( true )
    {
	  //get command from user and parse its arguments
      switch( PC_GetCommand(CommandValue, 64, &ByteCount) )
      {
        case NODE_SEARCH: // this will fail if there is not another XBee module powered in the area
        {
          char Command[] = "ND";
          char Delimit[] = "\r\r\r";

          PC_SendMsg( "\rSearching...\r", strlen("\rSearching...\r") );
					//Send AT ND
          //Get resulting string (wait for two \r in a row)
          XBee_ATCommand(Command, 0, CommandResp, Delimit);
          //PC_SendMsg( CommandResp, strlen(CommandResp) );
          //parse string
          ExtractSerialName( CommandResp );
          //source address 0xXXXX (two bytes worth, in ascii)
          //serial number high (4 bytes worth, in ascii)
          //serial number low (4 bytes worth, in ascii)
          //node identifier string (up to 20 bytes)
          
          //send string to user
          PC_SendMsg( CommandResp, strlen(CommandResp) );
          break;
        }
        
        case SEND_MESSAGE:
        {
          char * Tokens[3] = {0};
          
          Tokenize(CommandValue,Tokens,3,"\n");
          //check if name or number
          if( NumDetect(Tokens[0]) )
          {
            char * NumToks[2] = {0};
            Tokenize(Tokens[0], NumToks, 2, " ");
            //send AT DH with high value
            XBee_ATCommand("DH", NumToks[0], CommandResp, "\r");
            //send AT DL with low value
            XBee_ATCommand("DL", NumToks[1], CommandResp, "\r");
          }
          else
            //if name, send AT DN\r
            XBee_ATCommand("DN", Tokens[0], CommandResp, "\r");

          //then send message to that user
          XBee_SendMsg( Tokens[1] );
          XBee_SendMsg( "\r" );
          
          break;
        }
        
        case MY_ADDRESS:
        {
          //send AT SH - gets my high serial value
          XBee_ATCommand("SH", 0, CommandResp, "\r");
          //send response to user
          //
          //send AT SL - gets my low serial value
          XBee_ATCommand("SL", 0, CommandResp, "\r");
          //send string to user
          PC_SendMsg( CommandResp, strlen(CommandResp) );
          break;
        }
        
        case SET_MY_NAME:
        {
          //send AT NI <up to 20 char string>
          XBee_ATCommand("NI", CommandValue, CommandResp, "OK");
//          //save settings by sending AT WR
					
					BlockingDelay(1.0f);
					
          XBee_ATCommand("WR", 0, CommandResp, "OK");
					PC_SendMsg( "\rNameSaved\r", strlen("\rNameSaved\r") );
          break;
        }
        
        case GET_MY_NAME:
        {
          //send AT NI - with no arguments
          XBee_ATCommand("NI", 0, CommandResp, "\r");
          //send string to user
          PC_SendMsg( CommandResp, strlen(CommandResp) );
          break;
        }
        
        default:
        {
          PC_SendMsg( "Error:\r", strlen("Error:\r") );
          PC_SendMsg( CommandValue, strlen(CommandValue) );
          break;
        }
      }
    }
}
 

