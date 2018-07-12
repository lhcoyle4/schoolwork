// Steven Prickett
//
// Runs on LM4F120
// Driver for the SSD2119 interface on a Kentec 320x240x16 BoosterPack
// - Uses all 8 bits on PortB for writing data to LCD 
//   and bits 4-7 on Port A for control signals
// - Adapted from original Kentec320x240x16_ssd2119_8bit.c driver by TI

#include "lm4f120h5qr.h"

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

// ************** LCD_GPIOInit ****************************
// - Initializes Port B to be used as the data bus and
//   Port A 4-7 as controller signals
// ********************************************************
void LCD_GPIOInit(void){
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

// ************** LCD_WriteCommand ************************
// - Writes a command to the LCD controller
// ********************************************************
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

// ************** LCD_WriteData ***************************
// - Writes data to the LCD controller
// ********************************************************
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

// ************** LCD_Init ********************************
// - Initializes the LCD
// ********************************************************
void LCD_Init(void){
    unsigned long count = 0;
    
    LCD_GPIOInit();

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
        LCD_WriteData(0x0000);
    }
}

// ************** convertColor ****************************
// - converts 8-8-8 RGB values into 5-6-5 RGB
// ********************************************************
// 
unsigned short convertColor(unsigned char r, unsigned char g, unsigned char b){
    return ((r>>3)<<11) | ((g>>2)<<5) | (b>>3);
}

// ************** LCD_DrawPixel ***************************
// - Draws a 16-bit pixel on the screen
// ********************************************************
void LCD_DrawPixel(unsigned short x, unsigned short y, unsigned short color)
{
    // Set the X address of the display cursor.
    LCD_WriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCD_WriteData(x);

    // Set the Y address of the display cursor.
    LCD_WriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCD_WriteData(y);

    // Write the pixel value.
    LCD_WriteCommand(SSD2119_RAM_DATA_REG);
    LCD_WriteData(color);
}

// ************** LCD_DrawPixelRGB ************************
// - Draws a 16-bit representation of a 24-bit color pixel
// ********************************************************
void LCD_DrawPixelRGB(unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b){
    LCD_DrawPixel(x, y, convertColor(r, g, b));
}

// ************** LCD_RectDraw ****************************
// - Draws a rectangle at x,y with width, height, and color
// ********************************************************
void LCD_DrawRect(unsigned short x, unsigned short y, short width, short height, unsigned short color){
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

// ************** LCD_ColorFill ***************************
// - Fills the screen with the specified color
// ********************************************************
void LCD_ColorFill(unsigned short color){
    LCD_DrawRect(0, 0, 320, 240, color);
}

int abs(int a){
    if (a < 0) return -a;
    else return a;
}

// ************** LCD_LineDraw ***************************
// - Draws a line using the Bresenham line algrorithm from
//   http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm
// ********************************************************
void LCD_LineDraw(unsigned short startX, unsigned short startY, unsigned short endX, unsigned short endY, unsigned short color){
    int x0 = startX;
    int x1 = endX;
    int y0 = startY;
    int y1 = endY;
	
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;
 
    for(;;){
        LCD_DrawPixel(x0, y0, color);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

