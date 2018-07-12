/*******************************************************************************
filename    pi.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
assignment  2
due date    10/17/2012

Brief Description:
  A program to approximate the value of pi using two different methods.

*******************************************************************************/

#include <math.h> /* sqrt */

/*******************************************************************************
   Function: circle_pi

Description: Calculates the area of a quarter-circle using rectangles. As the
             number of rectangles increases, the width of each rectangle
             decreases and gives a more accurate value for pi.

     Inputs: rectangles - the number of rectangles to be used inside of the
             quarter-circle for the calculation of pi.

    Outputs: The approximation of pi calculated with the number of rectangles
             inputted.
*******************************************************************************/
#define RADIUS 2.0

double circle_pi(int rectangles)
{
  int i;           /* iterator for loop: current rectangle area being calc'ed */
  double width = RADIUS / (double)rectangles;    /* width of rectangles for i */
  double height;                     /* the height of rectangle to be calc'ed */
  double area = 0.0;                    /* the area of the rectangles calc'ed */

  for (i = 1; i <= rectangles; i++)
  {
    double rectmidpt = (width * i) - (0.5 * width);        /* horiz. midpoint */
    height = sqrt((RADIUS * RADIUS) - (rectmidpt * rectmidpt));
    area += (width * height);
  }

  return area;   /* return the calculation for pi with the current # of rects */
}

/*******************************************************************************
   Function: leibniz_pi

Description: Approximates pi using a formula derived by Gottfried Leibniz. It
             uses an infinite series of additions and subtractions to
             approximate pi: pi/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + ...
             This approximates pi/4. After the summation, multiplies by 4 to
             arrive at the final approximation.

     Inputs: iterations - the number of terms to add and subtract out, then
             divide by four to approximate pi.

    Outputs: The approximation of pi for the number of terms inputted.
*******************************************************************************/
double leibniz_pi(int iterations)
{
  int i = 1;
  double denominator = 3.0;
  double numerator = 1.0;
  double qtrpisumh;     /* holder for the qtrpisum calc. for current fraction */
  double qtrpisum = 1.0;   /* the approx. for pi/4 for # completed iterations */

  while (i < iterations)
    {
      numerator = -numerator;
      qtrpisumh = numerator;
      qtrpisumh /= denominator;
      qtrpisum += qtrpisumh;
      denominator += 2;
      i++;
    }

  return qtrpisum * 4;
}