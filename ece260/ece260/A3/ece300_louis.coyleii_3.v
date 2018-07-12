`default_nettype none

module reactiontest(SW, KEY, CLOCK_50, HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7);
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
	reg [3:0] hundredth_s_counter;
	reg [3:0] tenth_s_counter;
	reg [3:0] s_counter;
	reg [3:0] ten_s_counter;
	reg [3:0] m_counter;
	reg [3:0] ten_m_counter;
	reg [25:0] counter;
	reg [25:0] prng_counter;
	reg [28:0] wait_counter;
	reg [28:0] PRN;
	reg gen_random_wait;
	reg random_wait;
	reg begin_reaction_test;

	segdriver seg0(hundredth_s_counter, HEX0);
	segdriver seg1(tenth_s_counter, HEX1);
	segdriver seg2(s_counter, HEX2);
	segdriver seg3(ten_s_counter, HEX3);
	segdriver seg4(m_counter, HEX4);
	segdriver seg5(ten_m_counter, HEX5);
	
	// board begins in specific initial state
	// must press KEY[1] to test reaction
	initial begin
		prng_counter = 0;
		wait_counter = 0;
		gen_random_wait = 1;
		random_wait = 0;
		begin_reaction_test = 0;
		hundredth_s_counter = 0;
		tenth_s_counter = 0;
		s_counter = 0;
		ten_s_counter = 0;
		m_counter = 0;
		ten_m_counter = 0;
		HEX7 = ~0;
		HEX6 = ~0;
	end
	
	always @ (posedge CLOCK_50) begin
		counter <= counter + 1;
		// pressing key 1 starts the game by entering the random_wait state
		if(!KEY[1] && gen_random_wait) begin
			hundredth_s_counter <= 10;
			tenth_s_counter <= 10;
			s_counter <= 10;
			ten_s_counter <= 10;
			m_counter <= 10;
			ten_m_counter <= 10;
			// use the LSB's of the prng_counter to generate a PRN
			// that will be large enough to allow for a 1 to 10s wait
			PRN <= ((prng_counter % 10) + 1) * 50000000;
			prng_counter <= 0;
			wait_counter <= 0;
			gen_random_wait <= 0;
			begin_reaction_test <= 0;
			random_wait <= 1;
		end
		
		// pressing key 0 is only applicable when counter is running
		// this freezes the display, showing your reaction time
		// and begins counting on prng_counter for PRN generation
		if (!KEY[0] && begin_reaction_test) begin
			random_wait <= 0;
			begin_reaction_test <= 0;
			gen_random_wait <= 1;
		end
		
		// counts the amount of cycles between games
		if (gen_random_wait) begin
			prng_counter <= prng_counter + 1;
		end
		
		// when key 1 waits a random amount of time
		// by counting up to the generated PRN
		if(random_wait && wait_counter < PRN) begin
			wait_counter <= wait_counter + 1;
		end
		else if (random_wait && !begin_reaction_test) begin
			hundredth_s_counter <= 0;
			tenth_s_counter <= 0;
			s_counter <= 0;
			ten_s_counter <= 0;
			m_counter <= 0;
			ten_m_counter <= 0;
			counter <= 0;
			begin_reaction_test <= 1;
		end
		
		// when the wait_counter is greater than the PRN, the reaction test begins
		// by counting up on the display until 0 is pressed
		if (begin_reaction_test && counter > 500000) begin
			counter <= 0;
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
						if(ten_s_counter >= 5) begin
							ten_s_counter <= 0;
							m_counter <= m_counter + 1;
							if(m_counter >= 9) begin
								m_counter <= 0;
								ten_m_counter <= ten_m_counter + 1;
								if(ten_m_counter >= 5)begin
									hundredth_s_counter <= 0;
									tenth_s_counter <= 0;
									s_counter <= 0;
									ten_s_counter <= 0;
									m_counter <= 0;
									ten_m_counter <= 0;
								end
							end
						end
					end	
				end
			end
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
		   10: seg = 7'b1111111; //b0001000
		   11: seg = 7'b0000011;
		   12: seg = 7'b1000110;
		   13: seg = 7'b0100001;
		   14: seg = 7'b0000110;
		   15: seg = 7'b0001110;
		 endcase 
	 end
endmodule