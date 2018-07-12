-- Copyright (C) 1991-2012 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 12.1 Build 177 11/07/2012 SJ Full Version"

-- DATE "10/07/2014 14:47:27"

-- 
-- Device: Altera EP2C20F484C7 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEII;
LIBRARY IEEE;
USE CYCLONEII.CYCLONEII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	my_first_fpga IS
    PORT (
	KEY : IN std_logic_vector(0 DOWNTO 0);
	CLOCK_50 : IN std_logic;
	LEDR : OUT std_logic_vector(3 DOWNTO 0)
	);
END my_first_fpga;

-- Design Ports Information
-- LEDR[0]	=>  Location: PIN_R20,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
-- LEDR[1]	=>  Location: PIN_R19,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
-- LEDR[2]	=>  Location: PIN_U19,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
-- LEDR[3]	=>  Location: PIN_Y19,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
-- CLOCK_50	=>  Location: PIN_L1,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
-- KEY[0]	=>  Location: PIN_R22,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default


ARCHITECTURE structure OF my_first_fpga IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_KEY : std_logic_vector(0 DOWNTO 0);
SIGNAL ww_CLOCK_50 : std_logic;
SIGNAL ww_LEDR : std_logic_vector(3 DOWNTO 0);
SIGNAL \CLOCK_50~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \Add0~0_combout\ : std_logic;
SIGNAL \Add0~4_combout\ : std_logic;
SIGNAL \Add0~10_combout\ : std_logic;
SIGNAL \Add0~14_combout\ : std_logic;
SIGNAL \Add0~18_combout\ : std_logic;
SIGNAL \Add0~20_combout\ : std_logic;
SIGNAL \Add0~36_combout\ : std_logic;
SIGNAL \Add0~38_combout\ : std_logic;
SIGNAL \Add0~40_combout\ : std_logic;
SIGNAL \Add0~42_combout\ : std_logic;
SIGNAL \Add0~62_combout\ : std_logic;
SIGNAL \Add0~63_combout\ : std_logic;
SIGNAL \Add0~64_combout\ : std_logic;
SIGNAL \Add0~65_combout\ : std_logic;
SIGNAL \Add0~73_combout\ : std_logic;
SIGNAL \Add0~74_combout\ : std_logic;
SIGNAL \Add0~76_combout\ : std_logic;
SIGNAL \Add0~78_combout\ : std_logic;
SIGNAL \Add0~83_combout\ : std_logic;
SIGNAL \CLOCK_50~combout\ : std_logic;
SIGNAL \CLOCK_50~clkctrl_outclk\ : std_logic;
SIGNAL reset_n : std_logic;
SIGNAL \count[24]~feeder_combout\ : std_logic;
SIGNAL \Add0~81_combout\ : std_logic;
SIGNAL \Add0~1\ : std_logic;
SIGNAL \Add0~2_combout\ : std_logic;
SIGNAL \Add0~82_combout\ : std_logic;
SIGNAL \Add0~3\ : std_logic;
SIGNAL \Add0~5\ : std_logic;
SIGNAL \Add0~6_combout\ : std_logic;
SIGNAL \Add0~80_combout\ : std_logic;
SIGNAL \Add0~7\ : std_logic;
SIGNAL \Add0~8_combout\ : std_logic;
SIGNAL \Add0~79_combout\ : std_logic;
SIGNAL \Add0~9\ : std_logic;
SIGNAL \Add0~11\ : std_logic;
SIGNAL \Add0~12_combout\ : std_logic;
SIGNAL \Add0~77_combout\ : std_logic;
SIGNAL \Add0~13\ : std_logic;
SIGNAL \Add0~15\ : std_logic;
SIGNAL \Add0~16_combout\ : std_logic;
SIGNAL \Add0~75_combout\ : std_logic;
SIGNAL \Add0~17\ : std_logic;
SIGNAL \Add0~19\ : std_logic;
SIGNAL \Add0~21\ : std_logic;
SIGNAL \Add0~22_combout\ : std_logic;
SIGNAL \Add0~72_combout\ : std_logic;
SIGNAL \Add0~23\ : std_logic;
SIGNAL \Add0~24_combout\ : std_logic;
SIGNAL \Add0~71_combout\ : std_logic;
SIGNAL \Add0~25\ : std_logic;
SIGNAL \Add0~26_combout\ : std_logic;
SIGNAL \Add0~70_combout\ : std_logic;
SIGNAL \Add0~27\ : std_logic;
SIGNAL \Add0~28_combout\ : std_logic;
SIGNAL \Add0~69_combout\ : std_logic;
SIGNAL \Add0~29\ : std_logic;
SIGNAL \Add0~30_combout\ : std_logic;
SIGNAL \Add0~68_combout\ : std_logic;
SIGNAL \Add0~31\ : std_logic;
SIGNAL \Add0~32_combout\ : std_logic;
SIGNAL \Add0~67_combout\ : std_logic;
SIGNAL \Add0~33\ : std_logic;
SIGNAL \Add0~34_combout\ : std_logic;
SIGNAL \Add0~66_combout\ : std_logic;
SIGNAL \Add0~35\ : std_logic;
SIGNAL \Add0~37\ : std_logic;
SIGNAL \Add0~39\ : std_logic;
SIGNAL \Add0~41\ : std_logic;
SIGNAL \Add0~43\ : std_logic;
SIGNAL \Add0~44_combout\ : std_logic;
SIGNAL \Add0~61_combout\ : std_logic;
SIGNAL \Add0~45\ : std_logic;
SIGNAL \Add0~46_combout\ : std_logic;
SIGNAL \Add0~60_combout\ : std_logic;
SIGNAL \Add0~47\ : std_logic;
SIGNAL \Add0~48_combout\ : std_logic;
SIGNAL \Add0~50_combout\ : std_logic;
SIGNAL \count[25]~feeder_combout\ : std_logic;
SIGNAL \Add0~49\ : std_logic;
SIGNAL \Add0~51_combout\ : std_logic;
SIGNAL \Add0~53_combout\ : std_logic;
SIGNAL \count[26]~feeder_combout\ : std_logic;
SIGNAL \Add0~52\ : std_logic;
SIGNAL \Add0~54_combout\ : std_logic;
SIGNAL \Add0~56_combout\ : std_logic;
SIGNAL \count[27]~feeder_combout\ : std_logic;
SIGNAL \Add0~55\ : std_logic;
SIGNAL \Add0~57_combout\ : std_logic;
SIGNAL \Add0~59_combout\ : std_logic;
SIGNAL count : std_logic_vector(27 DOWNTO 0);

