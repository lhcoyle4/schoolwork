/*************************************************************
**************************************************************
    ECE 300 – Spring 2014

    Louis Coyle
    Homework #: 05

    Copyright DigiPen (USA) Corporation
    All Rights Reserved
**************************************************************
*************************************************************/

#include "lcd.h"

int main(void) {
   // Setup the Clock
   SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_USE_PLL
		         |SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);

   // Initialize the LCD
   LCD_Enable();

   // Draw the flag of Ukraine

   // Make the background a solid yellow
   LCD_Background(LCD_Color(0xFF, 0xD5, 0x00));

   // Draw a blue rectangle on the top half of the screen
   LCD_Rectangle(0, LCD_HEIGHT/2, 320, 120,
		         LCD_Color(0x00, 0x5B, 0xBB));

   return 0;
}
