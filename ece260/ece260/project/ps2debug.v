/*****************************************************************************/
/*!
* \file   ps2.v
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: ECE260
* \par    Final Project
* \date   04/17/14
* 
* \brief
* This file contains the implementation of the top-level ps2 module for the
* final project.
*
* Hours spent on this section: 4.
*/
/*****************************************************************************/

module ps2(CLOCK_50, PS2_CLK, PS2_DAT, LCD_ON, LCD_BLON, LCD_EN, 
			  LCD_RS, LCD_DATA, LCD_RW);
			//, HEX0, HEX1, HEX4, HEX5, GPIO_1);
			
input CLOCK_50, PS2_CLK, PS2_DAT;

/* 
	FOR DEBUGGING
output wire [6:0] HEX0;
output wire [6:0] HEX1;
output wire [6:0] HEX4;
output wire [6:0] HEX5;

output [1:0] GPIO_1;
*/

// two bytes of serial data to be shifted in from PS2_DAT
reg [15:0] PS2Data;
// ascii character data to be sent to lcd module
reg [7:0] ASCIIData;
reg start;
// whether or not the shift key is currently pressed, to be sent to lcd module
reg shiftOn;
// control bit for when ASCIIData is read by lcd module
reg writeData;
// control bit for when PS2Data is processed into
reg processData;
// to keep track of step in the character retrieval process
reg state;
// to control when to start a serial read
reg start;
// to stop the serial read after 16 bits read
reg [3:0] count;
// a lookup table to convert from make/break codes to ascii
reg [7:0] ASCIITable[125:0];
// lsbyte
wire [7:0] PS2Data0;
// msbyte
wire [7:0] PS2Data1;

// least significant byte of make/break code
assign PS2Data0 = PS2Data[7:0];
// most significant byte of make/break code
assign PS2Data1 = PS2Data[15:8];

/*
	FOR DEBUGGING
wire [3:0] PS2DataH;
wire [3:0] PS2DataL;
wire [3:0] ASCIIDataH;
wire [3:0] ASCIIDataL;
	
assign PS2DataL = PS2Data0[3:0];
assign PS2DataH = PS2Data0[7:4];

assign ASCIIDataL = ASCIIData[3:0];
assign ASCIIDataH = ASCIIData[7:4];

assign GPIO_1[0] = PS2_DAT;
assign GPIO_1[1] = PS2_CLK;

segdriver make0(PS2DataL, HEX0);
segdriver make1(PS2DataH, HEX1);
segdriver ascii0(ASCIIDataL, HEX4);
segdriver ascii1(ASCIIDataH, HEX5);
*/ 

lcd lcd16x2(CLOCK_50, LCD_ON, LCD_BLON, LCD_EN, 
				LCD_RS, LCD_DATA, LCD_RW, ASCIIData, 
				writeData);

initial begin
	$readmemh("ASCIITable.hex", ASCIITable, 0, 125);
	start = 0;
	shiftOn = 0;
	count = 0;
	writeData = 0;
end

always @ (posedge PS2_CLK) begin
	if (PS2_DAT == 0 && start == 0) begin
		processData <= 0;
		start <= 1;
	end
	else if (start == 1 && count < 16) begin
		PS2Data <= {PS2_DAT, PS2Data[15:1]};
		count <= count + 1;
	end
	else begin
		//ASCIIData <= ASCIITable[PS2Data];
		processData <= 1;
		start <= 0;
		count <= 0;
	end
end

always @ (*) begin
	if (processData) begin
		// if this was a make code for pressing shift
		if (PS2Data1 == 2'h12 || PS2Data1 == 2'h59) begin
			// then turn shift on and that's it
			shiftOn <= 1;
		end
		// if this was a break code
		else if (PS2Data1 == 2'F0 || PS2Data1 == 2'E0) begin
			// check to see if it was break code for shift key
			if (PS2Data0 == 2'h12 || PS2Data0 == 2'h59) begin
				// if so, turn shift off
				shiftOn <= 0;
			end
		
		end
		// otherwise, it was a make code, so convert to ascii and write to LCD
		else begin
			// if shift is on, shift-up the character first
			if (shiftOn) begin
				PS2Data1 <= PS2Data1 + 2'h30;
			end
			// convert the make code to ascii for the lcd module
			ASCIIData <= ASCIITable[PS2Data1];
			// tell the lcd module to read the character
			writeData <= 1;
			// and allow a new character to be processed
			processData <= 0;
		end
	end
end

endmodule