/******************************************************************************
filename    marathon.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
assignment  1
due date    10/08/2012

Brief Description:
  A marathon is 26 miles, 385 yards
  Prints the distance of a marathon in kilometers

******************************************************************************/

#include <stdio.h> /* printf */

#define YARDS_PER_MILE 1760
#define KILOS_PER_MILE 1.609

int main(void)
{
  int miles, yards;
  double kilometers;

  miles = 26;
  yards = 385;
  kilometers = (miles + (double)yards / YARDS_PER_MILE) * KILOS_PER_MILE;
  printf("A marathon is %f kilometers\n", kilometers);

  return 0;
}