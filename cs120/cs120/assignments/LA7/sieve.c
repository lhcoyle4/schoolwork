#include <stdio.h> /* printf      */
#include <math.h>  /* sqrt        */
#include "sieve.h" /* TRUE, FALSE */

#define SQRTSIZE sqrt(size)

void sieve(int array[], int size)
{
  int i, j, k;

  for (i = 0; i < size; i++)
  {
    array[i] = TRUE;
  }

  array[0] = FALSE;
  array[1] = FALSE;

  for (j = 2; j < SQRTSIZE; j++)
  {
    for (k = j + j; k < size; k += j)
    {
      array[k] = FALSE;
    }
  }
}

int twin_primes(const int primes[], int size)
{
  int i = 0;
  int count = 1;

  while(i < size)
  {
    if(primes[i] == primes[i+2] && primes[i] == TRUE && primes[i+2] == TRUE)
      {
        printf("twin prime #%4i: %4i and %4i\n", count, i, i+2);
        count++;
      }
    i++;
  }
  return count - 1;
}

double brun_constant(const int primes[], int size)
{
  int i = 0;
  double numerator = 1.0;
  double b_const = 0.0;

  while(i < size)
    {
      if(primes[i] == primes[i+2] && primes[i] == TRUE && primes[i+2] == TRUE)
        {
          b_const += ((numerator / i) + (numerator / (i+2)));
        }
      i++;
    }
  return b_const;
}