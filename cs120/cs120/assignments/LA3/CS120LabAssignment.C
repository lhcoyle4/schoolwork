#include<stdio.h>
#include<math.h>

int main(void)
 {
  float input1;
  float input2;
  float input3;
    /* Ask user for inputs */
  printf("Enter three inputs between 0 and 9.999: \n");
    /*Read the inputs into the variables */
  scanf("%f %f %f", &input1, &input2, &input3);
    /*Display the input/output header */
  printf("Number      sin      cos      tan      atan\n");
    /*Display the header separator */
  printf("-------------------------------------------\n");
    /*Display input1 and calculated results */
  printf("%.5f %8.3f %8.3f %8.3f %8.3f\n", input1, sin(input1), cos(input1),
         tan(input1), atan(input1));
    /*Display input2 and calculated results */
  printf("%.5f %8.3f %8.3f %8.3f %8.3f\n", input2, sin(input2), cos(input2),
         tan(input2), atan(input2));
    /*Display input3 and calculated results */
  printf("%.5f %8.3f %8.3f %8.3f %8.3f\n", input3, sin(input3), cos(input3),
         tan(input3), atan(input3));
  printf("\n");
  return 0;
}
