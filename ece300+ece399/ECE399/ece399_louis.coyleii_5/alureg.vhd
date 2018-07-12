/*
Louis Coyle II
Email: lhcoyle4@gmail.com
DigiPen login: louis.coyleii
Course: ECE399
Assignment: 5 - ALU with registers
Date: 10/12/14
*/

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.de1_pkg.all;

entity alureg is
	port (SW : in unsigned(9 downto 0);
			KEY : in std_logic_vector(0 downto 0);
			HEX0 : out unsigned(6 downto 0);
			HEX1 : out unsigned(6 downto 0);
			HEX2 : out unsigned(6 downto 0);
			HEX3 : out unsigned(6 downto 0));
end alureg;

architecture behavior of alureg is

  type REG_ARRAY is array (7 downto 0) of unsigned(7 downto 0);
  
  -- using a procedure rather than a function because the return is different depending
  -- on the input of the switches. this lets me specify the parameters as inout, and then
  -- have the actual variables that I am passing in be changed by the procedure
  procedure inst_decoder (instruction: in std_logic_vector(5 downto 0); 
					 data: in unsigned(7 downto 0);
					 reg:  in integer;
					 regfile: inout REG_ARRAY;
					 wreg: inout unsigned(7 downto 0)) is
	begin
		-- the case? statement basically uses std_match instead of the = operator,
		-- allowing the don't care values to be evaluated the way I want them to.
		-- ie, execute the instruction whenever just the values that we do care about are matching.
		-- using a normal case statement here would require the input to have actual don't care values
		-- in order to match any of these cases.
		case? instruction is
			WHEN "00----" => wreg := data;
			WHEN "01--00" => wreg := wreg + regfile(reg);
			WHEN "01--01" => wreg := wreg - regfile(reg);
			WHEN "01--10" => wreg := wreg and regfile(reg);
			WHEN "01--11" => wreg := wreg xor regfile(reg);
			WHEN "10----" => regfile(reg) := wreg;
			WHEN "11----" => wreg := regfile(reg);
		end case?;
	end inst_decoder;
	
begin
	process (KEY)
	variable wreg : unsigned(7 downto 0);
	variable regfile : REG_ARRAY;
	begin
		HEX0 <= hex(SW(3 downto 0));
		HEX1 <= hex(SW(7 downto 4));
		HEX2 <= hex(wreg(3 downto 0));
		HEX3 <= hex(wreg(7 downto 4));
		-- call the function to evaluate the instruction passed in via switches,
		-- and execute the proper commands on the data based on this instruction
		if (falling_edge(KEY(0))) then
			-- MSB SW's need to be std_logic_vector in order to compare to don't care values
			-- LSB SW's need to be integer to use them as an index into regfile array.
			-- otherwise they are evaluated as an unsigned, because we are using them for arithmetic
			inst_decoder(std_logic_vector(SW(9 downto 4)), SW(7 downto 0), 
							 to_integer(SW(2 downto 0)), regfile, wreg);
		end if;
	end process;
end behavior;