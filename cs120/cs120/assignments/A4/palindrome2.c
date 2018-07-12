/*******************************************************************************
filename    palindrome2.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
assignment  4
due date    11/07/2012

Brief Description:
  Given an array of characters, determine if it's a palindrome using pointers.
  Returns 1 (true) if the phrase is a palindrome and 0 if not.

*******************************************************************************/

/*******************************************************************************
   Function: is_palindrome2

Description: Given an array of characters, determine if it's a palindrome using 
             pointers.

     Inputs: *phrase - the given array of characters.
              length - the length of the given array of characters.

    Outputs: Returns 1 (true) if the phrase is a palindrome and 0 if not.
*******************************************************************************/

int is_palindrome2(const char *phrase, int length)
{
  int i = 0;            /* while loop index, to be compared with (length / 2) */
 /* flag to record if palindrome, cause loop to break as soon as deemed false */
  unsigned char ispal = 1;  /* also, the value to be returned at function end */

  while(ispal == 1 && i < (length / 2)) /* iterate through 1/2 array elements */
  {                                           /* if 1st==last, 2nd==2ndlast...*/
    if(*(phrase + i) == *(phrase + (length - (i + 1)))) 
      i++;                      /* increment i and continue checking elements */
    else 
      ispal = 0;        /* if checked elements !=, then not a pal, break loop */
  }

  return ispal;             /* returns 1 if all checks passed, else returns 0 */
}