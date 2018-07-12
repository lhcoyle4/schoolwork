#include <stdio.h>     /* printf      */
#include <ctype.h>     /* toupper     */
#include "histogram.h" /* lab defines */

/******************************************************************************
filename    histogram.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
lab         8
due date    10/30/2012

Brief Description:
  A program to analyze a given string of characters and output various different
  statistics, including the number of letters, spaces and other characters, a
  histogram of the number of occurrences of each letter, a calculated "average",
  the letter that occurs the most frequently and the number of times that letter
  occurrs.

******************************************************************************/


/*******************************************************************************
   Function: GetCounts

Description: Count the number of letters, spaces and other characters in one or
             more sentences.

     Inputs: sentence - an array of const characters, that the function will
                        read, not change.
               length - the number of characters in the sentence array.
              letters - will contain the number of occurrences of each letter.
               spaces - will contain number of spaces in the sentence.
                other - will contain number of other characters in the sentence.

    Outputs: The total number(int) of characters that were counted. The main
             function will also print spaces and other.
*******************************************************************************/

int GetCounts(const char sentence[], int length, int letters[], int *spaces, int *other)
{
  int i;
  int j = 0;
  int totalLetters = 0;  /* total number of letters, returned at function end */
  *spaces = 0;
  *other = 0;

  for (i = 0; i < NUM_LETTERS; i++)
  {
    letters[i] = 0;            /* set every element of the letters array to 0 */
  }

  for (i = 0; i < length; i++)  /* inc through input sentence, checking chars */
  {
    for (j = 0; j < NUM_LETTERS; j++)   /* check current char for all letters */
    {
      if(toupper((int)sentence[i]) - 65 == j)
      {
        letters[j] += 1;/* inc approrpiate array element and letter count var */
        totalLetters += 1;
      }
    }
    if(sentence[i] == 32)           /* if current char is a space, inc spaces */
    {
      *spaces += 1;
    }
    else                  /* otherwise, it is another character, so inc other */
    {
      *other += 1;
    }
  }
/* subtract totalLetters from other as it holds # of chars that aren't spaces */
  *other -= totalLetters;

  return totalLetters;      /* return the totalLetters counted from the input */
}


/*******************************************************************************
   Function: PrintHistogram

Description: Given the array, letters, prints a histogram of the letters with an
             asterisk(*) for each occurrence of the letter.

     Inputs: letters - an array with 26 elements, each set to the number of
                       times that letter occurred in the input sentence.

    Outputs: None by function definition, but will print a list of occurrences
             of each letter, in histogram form.
*******************************************************************************/

void PrintHistogram(const int letters[])
{
  int i;
  int j;

  for (i = 0; i < NUM_LETTERS; i++) /* iterate through each letter */
  {
    printf("%c:", i+65); /* print letter, starting with A(i=0), followed by : */
    for(j = 0; j < letters[i]; j++)  /* iterate # of times each letter occurs */
      printf("*");  /* print an asterisk after : for each iteration of j loop */
    printf("\n");    /* start a new line for which to print next letter count */
  }
}


/*******************************************************************************
   Function: GetStatistics

Description: Return various information about the given sentence.

     Inputs: letters - the array of counts that was filled in by GetCounts.
             average - will contain the "average" of the letters, calculated by
                       multiplying the count of each letter by its weight(pos in
                       alphabet), adding these products and dividing by 26.
          max_letter - will contain the letter that appeared most in sentence.
           max_count - will contain the number of times that max_letter appeared
                       in sentence.

    Outputs: No outputs by function defintion, but the main function will print
             average, max_letter and max_count.
*******************************************************************************/

void GetStatistics(const int letters[], double *average, char *max_letter, int *max_count)
{
  int i;
  *average = 0;
  *max_letter = 0;
  *max_count = 0;

  for(i = 0; i < NUM_LETTERS; i++) /* iterate through each letter for average */
  {
    *average += (i+1) * letters[i]; /* mult count of current letter by weight */
       /* check to see if count of current letter is higher than recorded max */
    if(letters[i] > *max_count)
    {
      *max_letter = i+65;                /* if so, set max_letter to new char */
      *max_count = letters[i];                 /* and max_count to new number */
    }
  }
  *average /= 26;  /* divide the sum of the products by 26 to get the average */
}