BEGIN

ww_KEY <= KEY;
ww_CLOCK_50 <= CLOCK_50;
LEDR <= ww_LEDR;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\CLOCK_50~clkctrl_INCLK_bus\ <= (gnd & gnd & gnd & \CLOCK_50~combout\);

-- Location: LCCOMB_X48_Y6_N4
\Add0~0\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~0_combout\ = count(0) $ (VCC)
-- \Add0~1\ = CARRY(count(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => count(0),
	datad => VCC,
	combout => \Add0~0_combout\,
	cout => \Add0~1\);

-- Location: LCCOMB_X48_Y6_N8
\Add0~4\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~4_combout\ = (count(2) & (\Add0~3\ $ (GND))) # (!count(2) & (!\Add0~3\ & VCC))
-- \Add0~5\ = CARRY((count(2) & !\Add0~3\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(2),
	datad => VCC,
	cin => \Add0~3\,
	combout => \Add0~4_combout\,
	cout => \Add0~5\);

-- Location: LCCOMB_X48_Y6_N14
\Add0~10\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~10_combout\ = (count(5) & (!\Add0~9\)) # (!count(5) & ((\Add0~9\) # (GND)))
-- \Add0~11\ = CARRY((!\Add0~9\) # (!count(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(5),
	datad => VCC,
	cin => \Add0~9\,
	combout => \Add0~10_combout\,
	cout => \Add0~11\);

-- Location: LCCOMB_X48_Y6_N18
\Add0~14\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~14_combout\ = (count(7) & (!\Add0~13\)) # (!count(7) & ((\Add0~13\) # (GND)))
-- \Add0~15\ = CARRY((!\Add0~13\) # (!count(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(7),
	datad => VCC,
	cin => \Add0~13\,
	combout => \Add0~14_combout\,
	cout => \Add0~15\);

-- Location: LCCOMB_X48_Y6_N22
\Add0~18\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~18_combout\ = (count(9) & (!\Add0~17\)) # (!count(9) & ((\Add0~17\) # (GND)))
-- \Add0~19\ = CARRY((!\Add0~17\) # (!count(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(9),
	datad => VCC,
	cin => \Add0~17\,
	combout => \Add0~18_combout\,
	cout => \Add0~19\);

-- Location: LCCOMB_X48_Y6_N24
\Add0~20\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~20_combout\ = (count(10) & (\Add0~19\ $ (GND))) # (!count(10) & (!\Add0~19\ & VCC))
-- \Add0~21\ = CARRY((count(10) & !\Add0~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(10),
	datad => VCC,
	cin => \Add0~19\,
	combout => \Add0~20_combout\,
	cout => \Add0~21\);

-- Location: LCCOMB_X48_Y5_N8
\Add0~36\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~36_combout\ = (count(18) & (\Add0~35\ $ (GND))) # (!count(18) & (!\Add0~35\ & VCC))
-- \Add0~37\ = CARRY((count(18) & !\Add0~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(18),
	datad => VCC,
	cin => \Add0~35\,
	combout => \Add0~36_combout\,
	cout => \Add0~37\);

-- Location: LCCOMB_X48_Y5_N10
\Add0~38\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~38_combout\ = (count(19) & (!\Add0~37\)) # (!count(19) & ((\Add0~37\) # (GND)))
-- \Add0~39\ = CARRY((!\Add0~37\) # (!count(19)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(19),
	datad => VCC,
	cin => \Add0~37\,
	combout => \Add0~38_combout\,
	cout => \Add0~39\);

-- Location: LCCOMB_X48_Y5_N12
\Add0~40\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~40_combout\ = (count(20) & (\Add0~39\ $ (GND))) # (!count(20) & (!\Add0~39\ & VCC))
-- \Add0~41\ = CARRY((count(20) & !\Add0~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(20),
	datad => VCC,
	cin => \Add0~39\,
	combout => \Add0~40_combout\,
	cout => \Add0~41\);

-- Location: LCCOMB_X48_Y5_N14
\Add0~42\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~42_combout\ = (count(21) & (!\Add0~41\)) # (!count(21) & ((\Add0~41\) # (GND)))
-- \Add0~43\ = CARRY((!\Add0~41\) # (!count(21)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => count(21),
	datad => VCC,
	cin => \Add0~41\,
	combout => \Add0~42_combout\,
	cout => \Add0~43\);

-- Location: LCFF_X47_Y5_N13
\count[21]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~62_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(21));

-- Location: LCFF_X47_Y5_N15
\count[20]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~63_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(20));

-- Location: LCFF_X47_Y5_N21
\count[19]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~64_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(19));

-- Location: LCFF_X47_Y5_N31
\count[18]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~65_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(18));

-- Location: LCFF_X48_Y6_N17
\count[10]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~73_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(10));

