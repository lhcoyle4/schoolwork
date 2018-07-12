library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity my_first_fpga is
	port (KEY : in std_logic_vector(0 downto 0);
			CLOCK_50 : in std_logic;
			LEDR : out std_logic_vector(3 downto 0));
end my_first_fpga;

architecture behavior of my_first_fpga is

	signal reset_n : std_logic;
	
begin
	
	process (CLOCK_50)
	
		variable count : unsigned(27 downto 0);
		
	begin
	
		if(rising_edge(CLOCK_50)) then
		
			reset_n <= std_logic(KEY(0));
			
			if (reset_n = '0') then
				count := to_unsigned(0, 28);
			else
				count := count + 1;
			end if;
			
			LEDR <= std_logic_vector(count(27 downto 24));
		
		end if;
	end process;
	
end behavior;

/*
module my_first_fpga(CLOCK_50, LEDR, KEY);
input CLOCK_50;
input [3:0]KEY;
output [3:0] LEDR;

reg [27:0] count;
wire reset_n;

assign reset_n = KEY[0];
always @(posedge CLOCK_50 or negedge reset_n)
begin    
    if(!reset_n)
        count = 0;
    else
        count = count + 1;
end

assign LEDR = count[27:24];

endmodule */