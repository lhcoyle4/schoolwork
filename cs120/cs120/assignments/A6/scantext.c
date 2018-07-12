/*******************************************************************************
filename    scantext.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
assignment  6
due date    11/26/2012

Brief Description:
  Will scan and manipulate strings in various different ways, including finding
  string length, counting number of tabs, substituting chars, finding length
  after converting tabs to spaces, and counting number of words.

*******************************************************************************/

/*******************************************************************************
   Function: mystrlen

Description: Given a string, determine and return its length.

     Inputs: *string - The input string to determine length of.

    Outputs: A value (int), indicating the number of characters in the string.
*******************************************************************************/
static int mystrlen(const char *string)
{
  /* Counter variable for number of chars in the string                  */
  int length = 0;
  
  /* While there are more chars in the string, increment length for each */
  while (*string++)
    length++;

  /* Return the total number of chars in the string                      */
  return length;
}

/*******************************************************************************
   Function: count_tabs

Description: Given a string, determine and return number of tabs in string.

     Inputs: *string - The input string to count number of tabs for.

    Outputs: A value (int), indicating the number of tabs in the string.
*******************************************************************************/
int count_tabs(const char *string)
{
  /* Counter variable for number of tabs in the string                  */
  int tabs = 0;

  /* While there are still more chars in the string, check next char    */
  while(*string) /* Starting with char 0 in the string                  */
  {
  /* Increment tabs variable if the current char is a tab               */
    if (*string == '\t')
      tabs++;
  /* Increment string to point to the next char in the string array     */
    string++;
  }

  /* Return the total number of tabs in string after checking each char */
  return tabs;
}

/*******************************************************************************
   Function: substitute_char

Description: Given a string, substitute old_char with new_char and return the 
             number of substitutions.

     Inputs: *string  - The input string to substitute chars in.
             old_char - The char to check for and be replaced.
             new_char - The char to replace old_char with.

    Outputs: A value (int), indicating the number of substitutions.
*******************************************************************************/
int substitute_char(char *string,
                    char old_char,
                    char new_char)
{
  /* Counter variable for the number of substitutions that occurred      */
  int subs = 0;

  /* While there are still more chars in the string, check next char     */
  while(*string) /* Starting with char 0 in the string                   */
  {
  /* If the current char is the old_char                                 */
    if(*string == old_char)
    {
  /* Then replace the current char with the new_char                     */
      *string = new_char;
  /* And increment the subs variable to indicate a substitution occurred */
      subs++;
    }
  /* Increment string to point to the next char in the string array      */
    string++;
  }

  /* Return the total number of subs occurred after checking each char   */
  return subs;
}

/*******************************************************************************
   Function: calculate_lengths

Description: Given a string and a tabsize, determine the length of the string 
             and the display length of the string. The display length is the 
             number of chars that will be required to display the string after 
             tabs are expanded into spaces.

     Inputs: *string         - The input string to calculate lengths for.
             tabsize         - The number of spaces in each tab.
             *string_length  - Will be set to the length of the string.
             *display_length - Will be set to the display length of the string.

    Outputs: None. However, the integer pointers *string_length and 
             *display_length will be used by the main function.
*******************************************************************************/
void calculate_lengths(const char *string,
                       int tabsize,
                       int *string_length,
                       int *display_length)
{
  /* Set the *display_length variable to 0 so count is done correctly        */
  *display_length = 0;

  /* Set *string_length to the output from the mystrlen function for *string */
  *string_length = mystrlen(string);

  /* While there are still more chars in the string, check next char         */
  while(*string) /* Starting with char 0 in the string                       */
  {
  /* If the current char is a tab then add the tabsize to *display_length    */
    if(*string == '\t')
      *display_length += tabsize;
  /* Otherwise, just increment *display_length by 1                          */
    else
      (*display_length)++;
  /* Increment string to point to the next char in the string array          */
    string++;
  }
}

/*******************************************************************************
   Function: count_words

Description: Given a string, determine and return the number of words. 

     Inputs: *string - the input string to determine number of words for.

    Outputs: A value (int), indicating the number of words in the string. Words
             in a string are delimited by whitespace chars which can be any of
             the following: space, newline or tab.
*******************************************************************************/
int count_words(const char *string)
{
  /* Counter variable for the number of words in the string                 */
  int words = 0;

  /* Flag variable to keep track of when loop encounters char != whitespace */
  int wordflag = 0; /* Will be set to 1 when a non-whitespace char is found */

  /* While there are still more chars in the string, check next char        */
  while(*string) /* Starting with char 0 in the string                      */
  {
  /* If current char is whitespace, (space, tab or newline)                 */
    if(*string == ' ' || *string == '\t' || *string == '\n')
    {
  /* And if the wordflag is set to 1 (means prev non-whitespace char)       */
      if(wordflag == 1)
      {
  /* Then a word has been found, increment the words var and reset flag     */
        words++;
        wordflag = 0;
      }
    }
  /* Otherwise, the current char is not whitespace, so set the flag         */
    else
      wordflag = 1;

  /* Increment string to point to the next char in the string array         */
    string++;
  }

  /* If flag is still set after loop ends, then last word was not counted   */
  /* because the word wasn't delimited by whitespace at the end             */
  if(wordflag == 1)
  /* In this case, increment the words variable to account for last word    */
    words++;

  /* Return the counted number of words for the string                      */
  return words;
}