-- Location: LCFF_X48_Y6_N21
\count[9]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~74_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(9));

-- Location: LCFF_X48_Y6_N25
\count[7]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~76_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(7));

-- Location: LCFF_X48_Y6_N13
\count[5]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~78_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(5));

-- Location: LCFF_X48_Y6_N7
\count[0]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~83_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(0));

-- Location: LCCOMB_X47_Y5_N12
\Add0~62\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~62_combout\ = (reset_n & \Add0~42_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datac => \Add0~42_combout\,
	combout => \Add0~62_combout\);

-- Location: LCCOMB_X47_Y5_N14
\Add0~63\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~63_combout\ = (reset_n & \Add0~40_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datac => \Add0~40_combout\,
	combout => \Add0~63_combout\);

-- Location: LCCOMB_X47_Y5_N20
\Add0~64\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~64_combout\ = (reset_n & \Add0~38_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datac => \Add0~38_combout\,
	combout => \Add0~64_combout\);

-- Location: LCCOMB_X47_Y5_N30
\Add0~65\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~65_combout\ = (reset_n & \Add0~36_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datac => \Add0~36_combout\,
	combout => \Add0~65_combout\);

-- Location: LCCOMB_X49_Y6_N2
\Add0~73\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~73_combout\ = (reset_n & \Add0~20_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~20_combout\,
	combout => \Add0~73_combout\);

