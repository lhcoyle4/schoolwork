/*****************************************************************************/
/*!
* \file   log2.v
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: ECE260
* \par    Assignment #6
* \date   03/14/2014
* 
* \brief
* This file contains the implementation of the log2 module.
* 
* Hours spent on this assignment: 3
* 
* Specific portions that gave you the most trouble: fractional inputs/negative
* outputs.
*/
/*****************************************************************************/

module log2(CLOCK_50, LEDR, SW);
input wire CLOCK_50;
output reg [17:0] LEDR; // in signed fixed point 3.13 plus sign bit
input wire [17:0] SW; // in unsigned fixed point 8.8 format

// input of the algorithm log2(value_of_power) = power;
integer value_of_power;
// to store the most significant bit that is set, for preprocessing
integer ms_set_bit; 
// to allow operations on the input from switches 
integer temp_for_msb;
// for detecting first set bit on fractional side
integer temp_for_msb_neg;
// counter for accessing table and for shift multiplies
reg [7:0] n;
// for the output of the algorithm log2(value_of_power) = power;
integer power;
// value from the table, for subtracting from the input iteratively
integer tabval;
// table values from .5 to (1 - 8191/8192) all left shifted 13
integer tablen[1:12];

initial begin
  // init the table and counter
  /*tablen[1] = 6144; // 3/4 << 13
  tablen[2] = 6144; // 3/4 << 13
  tablen[3] = 7168; // 7/8 << 13
  tablen[4] = 7680; // 15/16 << 13
  tablen[5] = 7936; // 31/32 << 13
  tablen[6] = 8064; // 63/64 << 13
  tablen[7] = 8128; // 127/128 << 13
  tablen[8] = 8160; // 255/256 << 13
  tablen[9] = 8176; // 511/512 << 13
  tablen[10] = 8184; // 1023/1024 << 13
  tablen[11] = 8188;// 2047/2048 << 13 
  tablen[12] = 8190;// 4095/4096 << 13
  tablen[13] = 8191;// 8191/8192 << 13*/

  tablen[1] = 4096;
  tablen[2] = 2048; // 1 - 3/4 << 13
  tablen[3] = 2048; // 1 - 3/4 << 13
  tablen[4] = 1024; // 1 - 7/8 << 13
  tablen[5] = 512;  // 1 - 15/16 << 13
  tablen[6] = 256;  // 1 - 31/32 << 13
  tablen[7] = 128;  // 1 - 63/64 << 13
  tablen[8] = 64;   // 1 - 127/128 << 13
  tablen[9] = 32;   // 1 - 255/256 << 13
  tablen[10] = 16;   // 1 - 511/512 << 13
  tablen[11] = 8;    // 1 - 1023/1024 << 13
  tablen[12] = 4;   // 1 - 2047/2048 << 13 
  tablen[13] = 2;   // 1 - 4095/4096 << 13
  tablen[14] = 1;   // 1 - 8191/8192 << 13
  power = 0;
  LEDR = 0;
  temp_for_msb = 0;
  temp_for_msb_neg = 0;
  value_of_power = 0;
  ms_set_bit = 0;
  n = 15;
end

always @(posedge CLOCK_50) begin
  // initial case
  if (n == 15) begin
    
    LEDR <= power;
    value_of_power <= SW; // read in unsigned 8.8 input to log2
    temp_for_msb <= SW; // put in temp variable for detecting MSB in whole side
    temp_for_msb_neg <= SW; // temp variable for detecting MSB in fractional side
    ms_set_bit <= 0;
    n <= n + 1;
  end
  else if (n == 16) begin
    if (temp_for_msb > 512) begin // greater than 1 in 8.8 fixed point
      temp_for_msb <= (temp_for_msb >> 1); // then continue shifting
      ms_set_bit <= ms_set_bit + 1;// and count the number of shifts
    end
    else if (temp_for_msb_neg <= 256) begin
      temp_for_msb_neg <= (temp_for_msb_neg << 1);
      ms_set_bit <= ms_set_bit - 1;
    end
    else begin
      // set up the output variable to init conds
      power <= (ms_set_bit << 13);
      // go to next state, finding fractional portion of power
      n <= 1;
    end
  end
  else begin
    tabval = tablen[n];
    if ((value_of_power - tabval) > 1) begin
      value_of_power <= value_of_power - (value_of_power>>n);
      power <= power + tabval;
    end
    n <= n + 1;
  end
end

endmodule
