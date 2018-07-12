/*************************************************************
**************************************************************
    ECE 300 – Spring 2014

    Louis Coyle
    Homework #: 05

    Copyright DigiPen (USA) Corporation
    All Rights Reserved
**************************************************************
*************************************************************/

#define LCD_HEIGHT 240
#define LCD_WIDTH  320

#define TARGET_IS_BLIZZARD_RA1 1

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"

void LCD_GPIOEnable(void);

void LCD_WriteCommand(unsigned char data);

void LCD_WriteData(unsigned short data);

void LCD_Enable(void);

void LCD_Rectangle(unsigned short x, unsigned short y,
				  short width, short height, unsigned short color);

void LCD_Background(unsigned short color);

unsigned short LCD_Color(unsigned char r, unsigned char g, unsigned char b);
