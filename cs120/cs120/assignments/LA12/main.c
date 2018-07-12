#include <stdio.h>

/* Prototypes */
void reverse_words1(const char input[], char output[]);
void reverse_words2(char input[]);

void test1(void)
{
  {
  char words1[] = "This";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  {
  char words1[] = "This is";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  {
  char words1[] = "This is a";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  {
  char words1[] = "This is a string";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  {
  char words1[] = "forth brought fathers our ago years seven and score Four";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }

  /* Bonus */
  {
  char words1[] = "   This  is another   string ";
  char rev1[sizeof(words1) + 1];
  printf(" Input string: |%s|\n", words1);
  reverse_words1(words1, rev1);
  printf("Output string: |%s|\n", rev1);
  }
}

void test2(void)
{
  {
  char words[] = "This";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  {
  char words[] = "This is";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }


  {
  char words[] = "This is a";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  {
  char words[] = "This is a string";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  {
  char words[] = "forth brought fathers our ago years seven and score Four";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

  /* Bonus */
  {
  char words[] = "   This  is another   string ";
  printf(" Input string: |%s|\n", words);
  reverse_words2(words);
  printf("Output string: |%s|\n", words);
  }

}

int main(void)
{

  printf("\n============== Test 1 ================\n");
  test1();  

  printf("\n============== Test 2 ================\n");
  test2();  


  return 0;
}
