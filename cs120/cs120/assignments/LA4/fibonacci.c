/* A program to create a table of fibonacci numbers and the corresponding     */
/* Fibonacci quotients up to a user specified n times, where n is between 2   */
/* and 46.                                                                    */

#include <stdio.h>

void inputheader(void)       /* fn to print text to display before user input */
{
printf("Enter the Fibonacci number to calculate.\n");
printf("The number must be an integer between 2 and 46. (Enter 1 to quit): ");
}

void header(void)                  /* fn to print text for beginning of table */
{
printf("\n           Fibonacci        Fibonacci\n");
printf(" N           number          quotient\n");
printf("-------------------------------------\n");
printf(" 0             0                  N/A\n");
printf(" 1             1                  N/A\n");
}

int main (void)
{
int Fnumber;                  /* int for the fibonacci number to calculate to */
int Fnumber1 = 1;                                      /* int for Fnumber - 1 */
int Fnumber2 = 1;                                      /* int for Fnumber - 2 */
int Fnumberh = 1;                              /* new int holder for Fnumber1 */
double Fquotient;                        /* double for the fibonacci quotient */
int i;                                                /* int for loop counter */

do
{
  inputheader();
  scanf("%i", &Fnumber);
  if(Fnumber == 1)
    return 0;
}
while(Fnumber < 2 || Fnumber > 46);

header();

for(i = 2; i <= Fnumber; i++)      /* loop to calc/print fib #s and quotients */
  {
    Fquotient = (double)Fnumber1 / (double)Fnumber2;
    printf("%2i%14i   %2.16f\n", i, Fnumberh, Fquotient);
    Fnumberh = Fnumber1 + Fnumber2;
    Fnumber2 = Fnumber1;
    Fnumber1 = Fnumberh;
  }
return 0;
}