-- Location: LCCOMB_X49_Y6_N28
\Add0~74\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~74_combout\ = (reset_n & \Add0~18_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~18_combout\,
	combout => \Add0~74_combout\);

-- Location: LCCOMB_X49_Y6_N0
\Add0~76\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~76_combout\ = (reset_n & \Add0~14_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~14_combout\,
	combout => \Add0~76_combout\);

-- Location: LCCOMB_X49_Y6_N12
\Add0~78\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~78_combout\ = (reset_n & \Add0~10_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~10_combout\,
	combout => \Add0~78_combout\);

-- Location: LCCOMB_X49_Y6_N10
\Add0~83\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~83_combout\ = (\Add0~0_combout\ & reset_n)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \Add0~0_combout\,
	datac => reset_n,
	combout => \Add0~83_combout\);

-- Location: PIN_L1,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\CLOCK_50~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_CLOCK_50,
	combout => \CLOCK_50~combout\);

-- Location: CLKCTRL_G2
\CLOCK_50~clkctrl\ : cycloneii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \CLOCK_50~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \CLOCK_50~clkctrl_outclk\);

-- Location: PIN_R22,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: Default
\KEY[0]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "register",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "input",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "none",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	inclk => \CLOCK_50~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => GND,
	padio => ww_KEY(0),
	regout => reset_n);

-- Location: LCCOMB_X49_Y10_N16
\count[24]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \count[24]~feeder_combout\ = \Add0~50_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~50_combout\,
	combout => \count[24]~feeder_combout\);

-- Location: LCFF_X49_Y10_N17
\count[24]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \count[24]~feeder_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(24));

-- Location: LCCOMB_X48_Y6_N2
\Add0~81\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~81_combout\ = (\Add0~4_combout\ & reset_n)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \Add0~4_combout\,
	datad => reset_n,
	combout => \Add0~81_combout\);

-- Location: LCFF_X48_Y6_N3
\count[2]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~81_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(2));

-- Location: LCCOMB_X48_Y6_N6
\Add0~2\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~2_combout\ = (count(1) & (!\Add0~1\)) # (!count(1) & ((\Add0~1\) # (GND)))
-- \Add0~3\ = CARRY((!\Add0~1\) # (!count(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(1),
	datad => VCC,
	cin => \Add0~1\,
	combout => \Add0~2_combout\,
	cout => \Add0~3\);

-- Location: LCCOMB_X49_Y6_N8
\Add0~82\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~82_combout\ = (reset_n & \Add0~2_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => reset_n,
	datac => \Add0~2_combout\,
	combout => \Add0~82_combout\);

-- Location: LCFF_X48_Y6_N23
\count[1]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~82_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(1));

-- Location: LCCOMB_X48_Y6_N10
\Add0~6\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~6_combout\ = (count(3) & (!\Add0~5\)) # (!count(3) & ((\Add0~5\) # (GND)))
-- \Add0~7\ = CARRY((!\Add0~5\) # (!count(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(3),
	datad => VCC,
	cin => \Add0~5\,
	combout => \Add0~6_combout\,
	cout => \Add0~7\);

-- Location: LCCOMB_X48_Y6_N0
\Add0~80\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~80_combout\ = (reset_n & \Add0~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datad => \Add0~6_combout\,
	combout => \Add0~80_combout\);

-- Location: LCFF_X48_Y6_N1
\count[3]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~80_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(3));

-- Location: LCCOMB_X48_Y6_N12
\Add0~8\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~8_combout\ = (count(4) & (\Add0~7\ $ (GND))) # (!count(4) & (!\Add0~7\ & VCC))
-- \Add0~9\ = CARRY((count(4) & !\Add0~7\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(4),
	datad => VCC,
	cin => \Add0~7\,
	combout => \Add0~8_combout\,
	cout => \Add0~9\);

-- Location: LCCOMB_X49_Y6_N14
\Add0~79\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~79_combout\ = (reset_n & \Add0~8_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~8_combout\,
	combout => \Add0~79_combout\);

-- Location: LCFF_X48_Y6_N31
\count[4]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~79_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(4));

