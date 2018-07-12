#include <stdio.h>

/* Prototypes */
int strtoint(const char string[]);
void inttostr(int number, char string[]);

void test1(void)
{
  printf("%i\n", strtoint("0"));
  printf("%i\n", strtoint("1"));
  printf("%i\n", strtoint("12"));
  printf("%i\n", strtoint("123"));
  printf("%i\n", strtoint("1234"));
  printf("%i\n", strtoint("1234567890"));
  printf("%i\n", strtoint("-0"));
  printf("%i\n", strtoint("-12"));
  printf("%i\n", strtoint("-123"));
  printf("%i\n", strtoint("-124"));
  printf("%i\n", strtoint("-1234567890"));
}

void test2(void)
{
  char buffer[12];
  
  inttostr(1, buffer);
  printf("|%s|\n", buffer);


  inttostr(12, buffer);
  printf("|%s|\n", buffer);

  inttostr(123, buffer);
  printf("|%s|\n", buffer);

  inttostr(1234, buffer);
  printf("|%s|\n", buffer);

  inttostr(1234567890, buffer);
  printf("|%s|\n", buffer);

  inttostr(0, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1, buffer);
  printf("|%s|\n", buffer);

  inttostr(-12, buffer);
  printf("|%s|\n", buffer);

  inttostr(-123, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1234, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1234567890, buffer);
  printf("|%s|\n", buffer);

}

int main(void)
{
  printf("\n============== Test 1 ================\n");
  test1();  


  printf("\n============== Test 2 ================\n");
  test2();  


  return 0;
}
