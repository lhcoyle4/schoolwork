/*****************************************************************************/
/*!
* \file   lcd.v
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: ECE260
* \par    Final Project
* \date   04/17/14
* 
* \brief
* This file contains the implementation of the lcd module for the final
* project.
*
* Hours spent on this assignment: 4 - 6 (initial) + 4
* 
* Note: I modeled my instruction table after the one in the DE2_Default code.
*/
/*****************************************************************************/

module lcd(CLOCK_50, LCD_ON, LCD_BLON, LCD_EN, 
			  LCD_RS, LCD_DATA, LCD_RW, KEY, ASCIIData, 
			  writeData);

input CLOCK_50;

input [7:0] ASCIIData;
input writeData;
input [1:0] KEY;

// LCD pins
output LCD_ON;
output LCD_BLON;
output LCD_EN;
output LCD_RS;
output LCD_RW;
output [7:0] LCD_DATA;

// turn the LCD and its backlight on
assign LCD_ON = 1'b1;
assign LCD_BLON = 1'b1;

wire RESET_delay;
wire myLCD_RS;
wire myLCD_START;
wire [7:0] myLCD_DATA;
wire myLCD_DONE;

power_on_reset_delay por_d(.inClock(CLOCK_50), 
.outResetNeg(RESET_delay), .inReset(KEY[0]));

message_write msg_w(
			.inClock(CLOCK_50),
			.inResetNeg(RESET_delay),
			.LCD_EN(LCD_EN),
			.LCD_RS(LCD_RS),
			.LCD_RW(LCD_RW),
			.LCD_DATA(LCD_DATA),
			.inASCIIData(ASCIIData),
			.inWriteData(writeData));

endmodule

// outResetNeg connected to RESET_DELAY
// goes to 1'b1 20ms after power on
module power_on_reset_delay(inClock, outResetNeg, inReset);
input inClock;
input inReset;
output reg outResetNeg;
reg [19:0] Counter;

