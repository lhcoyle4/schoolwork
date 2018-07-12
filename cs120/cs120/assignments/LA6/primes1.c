#include <stdio.h> /* printf */
/*******************************************************************************
filename    primes1.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
lab         6
due date    10/12/2012

Brief Description:
  A program to define two functions, one to determine whether or not the number
  is prime, another to take a range of numbers and show that each even number
  within the range is a sum of two prime numbers.
*******************************************************************************/

/*******************************************************************************
   Function: is_prime

Description: Given a number, determine whether or not it is prime.

     Inputs: number - the number for which to determine whether or not it is
             prime.

    Outputs: A value (int), TRUE or FALSE, indicating whether the supplied
             number is prime.
*******************************************************************************/
#define FALSE 0
#define TRUE  1

int is_prime(int number)
{
  int i;
  if(number == 1)
    return FALSE;
  else if(number == 2)
    return TRUE;
  else if(number % 2 == 0)
    return FALSE;
  else
  {
    for(i = 3; i < (number / 2); i += 2)
      if(number == i)
        break;
      else if(number % i == 0)
        return FALSE;
      else
        continue;
  }

  return TRUE;
}

/*******************************************************************************
   Function: conjecture

Description: Given a range of numbers, show that each even number is the sum of
             two prime numbers.

     Inputs: low - the number to start finding pairs of primes that equal
             itself.
             high - the last number to calculate primes that add up to it.

    Outputs: A formatted list of all even numbers and the primes that add
             together to equal them.
*******************************************************************************/
void conjecture(int low, int high)
{
  int i;
  int j;
  int k = 2;
  int done;
  for(i = low; i <= high; i += 2)
  {
    done = FALSE;
    for(j = 2; j <= k && (done == FALSE); j++)
    {
      if(is_prime(j))
      for(k = 2; k <= i && (done == FALSE); k++)
        {
          if(is_prime(k) && i == (j + k))
            {
              printf("%3i = %3i + %3i\n", i, j, k);
              done = TRUE;
            }
        }
    }
  }
}