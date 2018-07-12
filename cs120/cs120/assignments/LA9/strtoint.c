#include <string.h> /* strlen */

/*******************************************************************************
filename    strtoint.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
lab         9
due date    11/5/2012

Brief Description:
  Convert a string of digits into an integer and also does the opposite.

*******************************************************************************/

/*******************************************************************************
   Function: strtoint

Description: Convert a string of digits into an integer

     Inputs: string[] - an array of digits.

    Outputs: The converted->(int) version of the string.
*******************************************************************************/

int strtoint(const char string[])
{
  int i;                                                    /* for loop index */
  int inth = 0;                        /* to hold digits converted to integer */
  int length = (signed)strlen(string) - 1;/* length of the given string array */
  unsigned char isneg;         /* flag variable for if the string is negative */

  if(string[0] == '-')     /* determines if the string starts with a negative */
    isneg = 1;                            /* if so, it sets isneg to 1 (true) */
  else
    isneg = 0;                            /* else, it sets isneg to 0 (false) */

  for(i = 0; i < length; i++)    /* goes from the first to last array element */
  {
    if(i == 0 && isneg)           /* if isneg is true, skip for first element */
    {
      continue;
    }
      inth += string[i] - '0';/* add&convert each digit by indexing by 0 char */
      inth *= 10;   /* *10 to place the next converted digit in correct place */
  }

  inth += string[length] - '0';      /* add the final digit to the ones place */

  if(isneg)          /* if the string began with '-' return a negative total. */
    return -inth;
  else
    return inth;                             /* else, return a positive total */
}

/*******************************************************************************
   Function: inttostr

Description: Convert an integer into a string of digits.

     Inputs: number - the integer to be converted.
           string[] - the array to put each digit into.

    Outputs: None. The converted->(str) version of the integer will be put into 
             the string[] array.
*******************************************************************************/

void inttostr(int number, char string[])
{
  int i;                                                    /* for loop index */
  unsigned char isneg;  /* flag variable for if the given integer is negative */
  char tostring;           /* to hold the current digit to be added to string */
  int length;             /* length of the string array, tbd before reversing */
  char elementh;     /* holder for the element being changed during reversing */

  if(number < 0)                /* determines if the given number is negative */
  {
    isneg = 1;                                /* if so, sets isneg to 1(true) */
    number *= -1;                                /* and makes number positive */
  }
  else
    isneg = 0;                                /* else, sets isneg to 0(false) */

  for(i = 0; i < 11; i++)         /* iterates up to the max length for string */
  {
    tostring = (number % 10) + '0';     /* converts the ones place to a digit */
    number /= 10;                   /* removes the ones digit from the number */
    if(i != 0 && tostring == '0')           /* if number is 0 after dividing, */
    {
      if(isneg)                                   /* if the int was negative, */
      {
        string[i] = '-';          /* make the element contain a negative sign */
        string[i+1] = 0;        /* and add a nul terminator to end the string */
        break;
      }
      else
      {
        string[i] = 0;        /* else, add a nul terminator to end the string */
        break;
      }
    }
    else
      string[i] = tostring;   /* otherwise, just set the element to the digit */
  }

  length = (signed)strlen(string) - 1; /* length of array from above for loop */

  for(i = 0; i < ((length / 2) + 1); i++)  /* iterate until 1/2 through array */
  {
    elementh = string[i];                   /* hold the element to be changed */
    string[i] = string[length - i];/* swap 1st:last,2nd:2ndtolast... elements */
    string[length - i] = elementh; /* set last,2ndtolast... element to holder */
  }
}