/*
Louis Coyle II
Email: lhcoyle4@gmail.com
DigiPen login: louis.coyleii
Course: ECE399
Lab: 8 - ram part 2
Date: 10/21/14
*/

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.de1_pkg.all;

entity part2 is
	port (SW : in std_logic_vector(9 downto 0);
			KEY : in std_logic_vector(0 downto 0);
			LEDG : out std_logic_vector(0 downto 0);
			HEX0 : out std_logic_vector (6 downto 0);
			HEX1 : out std_logic_vector (6 downto 0);
			HEX3 : out std_logic_vector (6 downto 0));
end part2;

architecture rtl of part2 is
	signal data : std_logic_vector(3 downto 0);
	
	begin
	-- address, clock, data, wren, q
	M4K : entity work.ramlpm port map(SW(7 downto 4), KEY(0), SW(3 downto 0), 
												 SW(9), data);
												 
	LEDG <= SW(9 downto 9); -- display write signal,
	HEX0 <= hex(data); -- display the data read out of memory,
	HEX1 <= hex(SW(3 downto 0)); -- input data,
	HEX3 <= hex(SW(7 downto 4)); -- and address
end rtl;
