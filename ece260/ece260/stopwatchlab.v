`default_nettype none

module stopwatchlab(SW, KEY, CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7);
	output wire [6:0] HEX0;
	output wire [6:0] HEX1;
	output wire [6:0] HEX2;
	output wire [6:0] HEX3;
	output wire [6:0] HEX4;
	output wire [6:0] HEX5;
	output reg [6:0] HEX6;
	output reg [6:0] HEX7;
	input wire [3:0] SW;
	input wire CLOCK_50;
	input wire [3:0] KEY;
	wire clock_100hz;
	reg [3:0] hundredth_s_counter;
	reg [3:0] tenth_s_counter;
	reg [3:0] s_counter;
	reg [3:0] ten_s_counter;
	reg [3:0] m_counter;
	reg [3:0] ten_m_counter;
	reg running;
	reg reset;

	segdriver seg0(hundredth_s_counter, HEX0);
	segdriver seg1(tenth_s_counter, HEX1);
	segdriver seg2(s_counter, HEX2);
	segdriver seg3(ten_s_counter, HEX3);
	segdriver seg4(m_counter, HEX4);
	segdriver seg5(ten_m_counter, HEX5);
	clockdivider clk10hz(CLOCK_50, clock_100hz);
	
	initial begin
		running = 0;
		reset = 0;
		hundredth_s_counter = 0;
		tenth_s_counter = 0;
		s_counter = 0;
		ten_s_counter = 0;
		m_counter = 0;
		ten_m_counter = 0;
		HEX7 = ~0;
		HEX6 = ~0;
	end
	
	always @ (posedge clock_100hz) begin
		if(!KEY[1]) begin
			running <= 1;
			reset <= 0;
		end
		if (!KEY[2]) begin
			running <= 0;
		end
		if (!KEY[0]) begin
			reset <= 1;
			running <= 0;
		end
		if (reset) begin
			hundredth_s_counter <= 0;
			tenth_s_counter <= 0;
			s_counter <= 0;
			ten_s_counter <= 0;
		end
		if (running && !reset) begin
			hundredth_s_counter <= hundredth_s_counter + 1;
			if (hundredth_s_counter >= 9) begin
				hundredth_s_counter <= 0;
				tenth_s_counter <= tenth_s_counter + 1;
				if (tenth_s_counter >= 9) begin
					tenth_s_counter <= 0;
					s_counter <= s_counter + 1;
					if(s_counter >= 9) begin
						s_counter <= 0;
						ten_s_counter <= ten_s_counter + 1;
						if(ten_s_counter >= 9) begin
							ten_s_counter <= 0;
							m_counter <= m_counter + 1;
							if(m_counter >= 9) begin
								m_counter <= 0;
								ten_m_counter <= ten_m_counter + 1;
								if(ten_m_counter >= 5)begin
									reset <= 1;
								end
							end
						end
					end	
				end
			end
		end
	end
endmodule

module clockdivider(clock, clock_100hz);
	input wire clock;
   reg [26:0] counter;
	output reg clock_100hz;
	
	always @ (posedge clock) begin
		counter <= counter + 1;
		if(counter > 500000) begin
			clock_100hz <= ~clock_100hz;
			counter <= 0;
		end
	end
	
endmodule

module segdriver(decimal_in, seg);
	 output reg [6:0] seg;
    input wire [3:0] decimal_in;

    always @ (decimal_in) begin
		case(decimal_in)
		    0: seg = 7'b1000000;
		    1: seg = 7'b1111001;
		    2: seg = 7'b0100100;
		    3: seg = 7'b0110000;
		    4: seg = 7'b0011001;
		    5: seg = 7'b0010010;
		    6: seg = 7'b0000011;
		    7: seg = 7'b1111000;
		    8: seg = 7'b0000000;
		    9: seg = 7'b0011000;
		   10: seg = 7'b0001000;
		   11: seg = 7'b0000011;
		   12: seg = 7'b1000110;
		   13: seg = 7'b0100001;
		   14: seg = 7'b0000110;
		   15: seg = 7'b0001110;
		 endcase 
	 end
endmodule