always @(posedge inClock) begin
	if (!inReset) begin
		Counter <= 0;
	end
	if (Counter < 20'hEFFFE) begin
		Counter <= Counter + 1;
		outResetNeg <= 1'b0;
	end
	else
		outResetNeg <= 1'b1;
end

endmodule

module lcd_driver(
					inClock, 
					inResetNeg, 
					inRS, 
					inStart, 
					inData, 
					outDone, 
					LCD_EN, 
					LCD_RS, 
					LCD_RW, 
					LCD_DATA	);

input inClock, inResetNeg;
input inRS, inStart;
input [7:0] inData;

output reg outDone;

// LCD pins
output reg LCD_EN;
output LCD_RS;
output LCD_RW;
output [7:0] LCD_DATA;

reg [4:0] Counter;
reg [1:0] state;
reg prevStart;
reg Start;

// Set to only write, get RS from message writer
assign LCD_RS = inRS;
assign LCD_RW = 0;
assign LCD_DATA = inData;

parameter CLOCK_DIVIDER = 16;

always @ (posedge inClock or negedge inResetNeg) begin
	if (!inResetNeg) begin
		outDone <= 1'b0;
		LCD_EN <= 1'b0;
		Counter <= 0;
		state <= 0;
		prevStart <= 1'b0;
		Start <= 1'b0;
	end
	else begin
		prevStart <= inStart;
		if (prevStart == 0 && inStart == 1) begin
			Start <= 1'b1;
			outDone <= 1'b0;
		end
		if (Start) begin
			case(state)
			0: state <= 1;
			1: begin
					LCD_EN <= 1'b1;
					state <= 2;
				end
			2: begin
					// EN pulse width length > 230 ns (~320ns)
					if (Counter < CLOCK_DIVIDER) begin
						Counter <= Counter + 1;
					end
					else begin
						state <= 3;
					end
				end
			3: begin
					outDone <= 1'b1;
					LCD_EN <= 1'b0;
					Counter <= 0;
					state <= 0;
					Start <= 1'b0;
				end
			endcase
		end
	end
end

endmodule


module message_write(
						inClock, 
						inResetNeg,
						inASCIIData,
						inWriteData,
						LCD_DATA,
						LCD_EN,
						LCD_RS,
						LCD_RW );
						
input inClock, inResetNeg;
input [7:0] inASCIIData;
input inWriteData;

output LCD_EN, LCD_RS, LCD_RW;
output [7:0] LCD_DATA;

wire inDone;

reg [5:0] 	instTableIndex;
reg [8:0] 	instTableData;
reg [8:0] 	fnTableData;
reg [1:0] 	state;
reg [17:0] 	delay;
reg [7:0]   address;
reg			prevWriteData;
reg 			myLCD_RS;
reg			myLCD_START;
reg [7:0]   myLCD_DATA;

parameter LCD_INIT = 0;
parameter INST_TABLE_SIZE = 5;
parameter UP_ARROW = 8'h11;
parameter DOWN_ARROW = 8'h12;
parameter LEFT_ARROW = 8'h13;
parameter RIGHT_ARROW = 8'h14;
parameter ENTER = 8'h0D;
parameter ESCAPE = 8'h1B;
parameter FUNCTION_SET =  9'h038; 
parameter DISPLAY_ON =    9'h00F; // change from 00C to 00F to turn on blinking cursor
parameter DISPLAY_CLEAR = 9'h001;
parameter ENTRY_MODE =    9'h006;
parameter NEXT_LINE =	  9'h0C0;
parameter SET_DRAM = 	  9'h080;

always @ (posedge inClock or negedge inResetNeg) begin
	if (!inResetNeg) begin
		instTableIndex <= 0;
		state <= 0;
		delay <= 0;
		prevWriteData <= 0;
		address = 8'h00;
		myLCD_START <= 0;
		myLCD_DATA <= 0;
		myLCD_RS <= 0;
	end
	else begin
		prevWriteData <= inWriteData;
		case (state)
		0: begin
				// set the data/instruction switch (RS)
				// and the data/instruction code based on the info at current index
				if (instTableIndex < INST_TABLE_SIZE) begin
					myLCD_DATA <= instTableData[7:0];
					myLCD_RS <= instTableData[8];
					myLCD_START <= 1;
					state <= 1;
				end
				// or from the ps2 module, warranting that data is a character
				if (inWriteData && !prevWriteData && inASCIIData > 8'h1F && inASCIIData < 8'h7F) begin
					myLCD_DATA <= inASCIIData;
					myLCD_START <= 1;
					myLCD_RS <= 1;
					if (address < 8'h0F || (address > 8'h3F && address < 8'h4F)) begin
						address = address + 8'h01;
					end
					state <= 1;
				end
				// or based on the info in the function table indexed by 
				// the data from ps2 module
				if (inWriteData && !prevWriteData && (inASCIIData < 8'h20 || inASCIIData == 8'h7F)) begin
					case (inASCIIData)
						UP_ARROW:
						begin
							if (address > 8'h3F && address < 8'h50) begin
								address = address - 8'h40;
							end
							myLCD_DATA <= SET_DRAM + address;
						end
						DOWN_ARROW:
						begin
							if (address < 8'h10) begin
								address = address + 8'h40;
							end
							myLCD_DATA <= SET_DRAM + address;
						end
						LEFT_ARROW:
						begin
							if ((address > 8'h00 && address < 8'h10) || (address > 8'h40 && address < 8'h50)) begin
								address = address - 8'h01;
							end
							myLCD_DATA <= SET_DRAM + address;
						end
						RIGHT_ARROW:
						begin
							if (address < 8'h0F || (address > 8'h3F && address < 8'h4F)) begin
								address = address + 8'h01;
							end
							myLCD_DATA <= SET_DRAM + address;
						end
						ENTER: 
						begin
							address = 8'h40;
							myLCD_DATA <= NEXT_LINE;
						end
						ESCAPE: 
						begin
							address = 8'h00;
							myLCD_DATA <= DISPLAY_CLEAR;
						end
						default: myLCD_DATA <= 0;
					endcase
					myLCD_RS <= 0;
					myLCD_START <= 1;
					state <= 1;				
				end
			end
		1: begin
				// wait for the driver to be done sending the data
				// only go to next state once it's done
				if (inDone) begin
					myLCD_START <= 0;
					state <= 2;
				end
			end
		2: begin
				// just always delay a few ms between instructions
				// to account for setup delays and to ensure EN cycle time > 500ns
				// still will only take ~170ms to write the whole screen
				if (delay < 18'h3FFF3) begin
					delay <= delay + 1;
				end
				else begin
					delay <= 0;
					state <= 3;
				end
			end
		3: begin
				// increment index to read the next data/instruction into
				// the data registers on next iteration of FSM
				if (instTableIndex < INST_TABLE_SIZE) begin
					instTableIndex <= instTableIndex + 1;
				end
				state <= 0;
			end
		endcase
	end
end

always begin
	case(instTableIndex)
		// Init instructions
		LCD_INIT + 0: instTableData <= FUNCTION_SET;
		LCD_INIT + 1: instTableData <= DISPLAY_ON;
		LCD_INIT + 2: instTableData <= DISPLAY_CLEAR;
		LCD_INIT + 3: instTableData <= ENTRY_MODE;
		LCD_INIT + 4: instTableData <= SET_DRAM;
		default: instTableData <= 0;
	endcase
end

lcd_driver lcd_d(
		.inClock(inClock), 
		.inResetNeg(inResetNeg), 
		.inRS(myLCD_RS), 
		.inStart(myLCD_START), 
		.inData(myLCD_DATA), 
		.outDone(inDone),
		.LCD_EN(LCD_EN),
		.LCD_RS(LCD_RS),
		.LCD_RW(LCD_RW),
		.LCD_DATA(LCD_DATA)	);

endmodule
