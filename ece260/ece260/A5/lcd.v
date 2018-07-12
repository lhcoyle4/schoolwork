/*****************************************************************************/
/*!
* \file   lcd.v
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: ECE260
* \par    Assignment #5
* \date   02/17/14
* 
* \brief
* This file contains the implementation of the necessary modules for the lcd
* assignment.
*
* Hours spent on this assignment: 4 - 6
* 
* Note: I modeled my instruction table after the one in the DE2_Default code.
*/
/*****************************************************************************/

module lcd(CLOCK_50, LCD_ON, LCD_BLON, LCD_EN, LCD_RS, LCD_DATA, 
LCD_RW);

input CLOCK_50;

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

wire RESET_DELAY;
wire myLCD_RS;
wire myLCD_START;
wire [7:0] myLCD_DATA;
wire myLCD_DONE;

power_on_reset_delay por_d(.inClock(CLOCK_50), 
.outResetNeg(RESET_DELAY));

message_write msg_w(
			.inClock(CLOCK_50),
			.inResetNeg(RESET_DELAY),
			.LCD_EN(LCD_EN),
			.LCD_RS(LCD_RS),
			.LCD_RW(LCD_RW),
			.LCD_DATA(LCD_DATA)	);

endmodule


// outResetNeg connected to RESET_DELAY
// goes to 1'b1 20ms after power on
module power_on_reset_delay(inClock, outResetNeg);
input inClock;
output reg outResetNeg;
reg [19:0] Counter;

always @(posedge inClock) begin
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
reg [1:0] State;
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
		State <= 0;
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
			case(State)
			0: State <= 1;
			1: begin
					LCD_EN <= 1'b1;
					State <= 2;
				end
			2: begin
					// EN pulse width length > 230 ns (~320ns)
					if (Counter < CLOCK_DIVIDER) begin
						Counter <= Counter + 1;
					end
					else begin
						State <= 3;
					end
				end
			3: begin
					outDone <= 1'b1;
					LCD_EN <= 1'b0;
					Counter <= 0;
					State <= 0;
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
						LCD_DATA,
						LCD_EN,
						LCD_RS,
						LCD_RW	);
						
input inClock, inResetNeg;

output LCD_EN, LCD_RS, LCD_RW;
output [7:0] LCD_DATA;

wire inDone;

reg [5:0] 	INST_TABLE_INDEX;
reg [8:0] 	INST_TABLE_DATA;
reg [1:0] 	STATE;
reg [17:0] 	DELAY;
reg 			myLCD_RS;
reg			myLCD_START;
reg [7:0]   myLCD_DATA;

parameter LCD_INIT = 0;
parameter LCD_FIRST_LINE = 5;
parameter LCD_NEXT_LINE = LCD_FIRST_LINE + 16;
parameter LCD_SECOND_LINE = LCD_FIRST_LINE + 16 + 1;
parameter INST_TABLE_SIZE = LCD_FIRST_LINE + 32 + 1;
parameter FUNCTION_SET =  9'h038;
parameter DISPLAY_ON =    9'h00C;
parameter DISPLAY_CLEAR = 9'h001;
parameter ENTRY_MODE =    9'h006;
parameter NEXT_LINE =	  9'h0C0;
parameter SET_DRAM = 	  9'h080;

// message to be written to LCD
// manually padded with spaces at the end, as by default it would be padded
// from the front, causing the message to start 4 characters into the screen.
reg [127:0] message1 = " Hello world!   ";
reg [127:0] message2 = "                ";

