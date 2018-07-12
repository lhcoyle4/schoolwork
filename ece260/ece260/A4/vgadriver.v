module vgadriver(CLOCK_50, VGA_R, VGA_G, VGA_B, VGA_BLANK, VGA_SYNC, VGA_HS, VGA_VS, VGA_CLK);
input wire CLOCK_50;
output wire [9:0] VGA_R;
output wire [9:0] VGA_G;
output wire [9:0] VGA_B;
output wire VGA_BLANK;
output wire VGA_SYNC;
output wire VGA_HS;
output wire VGA_VS;
output wire VGA_CLK;

wire [9:0] r_val;
wire [9:0] g_val;
wire [9:0] b_val;
wire [9:0] x_count;
wire [9:0] y_count;
wire CLOCK_25;

// Clock Divider
// Divides the internal 50MHz clock in half for use as 25MHz pixel clock.
clock_divider  clock25( .inClock_50(CLOCK_50), 
                        .outClock_25(CLOCK_25));

// VGA Driver
// Handles driving of the VGA signal. Sets pins for syncing, maintaining black
// levels, sends the RGB information from the image_gen module to the screen.
vga_driver     vga    ( .inR(r_val), 
                        .inG(g_val), 
                        .inB(b_val), 
                        .outX(x_count), 
                        .outY(y_count), 
                        .outVGA_R(VGA_R), 
                        .outVGA_G(VGA_G), 
                        .outVGA_B(VGA_B), 
                        .outVGA_HS(VGA_HS), 
                        .outVGA_VS(VGA_VS), 
                        .outVGA_SYNC(VGA_SYNC), 
                        .outVGA_BLANK(VGA_BLANK), 
                        .outVGA_CLOCK(VGA_CLK), 
                        .inClock_25(CLOCK_25));

// Image Generation
// Changes the RGB levels based on the current (x,y) position on the screen
// in order to make an image.
image_gen      image  ( .outR(r_val),
                        .outG(g_val),
                        .outB(b_val),
                        .inX(x_count),
                        .inY(y_count),
                        .inVGA_VS(VGA_VS),
                        .inClock_25(CLOCK_25));

endmodule

module clock_divider(inClock_50, outClock_25);
input wire inClock_50;
output reg outClock_25;
  
always @ (posedge inClock_50) begin
  outClock_25 <= outClock_25 + 1;
end
  
endmodule


module vga_driver(inR, inG, inB, outX, outY, outVGA_R, outVGA_G, outVGA_B, 
                  outVGA_HS, outVGA_VS, outVGA_SYNC, outVGA_BLANK, outVGA_CLOCK, inClock_25);

input [9:0] inR;
input [9:0] inG;
input [9:0] inB;
output [9:0] outX;
output [9:0] outY;

output [9:0] outVGA_R;
output [9:0] outVGA_G;
output [9:0] outVGA_B;
output reg outVGA_HS;
output reg outVGA_VS;
output outVGA_SYNC;
output outVGA_BLANK;
output outVGA_CLOCK;

input inClock_25;

reg [9:0] H_Count;
reg [9:0] V_Count;

// Note: I got the idea to use parameters to make my code more clear from a
// demonstration verilog project on the DE_2 CD
// set up defines for horizontal
parameter H_DISP = 640;
parameter H_FRONTP = 16;
parameter H_SYNC = 96;
parameter H_BACKP = 48;
parameter H_BLANK = H_FRONTP + H_SYNC + H_BACKP;
parameter H_TOTAL = H_FRONTP + H_SYNC + H_BACKP + H_DISP;

// set up defines for vertical
parameter V_DISP = 480;
parameter V_FRONTP = 11;
parameter V_SYNC = 2;
parameter V_BACKP = 31;
parameter V_BLANK = V_FRONTP + V_SYNC + V_BACKP;
parameter V_TOTAL = V_FRONTP + V_SYNC + V_BACKP + V_DISP;

// VGA_SYNC pin not used
assign outVGA_SYNC = 1;

