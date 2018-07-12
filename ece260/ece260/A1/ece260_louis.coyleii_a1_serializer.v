module serializer(out, busy, clock, data, wr);
  output out, busy;
  input clock, wr;
  input [7:0] data;
  reg busy, out;
  reg [7:0] buffer;
  integer i;
  
  initial begin
    busy = 0;
    out = 1;
    buffer = 0;
    i = -1;
  end
  
  always @ (posedge(clock)) begin
   if ((wr && ~busy) || (~wr && busy)) begin
      busy <= 1;
      buffer <= data;
      if (i == -1) begin
       out <= 0;
       i <= i + 1;
      end
      else if (i > 7) begin
        out <= 1;
        i <= -1;
        busy <= 0;
      end
      else begin
        out <= buffer[i];
        i <= i + 1;
      end
   end
  end
  
endmodule
module testbench;
 wire busy;
 wire out;
 reg clock, wr;
 reg [7:0] data;
 
 serializer DUT(out, busy, clock, data, wr);
 
 initial begin
 clock = 0;
 wr = 1;
 data = 8'b01011010;
 #10 wr = 0;
 #100 wr = 1;
 data = 8'b11100010;
 #10 wr = 0;
 #100 wr = 1;
 data = 8'b00110011;
 #10 wr = 0;
 #100 wr = 1;
 data = 8'b10001110;
 #10 wr = 0;
 end
 
 always #5 clock = ~clock; 
endmodule