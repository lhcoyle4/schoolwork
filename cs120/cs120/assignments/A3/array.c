/*******************************************************************************
filename    array.c
author      Louis Coyle II
DP email    louis.coyleii@digipen.edu
course      CS120
section     A
assignment  3
due date    10/31/2012

Brief Description:
  The program will manipulate arrays in several different ways. This will
  include reversing, adding, scalar multiply, a dot product, and a cross
  product of given arrays.

*******************************************************************************/

/*******************************************************************************
   Function: reverse_array

Description: Given an array, reverse the order of the elements in the array.

     Inputs: a[] - Array for which order of elements will be reversed.
            size - The number of elements in the array. 

    Outputs: None. Will put the reversed array back into a[].
*******************************************************************************/
void reverse_array(int a[], int size)
{ 
  int i;                                                  /* for loop counter */
                       
  for (i = 0; i < (size / 2); i++)
  {
    int elementh;     /* holder for the element to be changed.                */
    elementh = a[i];  /* store original value for a[i] as it will be changed. */
    a[i] = a[size - 1 - i];  /* set first element to last, 2nd:2ndtolast etc. */
      /* set last element to original value of first, 2ndtolast:2nd etc.      */
    a[size - 1 - i] = elementh;
  }
} 

/*******************************************************************************
   Function: add_arrays

Description: Given three arrays, add the elements of the first two arrays and
             put the sum in the third array.

     Inputs: a[] - The first array to use elements from as addition terms.
             b[] - The second array to use elements from as addition terms.
             c[] - The array to put the sum of the elements from a[] and b[] in.
            size - The number of elements for the arrays (all the same).

    Outputs: None. Will put the result from the summation into c[].
*******************************************************************************/
void add_arrays(const int a[], const int b[], int c[], int size)
{
  int i;                                                  /* for loop counter */

  for (i = 0; i < size; i++)
  {
   /* set the respective c element to sum of a and b's corresponding elements */
    c[i] = a[i] + b[i]; 
  }
}

/*******************************************************************************
   Function: scalar_multiply

Description: Given an array and a multiplier, multiply each element by the
             multiplier.

     Inputs: a[] - Array for which elements will be multiplied by multiplier.
            size - Size of the array a[].
      multiplier - The value to multiply each element of a[] by.

    Outputs: None. The product of the multiplication will overwrite the original
             value of each element.
*******************************************************************************/
void scalar_multiply(int a[], int size, int multiplier)
{
  int i;                                                  /* for loop counter */

  for (i = 0; i < size; i++)
  {
    a[i] = a[i] * multiplier; /* multiply each element in array by multiplier */
  }
}

/*******************************************************************************
   Function: dot_product

Description: Given two arrays, determine the dot product (multiply each
             corresponding element and sum their products) and return the value.

     Inputs: a[] - The first array to use elements from as multiplication terms.
             b[] - The second array to use elements from as multiplication 
                   terms.
            size - The number of elements for the arrays (both the same).

    Outputs: The sum (int) of all of the products of the elements of the arrays.
*******************************************************************************/
int dot_product(const int a[], const int b[], int size)
{
  int i;                /* for loop counter                                   */
  int dotp = 0;         /* sum of products of elements, to be returned at end */

  for (i = 0; i < size; i++)
  {
    dotp += a[i] * b[i];    /* multiply elements from a and b and add to dotp */
  }

  return dotp;    /* return sum of all products of elements of arrays a and b */
}

/*******************************************************************************
   Function: cross_product

Description: Given three arrays, determine the cross product of the first two.
             The cross product is another array and will be placed into the
             third array. The size of each array will always be three.

     Inputs: a[] - The first array to use elements from in the cross product.
             b[] - The second array to use elements from in the cross product.
             c[] - The array to place the result of the cross product into.

    Outputs: None. The result of the cross product will be in c[].
*******************************************************************************/
void cross_product(const int a[], const int b[], int c[])
{
    /* compute the cross product and set c[] to results                       */
  c[0] = (a[1] * b[2]) - (a[2] * b[1]);
  c[1] = -((b[2] * a[0]) - (b[0] * a[2]));
  c[2] = (a[0] * b[1]) - (a[1] * b[0]);
}
