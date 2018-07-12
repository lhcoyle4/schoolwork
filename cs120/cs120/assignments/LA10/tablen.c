/*******************************************************************************
filename    tablen.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
lab         10
due date    11/13/2012

Brief Description:
  Checks an input file for tabs and lines longer than 80 characters. Prints the
  number of tabs in any line that contains them. Prints the length of any line
  that is longer than 80 characters. At the end, prints the number of too-long
  lines and the length of the longest line.

*******************************************************************************/
#include <stdio.h> /* FILE I/O, printf */
#define MAX_LINE_LENGTH 1000

/*******************************************************************************
   Function: tablen (made up of functions tab & len)

Description: Given file, determine if it contains tabs or lines longer than 80
             characters and correctly print this information.

     Inputs: char *filename - a pointer to the file to be opened and read.

    Outputs: None. Function will print the lines with tabs as well as the
             too-long lines to the screen. Will also print a summary at the end,
             containing the number of too-long lines and the length of the
             longest line.
*******************************************************************************/
void tab(const char *filename)
{
  char buffer[MAX_LINE_LENGTH];  /* the max size of each line to use fgets on */
  int line = 1;          /* the number of lines checked, starting with line 1 */
  int i;            /* for loop index, to iterate through each char in string */
  int tabst = 0;     /* counter variable for total number of tabs in the file */

  FILE *fp;                     /* for reading from a file                    */

  fp = fopen(filename, "rt");   /* open the file for read                     */
  if (fp)                       /* if the file was opened successfully        */
  {
    while(!feof(fp))            /* while not at the end of the file           */
    {
      if(fgets(buffer, MAX_LINE_LENGTH, fp)) /* read in the next line         */
      {
        int tabs = 0;     /* counter variable for number of tabs in each line */

        for(i = 0; i < MAX_LINE_LENGTH; i++)   /* increment through each char */
        {
          if(buffer[i] == '\t') /* if char is a tab, increment tabs           */
            tabs++;
          else if(buffer[i] == '\n')  /* if char is a new line, set it to nul */
          {
            buffer[i] = 0;
            break;              /* and break out of the loop                  */
          }
        }

        if(tabs > 0)            /* if there are more than 0 tabs in the line  */
        {
          /* print the line number, number of tabs and the line itself        */
          printf("#%3i: (tabs:%2i) |%s|\n", line, tabs, buffer);
          tabst += tabs; /* also add the number of tabs in this line to total */
        }
      }
      line++;  /* increment the counter for n of lines that have been checked */
    }
    fclose(fp);                 /* close the file                             */
  }
  /* print out the summary for total number of tabs in the file               */
  printf("*****  TABS IN USE  *****: ");
  printf("Number of tabs in the file is %2i.\n", tabst);
}


void len(const char *filename)
{
  char buffer[MAX_LINE_LENGTH];  /* the max size of each line to use fgets on */
  int line = 1;          /* the number of lines checked, starting with line 1 */
  int overlens = 0;  /* counter variable for total number of overlength lines */
  int longestline = 0;   /* to hold the line number of the longest line found */
  int longestlinec = 0;   /* to hold the number of characters in longest line */

  FILE *fp;                     /* for reading from a file                    */

  fp = fopen(filename, "rt");   /* open the file for read                     */
  if (fp)                       /* if the file was opened successfully        */
  {
    while(!feof(fp))            /* while not at the end of the file           */
    {
      if(fgets(buffer, MAX_LINE_LENGTH, fp)) /* read in the next line         */
      {
        int len = 0;          /* counter variable for the length of each line */

        while(buffer[len] != '\n')   /* count length of string up to new line */
          len++;                /* keep track of the length with len variable */
 
        buffer[len] = 0;        /* overwrite the newline character with a nul */

        if(len > 80)            /* if the line is overlength                  */
        {
          /* print out the line number, its length and the line itself        */
          printf("#%3i: (%3i) |%s|\n", line, len, buffer);

          overlens++;           /* increment the number of overlength strings */

          if(len > longestlinec)/* if this line is the longest found          */
          {
            longestlinec = len; /* set to contain the number of chars         */
            longestline = line; /* and record the line number                 */
          }
        }
      }
      line++;  /* increment the counter for n of lines that have been checked */
    }
    fclose(fp);                 /* close the file                             */
  }
  /* print the summary of all overlength lines as well as the longest line    */
  printf("***** LINE TOO LONG *****: %i lines longer than 80.", overlens);
  printf(" Longest line is %i at %i chars.\n", longestline, longestlinec);
}


void tablen(const char *filename)
{
  tab(filename);  /* call the function that counts and prints tabs            */
  len(filename);  /* call the function that determines and prints line length */
}