-- Location: LCCOMB_X48_Y6_N16
\Add0~12\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~12_combout\ = (count(6) & (\Add0~11\ $ (GND))) # (!count(6) & (!\Add0~11\ & VCC))
-- \Add0~13\ = CARRY((count(6) & !\Add0~11\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(6),
	datad => VCC,
	cin => \Add0~11\,
	combout => \Add0~12_combout\,
	cout => \Add0~13\);

-- Location: LCCOMB_X49_Y6_N26
\Add0~77\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~77_combout\ = (reset_n & \Add0~12_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~12_combout\,
	combout => \Add0~77_combout\);

-- Location: LCFF_X48_Y6_N9
\count[6]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~77_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(6));

-- Location: LCCOMB_X48_Y6_N20
\Add0~16\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~16_combout\ = (count(8) & (\Add0~15\ $ (GND))) # (!count(8) & (!\Add0~15\ & VCC))
-- \Add0~17\ = CARRY((count(8) & !\Add0~15\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(8),
	datad => VCC,
	cin => \Add0~15\,
	combout => \Add0~16_combout\,
	cout => \Add0~17\);

-- Location: LCCOMB_X49_Y6_N22
\Add0~75\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~75_combout\ = (reset_n & \Add0~16_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => reset_n,
	datac => \Add0~16_combout\,
	combout => \Add0~75_combout\);

-- Location: LCFF_X48_Y6_N15
\count[8]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~75_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(8));

-- Location: LCCOMB_X48_Y6_N26
\Add0~22\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~22_combout\ = (count(11) & (!\Add0~21\)) # (!count(11) & ((\Add0~21\) # (GND)))
-- \Add0~23\ = CARRY((!\Add0~21\) # (!count(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(11),
	datad => VCC,
	cin => \Add0~21\,
	combout => \Add0~22_combout\,
	cout => \Add0~23\);

-- Location: LCCOMB_X49_Y6_N16
\Add0~72\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~72_combout\ = (reset_n & \Add0~22_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~22_combout\,
	combout => \Add0~72_combout\);

-- Location: LCFF_X48_Y6_N27
\count[11]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~72_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(11));

-- Location: LCCOMB_X48_Y6_N28
\Add0~24\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~24_combout\ = (count(12) & (\Add0~23\ $ (GND))) # (!count(12) & (!\Add0~23\ & VCC))
-- \Add0~25\ = CARRY((count(12) & !\Add0~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(12),
	datad => VCC,
	cin => \Add0~23\,
	combout => \Add0~24_combout\,
	cout => \Add0~25\);

-- Location: LCCOMB_X49_Y6_N18
\Add0~71\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~71_combout\ = (reset_n & \Add0~24_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~24_combout\,
	combout => \Add0~71_combout\);

-- Location: LCFF_X48_Y6_N5
\count[12]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~71_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(12));

-- Location: LCCOMB_X48_Y6_N30
\Add0~26\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~26_combout\ = (count(13) & (!\Add0~25\)) # (!count(13) & ((\Add0~25\) # (GND)))
-- \Add0~27\ = CARRY((!\Add0~25\) # (!count(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(13),
	datad => VCC,
	cin => \Add0~25\,
	combout => \Add0~26_combout\,
	cout => \Add0~27\);

-- Location: LCCOMB_X49_Y6_N24
\Add0~70\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~70_combout\ = (reset_n & \Add0~26_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000011000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => reset_n,
	datac => \Add0~26_combout\,
	combout => \Add0~70_combout\);

-- Location: LCFF_X48_Y6_N19
\count[13]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~70_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(13));

-- Location: LCCOMB_X48_Y5_N0
\Add0~28\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~28_combout\ = (count(14) & (\Add0~27\ $ (GND))) # (!count(14) & (!\Add0~27\ & VCC))
-- \Add0~29\ = CARRY((count(14) & !\Add0~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(14),
	datad => VCC,
	cin => \Add0~27\,
	combout => \Add0~28_combout\,
	cout => \Add0~29\);

-- Location: LCCOMB_X48_Y5_N30
\Add0~69\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~69_combout\ = (reset_n & \Add0~28_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~28_combout\,
	combout => \Add0~69_combout\);

-- Location: LCFF_X48_Y5_N31
\count[14]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~69_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(14));

