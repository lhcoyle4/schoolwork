/*
Louis Coyle II
Email: lhcoyle4@gmail.com
DigiPen login: louis.coyleii
Course: ECE399
Lab: 8 - ram part 3
Date: 10/21/14
*/

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.de1_pkg.all;

entity part3 is
	port (SW : in std_logic_vector(9 downto 0);
			KEY : in std_logic_vector(0 downto 0);
			LEDG : out std_logic_vector(0 downto 0);
			HEX0 : out std_logic_vector (6 downto 0);
			HEX1 : out std_logic_vector (6 downto 0);
			HEX3 : out std_logic_vector (6 downto 0));
end part3;

architecture rtl of part3 is
	type mem is array(0 to 15) of std_logic_vector(3 downto 0);
	signal memory_array : mem;
	signal data : std_logic_vector(3 downto 0);
	
	begin
		process (KEY)
		begin
			if (falling_edge(KEY(0))) then
				if (SW(9)) then
					memory_array(to_integer(unsigned(SW(7 downto 4)))) <= SW(3 downto 0);		
				end if;
			end if;
			LEDG <= SW(9 downto 9); -- display write signal,
			HEX1 <= hex(SW(3 downto 0)); -- input data,
			HEX3 <= hex(SW(7 downto 4)); -- and address
			HEX0 <= hex(memory_array(to_integer(unsigned(SW(7 downto 4))))); -- display the data read out of memory
		end process;
end rtl;
