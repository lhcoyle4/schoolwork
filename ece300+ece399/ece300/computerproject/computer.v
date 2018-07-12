module computer (CLOCK_50, GPIO_1);
	input CLOCK_50;
	output [15:0] GPIO_1;
	//ROM
	//RAM
	
	// PORTA is memory mapped to 11'h7FF
	// assign GPIO[15:8] = RAM[11'h7FF];
	program_counter pc_();
	instruction_decoder id_();
	status_register sr_();
	alu alu_();
	program_terminal pt_();
	uart uart_();
	
endmodule