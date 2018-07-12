library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package de1_pkg is
	function hex (swstate : std_logic_vector(3 downto 0)) return std_logic_vector;
end;

package body de1_pkg is
	function hex (swstate : std_logic_vector(3 downto 0))
			 return std_logic_vector is
	begin
		case swstate is
			WHEN "0000" => return "1000000";
			WHEN "0001" => return "1111001";
			WHEN "0010" => return "0100100";
			WHEN "0011" => return "0110000";
			WHEN "0100" => return "0011001";
			WHEN "0101" => return "0010010";
			WHEN "0110" => return "0000010";
			WHEN "0111" => return "1111000";
			WHEN "1000" => return "0000000";
			WHEN "1001" => return "0011000";
			WHEN "1010" => return "0001000";
			WHEN "1011" => return "0000011";
			WHEN "1100" => return "1000110";
			WHEN "1101" => return "0100001";
			WHEN "1110" => return "0000110";
			WHEN "1111" => return "0001110";
		end case; 
	end hex;
end package body;