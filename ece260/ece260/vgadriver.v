`default_nettype none

module vgadriver(CLOCK_50, VGA_R, VGA_G, VGA_B, VGA_BLANK, VGA_SYNC, VGA_HS, VGA_VS);
input wire CLOCK_50;
output reg[9:0] VGA_R;
output reg[9:0] VGA_G;
output reg[9:0] VGA_B;
output reg VGA_BLANK;
output reg VGA_SYNC;
output reg VGA_HS;
output reg VGA_VS;
reg[9:0] x_count;
reg[9:0] y_count;
wire CLOCK_25;

clockdivider clock25(CLOCK_50, CLOCK_25);

initial begin
	x_count = 0;
	y_count = 0;
	VGA_R = 512;
	VGA_G = 512;
	VGA_B = 512;
	VGA_BLANK = 1;
	VGA_SYNC = 1;
	VGA_HS = 1;
	VGA_VS = 1;
end

always @ (posedge CLOCK_25) begin
	x_count <= x_count + 1;
	
	// in display interval
	if (x_count <= 640) begin
		VGA_R <= 0;
		VGA_G <= 1024;
		VGA_B <= 0;
		//update pixels for (x,y) pos
	end
	
	// display interval over, front porch begins
	if (x_count > 640 && x_count < 800) begin
		//FRONTPORCH - VGA_BLANK
		VGA_BLANK <= 0;
		// front porch over, sync begins
		if (x_count >= 656 && x_count < 753) begin
			//SYNC - HSYNC
			VGA_SYNC <= 0;
			VGA_HS <= 0;
		end
		//sync over, back porch begins
		else begin
			VGA_SYNC <= 1;
			VGA_HS <= 1;
		end
		//BACKPORCH - VGA_BLANK
	end
	// back porch over, prepare for display interval
	else begin
		VGA_BLANK <= 1;
	end
	
	// row is over, so go to next row
	if (x_count >= 800) begin
		x_count <= 0;
		y_count <= y_count + 1;
	end
	
	// display interval for frame
	if (y_count <= 480) begin
		//dunno
	end
	
	// display interval over, porches and sync begin
	if (y_count > 480 && y_count < 525) begin
		//FRONTPORCH - VGA_BLANK
		VGA_BLANK <= 0;
		if (y_count > 490 && y_count <= 492) begin
			//SYNC - VSYNC
			VGA_SYNC <= 0;
			VGA_VS <= 0;
		end
		//sync over, back porch begins
		else begin
			VGA_SYNC <= 1;
			VGA_VS <= 1;
		end
		//BACKPORCH - VGA_BLANK
	end
	// back porch over, prepare for display interval
	else begin 
		VGA_BLANK <= 1;
	end
	
	// frame is over, so go to next frame
	if (y_count >= 525) begin
		y_count <= 0;
	end
	
end


endmodule

module clockdivider(clock, clock_25);
	input wire clock;
	output reg clock_25;
	
	always @ (posedge clock) begin
		clock_25 <= clock_25 + 1;
	end
	
	endmodule