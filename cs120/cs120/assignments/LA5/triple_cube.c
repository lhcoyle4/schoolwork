#include <stdio.h>

void print_cubes(void)
{
  int i, onesd, tensd, hundredsd, onescube, tenscube, hundredscube, cube;
  for(i = 100; i <= 999; i++)
    {
      onesd = i % 10;
      tensd = (i % 100) / 10;
      hundredsd = i / 100;
      onescube = onesd * onesd * onesd;
      tenscube = tensd * tensd * tensd;
      hundredscube = hundredsd * hundredsd * hundredsd;
      cube = onescube + tenscube + hundredscube;
      if (cube == i)
        {
          printf("%i has the cube property. ", i);
          printf("(%i + %i + %i)\n", hundredscube, tenscube, onescube);
        }
    }
}

void print_pythagorean_triples(int low, int high)
{
  int i, j, k, triplea, tripleb, triplec, idcount;
  idcount = 0;
  for(i = low; i < high; i++)
    {
      for(j = (i + 1); j < high; j++)
      {
        for(k = (j + 1); k < high; k++)
        {
          if((k > j) && (k > i))
          {
            triplec = k * k;
            tripleb = j * j;
            triplea = i * i;
          }
          else if((j > k) && (j > i))
          {
            triplec = j * j;
            tripleb = k * k;
            triplea = i * i;
          }
          else
          {
            triplec = i * i;
            tripleb = k * k;
            triplea = i * i;
          }

          if((triplea + tripleb) == triplec)
          {
            idcount += 1;
            printf("Triple # %2i:  %2i, %2i, %2i --> ", idcount, i, j, k);
            printf("%4i + %4i = %4i\n", triplea, tripleb, triplec);
          }
        }
      }
    }
}


