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

/*************************************************************
 *************************************************************

    The code below was written by Steven Prickett:
    http://users.ece.utexas.edu/~valvano/arm/SSD2119.c

 *************************************************************
 ************************************************************/

// define command codes
#define SSD2119_DEVICE_CODE_READ_REG  0x00
#define SSD2119_OSC_START_REG         0x00
#define SSD2119_OUTPUT_CTRL_REG       0x01
#define SSD2119_LCD_DRIVE_AC_CTRL_REG 0x02
#define SSD2119_PWR_CTRL_1_REG        0x03
#define SSD2119_DISPLAY_CTRL_REG      0x07
#define SSD2119_FRAME_CYCLE_CTRL_REG  0x0B
#define SSD2119_PWR_CTRL_2_REG        0x0C
#define SSD2119_PWR_CTRL_3_REG        0x0D
#define SSD2119_PWR_CTRL_4_REG        0x0E
#define SSD2119_GATE_SCAN_START_REG   0x0F
#define SSD2119_SLEEP_MODE_REG        0x10
#define SSD2119_ENTRY_MODE_REG        0x11
#define SSD2119_GEN_IF_CTRL_REG       0x15
#define SSD2119_PWR_CTRL_5_REG        0x1E
#define SSD2119_RAM_DATA_REG          0x22
#define SSD2119_FRAME_FREQ_REG        0x25
#define SSD2119_VCOM_OTP_1_REG        0x28
#define SSD2119_VCOM_OTP_2_REG        0x29
#define SSD2119_GAMMA_CTRL_1_REG      0x30
#define SSD2119_GAMMA_CTRL_2_REG      0x31
#define SSD2119_GAMMA_CTRL_3_REG      0x32
#define SSD2119_GAMMA_CTRL_4_REG      0x33
#define SSD2119_GAMMA_CTRL_5_REG      0x34
#define SSD2119_GAMMA_CTRL_6_REG      0x35
#define SSD2119_GAMMA_CTRL_7_REG      0x36
#define SSD2119_GAMMA_CTRL_8_REG      0x37
#define SSD2119_GAMMA_CTRL_9_REG      0x3A
#define SSD2119_GAMMA_CTRL_10_REG     0x3B
#define SSD2119_V_RAM_POS_REG         0x44
#define SSD2119_H_RAM_START_REG       0x45
#define SSD2119_H_RAM_END_REG         0x46
#define SSD2119_X_RAM_ADDR_REG        0x4E
#define SSD2119_Y_RAM_ADDR_REG        0x4F
#define ENTRY_MODE_DEFAULT 0x6830


#define LCD_HEIGHT 240
#define LCD_WIDTH  320

// entry mode macros
#define HORIZ_DIRECTION 0x28
#define VERT_DIRECTION 0x20
#define ENTRY_MODE_DEFAULT 0x6830
#define MAKE_ENTRY_MODE(x) ((ENTRY_MODE_DEFAULT & 0xFF00) | (x))

// bit-banded addresses for port stuff
#define LCD_RD_PIN       (*((volatile unsigned long *)0x40004040))     // PA4
#define LCD_WR_PIN       (*((volatile unsigned long *)0x40004080))     // PA5
#define LCD_RS_PIN       (*((volatile unsigned long *)0x40004100))     // PA6
#define LCD_CS_PIN       (*((volatile unsigned long *)0x40004200))     // PA7
#define LCD_WR_RS        (*((volatile unsigned long *)0x40004180))     //
#define LCD_CTRL         (*((volatile unsigned long *)0x400043C0))     // PA4-7
#define LCD_DATA         (*((volatile unsigned long *)0x400053FC))     // PB0-7

// Enables GPIO pins needed for the LCD
void LCD_GPIOEnable(void){
    unsigned long wait = 0;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
    wait++;                               // wait for port activation
    wait++;                               // wait for port activation
    GPIO_PORTB_DIR_R   |= 0xFF;           // make PB0-7 outputs
    GPIO_PORTB_AFSEL_R &= ~0xFF;          // disable alternate functions
    GPIO_PORTB_DEN_R   |= 0xFF;           // enable digital I/O on PB0-7

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
    wait++;                               // wait for port activation
    wait++;                               // wait for port activation
    GPIO_PORTA_DIR_R   |= 0xF0;           // make PA4-7 outputs
    GPIO_PORTA_AFSEL_R &= ~0xF0;          // disable alternate functions
    GPIO_PORTA_DEN_R   |= 0xF0;           // enable digital I/O on PA4-7

    LCD_CTRL = 0xFF;

    for (wait = 0; wait < 500; wait++) {}
}

// Writes address of command register to access to LCD
void LCD_WriteCommand(unsigned char data){
    // Write 0 as MSB of command data
    LCD_DATA = 0x00;

    // Set CS, WR, RS low
    LCD_CTRL = 0x10;

    // Set WR and RS high
    LCD_WR_RS = 0xFF;

    // Write data as LSB of command data
    LCD_DATA = data;

    // Set WR and RS low
    LCD_WR_RS = 0x00;

    // Set CS, WR, RS high
    LCD_CTRL = 0xF0;
}