-- Location: LCCOMB_X48_Y5_N2
\Add0~30\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~30_combout\ = (count(15) & (!\Add0~29\)) # (!count(15) & ((\Add0~29\) # (GND)))
-- \Add0~31\ = CARRY((!\Add0~29\) # (!count(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(15),
	datad => VCC,
	cin => \Add0~29\,
	combout => \Add0~30_combout\,
	cout => \Add0~31\);

-- Location: LCCOMB_X47_Y5_N6
\Add0~68\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~68_combout\ = (reset_n & \Add0~30_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~30_combout\,
	combout => \Add0~68_combout\);

-- Location: LCFF_X48_Y5_N29
\count[15]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~68_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(15));

-- Location: LCCOMB_X48_Y5_N4
\Add0~32\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~32_combout\ = (count(16) & (\Add0~31\ $ (GND))) # (!count(16) & (!\Add0~31\ & VCC))
-- \Add0~33\ = CARRY((count(16) & !\Add0~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(16),
	datad => VCC,
	cin => \Add0~31\,
	combout => \Add0~32_combout\,
	cout => \Add0~33\);

-- Location: LCCOMB_X48_Y5_N28
\Add0~67\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~67_combout\ = (reset_n & \Add0~32_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010101000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datad => \Add0~32_combout\,
	combout => \Add0~67_combout\);

-- Location: LCFF_X48_Y5_N5
\count[16]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	sdata => \Add0~67_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(16));

-- Location: LCCOMB_X48_Y5_N6
\Add0~34\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~34_combout\ = (count(17) & (!\Add0~33\)) # (!count(17) & ((\Add0~33\) # (GND)))
-- \Add0~35\ = CARRY((!\Add0~33\) # (!count(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(17),
	datad => VCC,
	cin => \Add0~33\,
	combout => \Add0~34_combout\,
	cout => \Add0~35\);

-- Location: LCCOMB_X47_Y5_N16
\Add0~66\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~66_combout\ = (reset_n & \Add0~34_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~34_combout\,
	combout => \Add0~66_combout\);

-- Location: LCFF_X47_Y5_N17
\count[17]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~66_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(17));

-- Location: LCCOMB_X48_Y5_N16
\Add0~44\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~44_combout\ = (count(22) & (\Add0~43\ $ (GND))) # (!count(22) & (!\Add0~43\ & VCC))
-- \Add0~45\ = CARRY((count(22) & !\Add0~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(22),
	datad => VCC,
	cin => \Add0~43\,
	combout => \Add0~44_combout\,
	cout => \Add0~45\);

-- Location: LCCOMB_X47_Y5_N22
\Add0~61\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~61_combout\ = (reset_n & \Add0~44_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datac => \Add0~44_combout\,
	combout => \Add0~61_combout\);

-- Location: LCFF_X47_Y5_N23
\count[22]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~61_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(22));

-- Location: LCCOMB_X48_Y5_N18
\Add0~46\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~46_combout\ = (count(23) & (!\Add0~45\)) # (!count(23) & ((\Add0~45\) # (GND)))
-- \Add0~47\ = CARRY((!\Add0~45\) # (!count(23)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(23),
	datad => VCC,
	cin => \Add0~45\,
	combout => \Add0~46_combout\,
	cout => \Add0~47\);

-- Location: LCCOMB_X47_Y5_N4
\Add0~60\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~60_combout\ = (reset_n & \Add0~46_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~46_combout\,
	combout => \Add0~60_combout\);

-- Location: LCFF_X47_Y5_N5
\count[23]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \Add0~60_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(23));

-- Location: LCCOMB_X48_Y5_N20
\Add0~48\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~48_combout\ = (count(24) & (\Add0~47\ $ (GND))) # (!count(24) & (!\Add0~47\ & VCC))
-- \Add0~49\ = CARRY((count(24) & !\Add0~47\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(24),
	datad => VCC,
	cin => \Add0~47\,
	combout => \Add0~48_combout\,
	cout => \Add0~49\);

-- Location: LCCOMB_X49_Y10_N6
\Add0~50\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~50_combout\ = (reset_n & \Add0~48_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~48_combout\,
	combout => \Add0~50_combout\);

-- Location: LCCOMB_X49_Y8_N20
\count[25]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \count[25]~feeder_combout\ = \Add0~53_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~53_combout\,
	combout => \count[25]~feeder_combout\);

