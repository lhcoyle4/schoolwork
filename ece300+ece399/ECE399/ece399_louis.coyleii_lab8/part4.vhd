/*
Louis Coyle II
Email: lhcoyle4@gmail.com
DigiPen login: louis.coyleii
Course: ECE399
Lab: 8 - ram part 4
Date: 10/21/14
*/

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.de1_pkg.all;

entity part4 is
	port (SW : in std_logic_vector(9 downto 0);
			KEY : in std_logic_vector(0 downto 0);
			LEDG : out std_logic_vector(0 downto 0);
			HEX0 : out std_logic_vector (6 downto 0);
			HEX1 : out std_logic_vector (6 downto 0);
			HEX3 : out std_logic_vector (6 downto 0);
			SRAM_ADDR : out std_logic_vector (3 downto 0);
			SRAM_DQ : inout std_logic_vector (3 downto 0);
			SRAM_WE_N : out std_logic;
			SRAM_OE_N : out std_logic;
			SRAM_UB_N : out std_logic;
			SRAM_LB_N : out std_logic;
			SRAM_CE_N : out std_logic);
end part4;

architecture rtl of part4 is
	begin
	
	SRAM_ADDR <= SW(7 downto 4);
	SRAM_OE_N <= '0';
	SRAM_UB_N <= '0';
	SRAM_LB_N <= '0';
	SRAM_CE_N <= '0';
	LEDG <= SW(9 downto 9); -- display write signal,
	HEX1 <= hex(SW(3 downto 0)); -- input data,
	HEX3 <= hex(SW(7 downto 4)); -- and address
	HEX0 <= hex(SRAM_DQ(3 downto 0)); -- display the data read out of memory
	
	process (KEY)
	begin
		if (falling_edge(KEY(0))) then
			if (SW(9)) then
				SRAM_WE_N <= '0';
				SRAM_DQ <= SW(3 downto 0);		
			else
				SRAM_WE_N <= '1';
				SRAM_DQ <= "ZZZZ";
			end if;
		end if;
	end process;
end rtl;