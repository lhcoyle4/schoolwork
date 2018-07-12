/*******************************************************************************
filename    reverse.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
lab         12
due date    12/04/2012

Brief Description:
  Given a string, make the last word the first word, second to last word the 
  second to first word, etc.
*******************************************************************************/
#include <string.h> /* strlen, strcpy */

/*******************************************************************************
   Function: reverse

Description: Helper function to reverse a range of characters.

     Inputs: *start - the beginning of the range of characters to reverse.
             *end   - the end of the range of characters to reverse.

    Outputs: None. Reverses the characters within the string they belong to.
*******************************************************************************/
static void reverse(char *start, char *end)
{
  /* to hold the value of *start before it gets changed, so *end can be set */
  char temp; 

  while(start < end)
  {
    temp = *start; /* hold the current value of *start before changed       */
    *start++ = *end; /* set *start to *end and then increment *start        */
    *end-- = temp; /* set *end to original value from *start, then dec *end */
  }
}

/*******************************************************************************
   Function: reverse_words2

Description: Given an input string, reverse the order of the words.

     Inputs: input[] - the input string to reverse words within.

    Outputs: None. Reverses the words within the input string.
*******************************************************************************/
void reverse_words2(char input[])
{
  int remaining = strlen(input) - 1; /* length of the input string w/o nul */
  int i = 0;
  char wordstart = 0; /* to record element in which a word starts */
  char wordend = 0; /* to record element in which a word ends     */
  char wordflag = 0; /* to record whether currently in a word     */

  reverse(input, (input + remaining)); /* reverse the whole string */

  /* reverse each word in the string, so letters are in order               */
  while(input[i] != 0) /* keep on iterating as long as not at end of string */
  {
    /* if the current element isn't space and aren't already in a word       */
    if(input[i] != ' ' && wordflag == 0)
    {
      wordstart = i; /* record that a word starts here                       */
      wordflag = 1; /* and set the flag so as not to keep changing wordstart */
    }
    else if(input[i] == ' ') /* if current element is a space, do stuff       */
    {
      if(i != 0 && input[i - 1] != ' ') /* if previous element wasn't a space */
      {
        wordend = i - 1; /* then up to the previous element is a word         */
        reverse(input + wordstart, input + wordend); /* reverse the word      */

        wordflag = 0; /* we're done with this word, so we can reverse another */
        i++; /* look at the next element next iteration                       */
      }
      else
        i++; /* the previous element was a space, so keep incrementing       */
    }
    else if(input[i + 1] == 0 && wordflag == 1) /* if next element nul     */
    {
      wordend = i; /* the word ends just before nul because flag == 1      */
      reverse(input + wordstart, input + wordend); /* so reverse that word */
      i++; /* and increment i so the loop breaks                           */
    }
    else
      i++; /* still in a word (no space yet), so keep incrementing */
  }
  
}

/*******************************************************************************
   Function: reverse_words1

Description: Given an input string and an output string, reverse the order of 
             the words and put the reversed order into output.

     Inputs: input[]  - the input string to reverse words within.
             output[] - the array to put the reversed order of words into.

    Outputs: None. Reverses the input string's words and puts them into output.
*******************************************************************************/
void reverse_words1(const char input[], char output[])
{
 strcpy(output, input); /* copy input into output */
 reverse_words2(output); /* then use reverse_words2 on the output  */
}

