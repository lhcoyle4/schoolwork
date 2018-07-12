/*
Louis Coyle II
Email: lhcoyle4@gmail.com
DigiPen login: louis.coyleii
Course: ECE399
Lab: 8 - ram part 6
Date: 10/21/14
*/

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.de1_pkg.all;

entity part6 is
	port (SW : in std_logic_vector(9 downto 0);
			KEY : in std_logic_vector(0 downto 0);
			CLOCK_50 : in std_logic;
			LEDG : out std_logic_vector(0 downto 0);
			HEX0 : out std_logic_vector (6 downto 0);
			HEX1 : out std_logic_vector (6 downto 0);
			HEX3 : out std_logic_vector (6 downto 0));
end part6;

architecture rtl of part6 is
	signal data : std_logic_vector(3 downto 0);
	signal address : std_logic_vector(3 downto 0);
	signal clock : std_logic;
	
	begin
	-- address, clock, data, wren, q
	M4K : entity work.ram1lpm port map(address, clock, SW(3 downto 0), 
												  SW(9), data);
												 
	LEDG <= SW(9 downto 9); -- display write signal,
	HEX0 <= hex(data); -- display the data read out of memory,
	HEX1 <= hex(SW(3 downto 0)); -- input data,
	HEX3 <= hex(SW(7 downto 4)); -- and address
	
	process(CLOCK_50, KEY) 
		variable prescaler : integer;
		variable readadr : integer;
	begin
		-- increment the read address once every second
		if (rising_edge(CLOCK_50)) then
			if (prescaler < 25000000) then
				prescaler := prescaler + 1;
			else 
				prescaler := 0;
				if (clock) then
					clock <= '0';
				else 
					clock <= '1';
				end if;
			end if;
		end if;
		if (rising_edge(clock)) then
				if (readadr < 15) then
					readadr := readadr + 1;
				else 
					readadr := 0;
				end if;
		end if;
		-- KEY 0 as a reset input
		if (KEY(0) = '0') then
			readadr := 0;
		end if;
		-- multiplex addressing between read and write
		if (SW(9)) then
			address <= SW(7 downto 4);
		else 
			address <= std_logic_vector(to_unsigned(readadr, 4));
		end if;
	end process;
end rtl;