-- Location: LCFF_X49_Y8_N21
\count[25]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \count[25]~feeder_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(25));

-- Location: LCCOMB_X48_Y5_N22
\Add0~51\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~51_combout\ = (count(25) & (!\Add0~49\)) # (!count(25) & ((\Add0~49\) # (GND)))
-- \Add0~52\ = CARRY((!\Add0~49\) # (!count(25)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(25),
	datad => VCC,
	cin => \Add0~49\,
	combout => \Add0~51_combout\,
	cout => \Add0~52\);

-- Location: LCCOMB_X49_Y8_N6
\Add0~53\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~53_combout\ = (reset_n & \Add0~51_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => reset_n,
	datac => \Add0~51_combout\,
	combout => \Add0~53_combout\);

-- Location: LCCOMB_X49_Y4_N0
\count[26]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \count[26]~feeder_combout\ = \Add0~56_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~56_combout\,
	combout => \count[26]~feeder_combout\);

-- Location: LCFF_X49_Y4_N1
\count[26]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \count[26]~feeder_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(26));

-- Location: LCCOMB_X48_Y5_N24
\Add0~54\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~54_combout\ = (count(26) & (\Add0~52\ $ (GND))) # (!count(26) & (!\Add0~52\ & VCC))
-- \Add0~55\ = CARRY((count(26) & !\Add0~52\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => count(26),
	datad => VCC,
	cin => \Add0~52\,
	combout => \Add0~54_combout\,
	cout => \Add0~55\);

-- Location: LCCOMB_X49_Y4_N6
\Add0~56\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~56_combout\ = (reset_n & \Add0~54_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~54_combout\,
	combout => \Add0~56_combout\);

-- Location: LCCOMB_X49_Y2_N24
\count[27]~feeder\ : cycloneii_lcell_comb
-- Equation(s):
-- \count[27]~feeder_combout\ = \Add0~59_combout\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \Add0~59_combout\,
	combout => \count[27]~feeder_combout\);

-- Location: LCFF_X49_Y2_N25
\count[27]\ : cycloneii_lcell_ff
PORT MAP (
	clk => \CLOCK_50~clkctrl_outclk\,
	datain => \count[27]~feeder_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	regout => count(27));

-- Location: LCCOMB_X48_Y5_N26
\Add0~57\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~57_combout\ = \Add0~55\ $ (count(27))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => count(27),
	cin => \Add0~55\,
	combout => \Add0~57_combout\);

-- Location: LCCOMB_X49_Y2_N6
\Add0~59\ : cycloneii_lcell_comb
-- Equation(s):
-- \Add0~59_combout\ = (reset_n & \Add0~57_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => reset_n,
	datad => \Add0~57_combout\,
	combout => \Add0~59_combout\);

-- Location: PIN_R20,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
\LEDR[0]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "register",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \Add0~50_combout\,
	outclk => \CLOCK_50~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_LEDR(0));

-- Location: PIN_R19,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
\LEDR[1]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "register",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \Add0~53_combout\,
	outclk => \CLOCK_50~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_LEDR(1));

-- Location: PIN_U19,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
\LEDR[2]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "register",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \Add0~56_combout\,
	outclk => \CLOCK_50~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_LEDR(2));

-- Location: PIN_Y19,	 I/O Standard: 3.3-V LVTTL,	 Current Strength: 4mA
\LEDR[3]~I\ : cycloneii_io
-- pragma translate_off
GENERIC MAP (
	input_async_reset => "none",
	input_power_up => "low",
	input_register_mode => "none",
	input_sync_reset => "none",
	oe_async_reset => "none",
	oe_power_up => "low",
	oe_register_mode => "none",
	oe_sync_reset => "none",
	operation_mode => "output",
	output_async_reset => "none",
	output_power_up => "low",
	output_register_mode => "register",
	output_sync_reset => "none")
-- pragma translate_on
PORT MAP (
	datain => \Add0~59_combout\,
	outclk => \CLOCK_50~clkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	devoe => ww_devoe,
	oe => VCC,
	padio => ww_LEDR(3));
END structure;


