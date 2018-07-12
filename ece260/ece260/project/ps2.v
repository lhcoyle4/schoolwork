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
			  LCD_RS, LCD_DATA, LCD_RW,HEX0, HEX1, HEX4, HEX5, GPIO_1, LEDR, KEY);
			
input CLOCK_50, PS2_CLK, PS2_DAT;
input [1:0] KEY;

//	FOR DEBUGGING
output wire [6:0] HEX0;
output wire [6:0] HEX1;
output wire [6:0] HEX4;
output wire [6:0] HEX5;

output [1:0] GPIO_1;

output [1:0] LEDR;
//

// LCD pins
output LCD_ON;
output LCD_BLON;
output LCD_EN;
output LCD_RS;
output LCD_RW;
output [7:0] LCD_DATA;

reg [15:0] PS2Data; // two bytes of serial data to be shifted in from PS2_DAT
reg [7:0] ASCIIData; // ascii character data to be sent to lcd module
reg start; // to start reading when a start bit of zero is read from PS2_DAT
reg shiftOn; // whether or not the shift key is currently pressed, to be sent to lcd module
reg writeData; // control bit for when ASCIIData is read by lcd module
reg processData; // control bit for when PS2Data is processed into
reg state; // to keep track of step in the character retrieval process
wire resetNeg; // is 0 when the device is in power on reset delay interval
reg [3:0] count; // to stop the serial read after 16 bits read
reg [7:0] ASCIITable[125:0]; // a lookup table to convert from make/break codes to ascii
reg [7:0] shiftASCIITable[125:0]; // a lookup table to convert from make/break codes to uppercase ascii
wire [7:0] PS2Data0; // lsbyte
wire [7:0] PS2Data1; // msbyte

// least significant byte of make/break code
assign PS2Data0 = PS2Data[7:0];
// most significant byte of make/break code
assign PS2Data1 = PS2Data[15:8];

//	FOR DEBUGGING
wire [3:0] PS2DataH;
wire [3:0] PS2DataL;
wire [3:0] ASCIIDataH;
wire [3:0] ASCIIDataL;
	
assign PS2DataL = PS2Data1[3:0];
assign PS2DataH = PS2Data1[7:4];

assign ASCIIDataL = ASCIIData[3:0];
assign ASCIIDataH = ASCIIData[7:4];

assign GPIO_1[0] = PS2_DAT;
assign GPIO_1[1] = PS2_CLK;

assign LEDR[0] = shiftOn;

segdriver make0(PS2DataL, HEX0);
segdriver make1(PS2DataH, HEX1);
segdriver ascii0(ASCIIDataL, HEX4);
segdriver ascii1(ASCIIDataH, HEX5);
//

ps2_power_on_reset_delay por_d(.inClock(CLOCK_50), 
.outResetNeg(resetNeg));

lcd lcd16x2(CLOCK_50, LCD_ON, LCD_BLON, LCD_EN, 
				LCD_RS, LCD_DATA, LCD_RW, KEY, ASCIIData, 
				writeData);

initial begin
	$readmemh("ASCIITable.hex", ASCIITable, 0, 120);
	$readmemh("shiftASCIITable.hex", shiftASCIITable, 0, 120);
	start = 0;
	shiftOn = 0;
	count = 0;
	writeData = 0;
end

always @ (posedge PS2_CLK or negedge resetNeg) begin
	if (!resetNeg) begin
		start <= 0;
		shiftOn <= 0;
		count <= 0;
		writeData <= 0;
	end
	else if (PS2_DAT == 0 && start == 0) begin
		writeData <= 0;
		start <= 1;
	end
	else if (start == 1 && count < 8) begin
		PS2Data <= {PS2_DAT, PS2Data[15:1]};
		count <= count + 1;
	end
	else if (start == 1) begin
		//ASCIIData <= ASCIITable[PS2Data];
		// if the data was a break code (because the shift register is only 16-bit,
		// then we only care to look for a F0, never E0)
		if (PS2Data1 == 8'hF0 || PS2Data0 == 8'hF0) begin
			// then, check to see if it was break code for shift key
			if (PS2Data1 == 8'h12 || PS2Data1 == 8'h59) begin
				// turn shift off to finish processing data
				shiftOn <= 0;
			end
		end
		// if the data was a make code for pressing shift
		else if (PS2Data1 == 8'h12 || PS2Data1 == 8'h59) begin
			// then turn shift on and that's it
			shiftOn <= 1;
		end
		// otherwise, it was a make code, so convert to ascii and write to LCD
		else begin
			// if shift is pressed, shift-up the character first
			if (shiftOn) begin
				ASCIIData <= shiftASCIITable[PS2Data1];
			end
			// convert the make code to ascii for the lcd module
			else begin
				ASCIIData <= ASCIITable[PS2Data1];
			end
			// tell the lcd module to read the character
			writeData <= 1;
		end
		start <= 0;
		count <= 0;
	end
	else begin
		start <= 0;
		count <= 0;
	end
end

endmodule

// outResetNeg connected to RESET_DELAY
// goes to 1'b1 after LCD module has been initialized (~100ms)
module ps2_power_on_reset_delay(inClock, outResetNeg);
input inClock;
output reg outResetNeg;
reg [23:0] Counter;

always @(posedge inClock) begin
	if (Counter < 24'h59FFF4) begin
		Counter <= Counter + 1;
		outResetNeg <= 1'b0;
	end
	else
		outResetNeg <= 1'b1;
end
endmodule