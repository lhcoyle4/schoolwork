module log(CLOCK_50, LEDR, SW);
input CLOCK_50;
output reg [17:0] LEDR;
input [17:0] SW;

// input of the algorithm log2(value_of_power) = power;
integer value_of_power;
// counter for accessing table and for shift multiplies
reg [7:0] n;
// for the output of the algorithm log2(value_of_power) = power;
integer power;
// value from the table, for subtracting from the input iteratively
integer tabval;
// table values from 1.0000000 to 1.0000001
integer tablen[0:20];

initial begin
  // init the table and counter
  tablen[0] = ;
  tablen[1] = ;
  tablen[2] = ;
  tablen[3] = ;
  tablen[4] = ;
  tablen[5] = ;
  tablen[6] = ;
  tablen[7] = ;
  tablen[8] = ;
  tablen[9] = ;
  tablen[10] = ;
  tablen[11] = ;
  tablen[12] = ;
  tablen[13] = ;
  tablen[14] = ;
  tablen[15] = ;
  tablen[16] = ;
  tablen[17] = ;
  tablen[18] = ;
  tablen[19] = ;
  tablen[20] = ;
  n = 20;
end

always @(posedge CLOCK_50) begin
  // initial case
  if (n == 20) begin
    n <= 0;
    // set up the output variable to init conds
    
    // initialize the unused bits in value_of_power to 0
    
    // get value of power from the switches
    
    // give the LED the correct output value from the previous run
   
  end
  else begin
    tabval = tablen[n];
    if (value_of_power > 0) begin
      power <= power - (power>>>n)
      value_of_power <= value_of_power - tabval;
    end
    else begin
      power <= power + (power>>>n)
      value_of_power <= value_of_power + tabval;
    end
    n <= n + 1;
end

endmodule