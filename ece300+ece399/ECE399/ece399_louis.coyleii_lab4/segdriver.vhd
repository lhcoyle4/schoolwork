/*
Louis Coyle II
Email: lhcoyle4@gmail.com
DigiPen login: louis.coyleii
Course: ECE399
Lab: 4 - segdriver
Date: 10/07/14
*/

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.de1_pkg.all;

entity segdriver is 
	port(SW : in std_logic_vector(7 downto 0);
		  CLOCK_50 : in std_logic;
		  HEX0: out std_logic_vector(6 downto 0);
		  HEX1: out std_logic_vector(6 downto 0));
end segdriver;

architecture behavior of segdriver is
begin
	process(CLOCK_50)	
	begin
		if (rising_edge(CLOCK_50)) then
			HEX0 <= hex(SW(3 downto 0));
			HEX1 <= hex(SW(7 downto 4));
		end if;
	end process;
end behavior;