// Writes data to the LCD, after selecting command register
void LCD_WriteData(unsigned short data){
    // Write MSB to LCD data bus
    LCD_DATA = (data >> 8);

    // Set CS, WR low
    LCD_CTRL = 0x50;

    // Set WR high
    LCD_WR_PIN = 0xFF;

    // Write LSB to LCD data bus
    LCD_DATA = data;

    // Set WR low
    LCD_WR_PIN = 0x00;

    // Set CS, WR high
    LCD_CTRL = 0xF0;
}

//
void LCD_Enable(void){
    unsigned long count = 0;

    LCD_GPIOEnable();

    // Enter sleep mode (if we are not already there).
    LCD_WriteCommand(SSD2119_SLEEP_MODE_REG);
    LCD_WriteData(0x0001);

    // Set initial power parameters.
    LCD_WriteCommand(SSD2119_PWR_CTRL_5_REG);
    LCD_WriteData(0x00BA);
    LCD_WriteCommand(SSD2119_VCOM_OTP_1_REG);
    LCD_WriteData(0x0006);

    // Start the oscillator.
    LCD_WriteCommand(SSD2119_OSC_START_REG);
    LCD_WriteData(0x0001);

    // Set pixel format and basic display orientation (scanning direction).
    LCD_WriteCommand(SSD2119_OUTPUT_CTRL_REG);
    LCD_WriteData(0x30EF);
    LCD_WriteCommand(SSD2119_LCD_DRIVE_AC_CTRL_REG);
    LCD_WriteData(0x0600);

    // Exit sleep mode.
    LCD_WriteCommand(SSD2119_SLEEP_MODE_REG);
    LCD_WriteData(0x0000);

    // Delay 30mS
    for (count = 0; count < 200000; count++) {}

    // Configure pixel color format and MCU interface parameters.
    LCD_WriteCommand(SSD2119_ENTRY_MODE_REG);
    LCD_WriteData(ENTRY_MODE_DEFAULT);

    // Enable the display.
    // You mentioned that this command was incorrect,
    // however the only problem that I could see was that
    // BASEE was not being enabled to allow a lit base image
    // for the display. Turning BASEE on makes the command
    // 0x0133, but the display functions just the same at
    // this level of use with either command.
    LCD_WriteCommand(SSD2119_DISPLAY_CTRL_REG);
    LCD_WriteData(0x0033);

    // Set VCIX2 voltage to 6.1V.
    LCD_WriteCommand(SSD2119_PWR_CTRL_2_REG);
    LCD_WriteData(0x0005);

    // Configure gamma correction.
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_1_REG);
    LCD_WriteData(0x0000);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_2_REG);
    LCD_WriteData(0x0400);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_3_REG);
    LCD_WriteData(0x0106);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_4_REG);
    LCD_WriteData(0x0700);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_5_REG);
    LCD_WriteData(0x0002);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_6_REG);
    LCD_WriteData(0x0702);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_7_REG);
    LCD_WriteData(0x0707);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_8_REG);
    LCD_WriteData(0x0203);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_9_REG);
    LCD_WriteData(0x1400);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_10_REG);
    LCD_WriteData(0x0F03);

    // Configure Vlcd63 and VCOMl.
    LCD_WriteCommand(SSD2119_PWR_CTRL_3_REG);
    LCD_WriteData(0x0007);
    LCD_WriteCommand(SSD2119_PWR_CTRL_4_REG);
    LCD_WriteData(0x3100);

    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    LCD_WriteCommand(SSD2119_V_RAM_POS_REG);
    LCD_WriteData((LCD_HEIGHT-1) << 8);
    LCD_WriteCommand(SSD2119_H_RAM_START_REG);
    LCD_WriteData(0x0000);
    LCD_WriteCommand(SSD2119_H_RAM_END_REG);
    LCD_WriteData(LCD_WIDTH-1);
    LCD_WriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCD_WriteData(0x00);
    LCD_WriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCD_WriteData(0x00);

    // Clear the contents of the display buffer.
    LCD_WriteCommand(SSD2119_RAM_DATA_REG);
    for(count = 0; count < (320 * 240); count++)
    {
        LCD_WriteData(0x0000); //
    }
}

// Draws a rectangle at position x, y, with size width,height and color
void LCD_Rectangle(unsigned short x, unsigned short y,
				  short width, short height, unsigned short color){
    int i, j;

    for (i = 0; i < height; i++) {
        // Set the X address of the display cursor.
        LCD_WriteCommand(SSD2119_X_RAM_ADDR_REG);
        LCD_WriteData(x);

        // Set the Y address of the display cursor.
        LCD_WriteCommand(SSD2119_Y_RAM_ADDR_REG);
        LCD_WriteData(y + i);

        LCD_WriteCommand(SSD2119_RAM_DATA_REG);
        for (j = 0; j < width; j++) {
            LCD_WriteData(color);
        }
    }

}

// Sets the background color of the screen
void LCD_Background(unsigned short color){
	LCD_Rectangle(0, 0, LCD_WIDTH, LCD_HEIGHT, color);
}

// Converts 24-bit RGB to 16-bit 5-6-5 RGB
unsigned short LCD_Color(unsigned char r, unsigned char g, unsigned char b){
    return ((r>>3)<<11) | ((g>>2)<<5) | (b>>3);
}