// drive the analog RGB outputs to the blanking level when not displaying
assign outVGA_BLANK =  ~((H_Count < H_BLANK)||(V_Count < V_BLANK));

// supply the DAC with inverted pixel clock to allow RGB, hs/vs, blank inputs to
// be latched on the rising edge of this supplied clock
assign outVGA_CLOCK = ~inClock_25;

// supply the DAC with RGB levels from image_gen module;
assign outVGA_R = inR;
assign outVGA_G = inG;
assign outVGA_B = inB;

// calculate and assign X and Y positions for use in image_gen module
assign outX = (H_Count >= H_BLANK) ? H_Count - H_BLANK : 0;
assign outY = (V_Count >= V_BLANK) ? V_Count - V_BLANK : 0;


always @ (posedge inClock_25) begin
  if (H_Count < H_TOTAL)
    H_Count <= H_Count + 1;
  else
    H_Count <= 0;

  // front porch ends, h sync begins
  if (H_Count == H_FRONTP - 1)
    outVGA_HS <= 0;
  // h sync ends
  if (H_Count == H_FRONTP + H_SYNC - 1) 
    outVGA_HS <= 1;
end

always @ (posedge outVGA_HS) begin
  if (V_Count < V_TOTAL)
    V_Count <= V_Count + 1;
  else
    V_Count <= 0;
  // front porch ends, v sync begins
  if (V_Count == V_FRONTP - 1)
    outVGA_VS <= 0;
  // v sync ends
  if (V_Count == V_FRONTP + V_SYNC - 1) 
    outVGA_VS <= 1;
end

endmodule


module image_gen(outR, outG, outB, inX, inY, inVGA_VS, inClock_25);
output reg [9:0] outR;
output reg [9:0] outG;
output reg [9:0] outB;

input [9:0] inX;
input [9:0] inY;

input inVGA_VS;
input inClock_25;

reg [18:0] clock_60hz;
reg [9:0] mobile_offset;

parameter X_SIZE = 640;
parameter Y_SIZE = 480;
parameter STATIC_OBJECT_X = 128;
parameter STATIC_OBJECT_Y = 128;
parameter MOBILE_OBJECT_X = 64;
parameter MOBILE_OBJECT_Y = 64;
parameter X_MIDPT = X_SIZE >> 1;
parameter Y_MIDPT = Y_SIZE >> 1;

initial begin
  mobile_offset = MOBILE_OBJECT_Y;
  outR = 0;
  outG = 0;
  outB = 0;
end

// make a variable that gets incremented every frame, for smooth animation,
// and only increments to move object to (size of screen) - (object height).
always @ (posedge inVGA_VS) begin
  if (mobile_offset < Y_SIZE - MOBILE_OBJECT_Y)
    mobile_offset <= mobile_offset + 1;
  else
    mobile_offset <= MOBILE_OBJECT_Y;
end

always @ (posedge inClock_25) begin
  // make a red circle in the center of the screen by setting the red val
  // to a visible level when (x,y) are in this circle
  if ((((inX - X_MIDPT) * (inX - X_MIDPT)) + 
      ((inY - Y_MIDPT) * (inY - Y_MIDPT))) == 1024) 
  begin
    outR <= ~0;
    // set G and B to 0 in this circle
    outG <= 0;
    outB <= 0;
  end
  // move the blue square from the top to the bottom of the screen based on the
  // mobile offset, which gets incremented every frame
  else if (inX >= X_MIDPT - MOBILE_OBJECT_X && inX <= X_MIDPT + MOBILE_OBJECT_X &&
      inY >= 0 + mobile_offset - MOBILE_OBJECT_Y && inY <= MOBILE_OBJECT_Y + mobile_offset)
  begin
    outB <= ~0;
    // set G and R to 0 in this moving area
    outG <= 0;
    outR <= 0;
  end
  // make a green gradient that gets darker towards the bottom of the screen
  // by multiplying the current Y value by 2 and setting the green val to this.
  else begin
	  outG <= inY << 1;
    // set red and green to 0 in this remaining area
    outR <= 0;
    outB <= 0;
  end
end

endmodule