always @ (posedge inClock or negedge inResetNeg) begin
	if (!inResetNeg) begin
		INST_TABLE_INDEX <= 0;
		STATE <= 0;
		DELAY <= 0;
		myLCD_START <= 0;
		myLCD_DATA <= 0;
		myLCD_RS <= 0;
	end
	else begin
		if (INST_TABLE_INDEX < INST_TABLE_SIZE) begin
			case (STATE)
			0: begin
					// set the data/instruction switch (RS)
					// and the data/instruction code based on the info at current index
					myLCD_DATA <= INST_TABLE_DATA[7:0];
					myLCD_RS <= INST_TABLE_DATA[8];
					myLCD_START <= 1;
					STATE <= 1;
				end
			1: begin
					// wait for the driver to be done sending the data
					// only go to next state once it's done
					if (inDone) begin
						myLCD_START <= 0;
						STATE <= 2;
					end
				end
			2: begin
					// just always delay > 5ms between instructions
					// to account for setup delays and to ensure EN cycle time > 500ns
					// still will only take ~170ms to write the whole screen
					if (DELAY < 18'h3FFF3) begin
						DELAY <= DELAY + 1;
					end
					else begin
						DELAY <= 0;
						STATE <= 3;
					end
				end
			3: begin
					// increment index to read the next data/instruction into
					// the data registers on next iteration of FSM
					INST_TABLE_INDEX <= INST_TABLE_INDEX + 1;
					STATE <= 0;
				end
			endcase
		end
	end
end

always begin
	case(INST_TABLE_INDEX)
		// Init instructions
		LCD_INIT + 0: INST_TABLE_DATA <= FUNCTION_SET;
		LCD_INIT + 1: INST_TABLE_DATA <= DISPLAY_ON;
		LCD_INIT + 2: INST_TABLE_DATA <= DISPLAY_CLEAR;
		LCD_INIT + 3: INST_TABLE_DATA <= ENTRY_MODE;
		LCD_INIT + 4: INST_TABLE_DATA <= SET_DRAM;
		// First line characters (write instructions)
		LCD_FIRST_LINE + 0: INST_TABLE_DATA <= {1'b1, message1[127:120]};
		LCD_FIRST_LINE + 1: INST_TABLE_DATA <= {1'b1, message1[119:112]};
		LCD_FIRST_LINE + 2: INST_TABLE_DATA <= {1'b1, message1[111:104]};
		LCD_FIRST_LINE + 3: INST_TABLE_DATA <= {1'b1, message1[103:96]};
		LCD_FIRST_LINE + 4: INST_TABLE_DATA <= {1'b1, message1[95:88]};
		LCD_FIRST_LINE + 5: INST_TABLE_DATA <= {1'b1, message1[87:80]};
		LCD_FIRST_LINE + 6: INST_TABLE_DATA <= {1'b1, message1[79:72]};
		LCD_FIRST_LINE + 7: INST_TABLE_DATA <= {1'b1, message1[71:64]};
		LCD_FIRST_LINE + 8: INST_TABLE_DATA <= {1'b1, message1[63:56]};
		LCD_FIRST_LINE + 9: INST_TABLE_DATA <= {1'b1, message1[55:48]};
		LCD_FIRST_LINE + 10: INST_TABLE_DATA <= {1'b1, message1[47:40]};
		LCD_FIRST_LINE + 11: INST_TABLE_DATA <= {1'b1, message1[39:32]};
		LCD_FIRST_LINE + 12: INST_TABLE_DATA <= {1'b1, message1[31:24]};
		LCD_FIRST_LINE + 13: INST_TABLE_DATA <= {1'b1, message1[23:16]};
		LCD_FIRST_LINE + 14: INST_TABLE_DATA <= {1'b1, message1[15:8]};
		LCD_FIRST_LINE + 15: INST_TABLE_DATA <= {1'b1, message1[7:0]};
		// Next line instruction
		LCD_NEXT_LINE: INST_TABLE_DATA <= NEXT_LINE;
		// Second line characters (write instructions)
		LCD_SECOND_LINE + 0: INST_TABLE_DATA <= {1'b1, message2[127:120]};
		LCD_SECOND_LINE + 1: INST_TABLE_DATA <= {1'b1, message2[119:112]};
		LCD_SECOND_LINE + 2: INST_TABLE_DATA <= {1'b1, message2[111:104]};
		LCD_SECOND_LINE + 3: INST_TABLE_DATA <= {1'b1, message2[103:96]};
		LCD_SECOND_LINE + 4: INST_TABLE_DATA <= {1'b1, message2[95:88]};
		LCD_SECOND_LINE + 5: INST_TABLE_DATA <= {1'b1, message2[87:80]};
		LCD_SECOND_LINE + 6: INST_TABLE_DATA <= {1'b1, message2[79:72]};
		LCD_SECOND_LINE + 7: INST_TABLE_DATA <= {1'b1, message2[71:64]};
		LCD_SECOND_LINE + 8: INST_TABLE_DATA <= {1'b1, message2[63:56]};
		LCD_SECOND_LINE + 9: INST_TABLE_DATA <= {1'b1, message2[55:48]};
		LCD_SECOND_LINE + 10: INST_TABLE_DATA <= {1'b1, message2[47:40]};
		LCD_SECOND_LINE + 11: INST_TABLE_DATA <= {1'b1, message2[39:32]};
		LCD_SECOND_LINE + 12: INST_TABLE_DATA <= {1'b1, message2[31:24]};
		LCD_SECOND_LINE + 13: INST_TABLE_DATA <= {1'b1, message2[23:16]};
		LCD_SECOND_LINE + 14: INST_TABLE_DATA <= {1'b1, message2[15:8]};
		LCD_SECOND_LINE + 15: INST_TABLE_DATA <= {1'b1, message2[7:0]};
		default: INST_TABLE_DATA <= 0;
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
