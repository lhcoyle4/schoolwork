/*******************************************************************************
filename    jumble.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
assignment  5
due date    11/14/2012

Brief Description:
  Encodes or decodes a given string with a given password and number of passes.

*******************************************************************************/
#include "jumble.h" /* mystrlen, jumble, ENCODE, DECODE */

/*******************************************************************************
   Function: mystrlen

Description: Given a string, determine its length, not including the nul.

     Inputs: *string - the input string.

    Outputs: A value(int) being the number of characters in the string.
*******************************************************************************/
int mystrlen(const unsigned char *string)
{
  int len = 0;            /* to hold the length of the string                 */

  while(string[len] != 0) /* starting at the first element, check if nul      */
    len++;                /* if not nul, increment len and continue looping   */

  return len;    /* after encountering a nul and loop ends, return the length */
}

/*******************************************************************************
   Function: jumble

Description: Encodes or decodes a string, depending on the parameters provided.

     Inputs: *string - the input string to encode or decode.
           *password - the string that will be used to encode/decode the input.
              method - can be either ENCODE or DECODE. This tells you whether to
                       encode or decode the input.
              passes - how many times you need to encode or decode the input.

    Outputs: None. The input string itself will be changed.
*******************************************************************************/
void jumble(unsigned char *string, 
            const unsigned char *password, 
            enum CODE_METHOD method, 
            int passes)
{
  int slength = mystrlen(string); /* find and store the length of the input   */
  int pwlength = mystrlen(password); /* do the same for the length of the pw  */
  int i;                             /* for loop index                        */
  int pwcount = 0;             /* to keep track of which element of pw to add */

  if(method == DECODE)  /* if the method is set to decode, then subtraction   */
    passes *= -1;       /* so make passes negative so that subtraction occurs */

  for(i = 0; i < slength; i++)   /* iterate through each element in the input */
  {
    string[i] += password[pwcount] * passes; /* encode/decode the string      */

    if(pwcount == pwlength - 1) /* if pwcount is equal to last element of pw  */
      pwcount = 0;         /* set it back to be the first element of password */
    else
      pwcount++;      /* otherwise continue incrementing through the elements */
  }
}