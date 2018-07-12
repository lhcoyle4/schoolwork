; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Assignment: 1 - Part 1
; Date: 09/15/14

	.text              ;indicates that the following section is executable code
	.global printf     ;tells the assembler that this symbol is either defined in the current file or referenced from another. In this case, printf is defined in another file, so the assembler will choose .ref
	.global main       ;In this case the assembler will choose .def because the symbol is defined in this file.
main:                  ;label that assigns a run-time address to the following code, may be jumped to or referred to by linker
	PUSH {lr}          ;saves the address in the link register, which is the address of the line of code after the jump to this function
	ADR r0, format     ;writes the address of the format string to r0, for use by printf
	BL printf          ;branches and links to the c function printf, which is locatable through the global symbol above
	MOVS r0, #0        ;moves the literal 0 into the r0 register, and updates the condition flags, reporting a successful exit from program (return 0;)
	POP {pc}           ;restores the address from the link register to the program counter, restoring program execution the the line after the jump to this function
format:                ;label to the format specifier string for printf
	.align 4           ;align the data on 4 byte boundaries
	.cstring "Hello\n" ;cstring is an array of characters followed by a null-terminator 
	.end               ;end of the program
