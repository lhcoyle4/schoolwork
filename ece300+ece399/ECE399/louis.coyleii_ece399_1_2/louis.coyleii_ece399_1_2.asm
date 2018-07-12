; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Assignment: 1 - Part 2
; Date: 09/16/14

	.text                     ;indicates that the following section is executable code
	.global printf            ;tells the assembler that this symbol is either defined in the current file or referenced from another. In this case, printf is defined in another file, so the assembler will choose .ref
	.global main              ;In this case the assembler will choose .def because the symbol is defined in this file.
main:                         ;label that assigns a run-time address to the following code, may be jumped to or referred to by linker
	PUSH {lr, r4, r5, r6, r7} ;saves the address in the link register, which is the address of the line of code after the jump to this function, and the values in the registers that will be used
	MOV r1, #1				  ;initialize the 2nd argument to printf with the first integer in the fib sequence to print, this will be updated every iteration with the next term
	MOV r4, #0				  ;initialize the previous register with starting value of fibonacci sequence
	MOV r5, #1				  ;initialize the current register with 2nd term of the fibonacci sequence
	MOV r6, #1				  ;initialize the temporary register for holding the addition of current + previous fibonacci terms, will also be used to print the value of the recently calculated fib term
	MOV r7, #20		          ;writes 20 to register 4, to be used as a loop iterator
fib:						  ;label to allow branching back to the start of the fibonacci loop
	ADR r0, format     	      ;writes the address of the format string to r0, for use by printf
	BL printf                 ;branches and links to the c function printf, which is locatable through the global symbol above
	ADD r6, r4, r5			  ;adds the current and previous terms in the fibonacci sequence, to get the next term
	MOV r4, r5				  ;move the value in the current register for the fibonacci sequence into the previous register
	MOV r5, r6				  ;move the result of the addition of the fibonacci terms from the temporary register into the current register
	MOV r1, r5			      ;update the 2nd argument to the printf function with the current term of the fibonacci sequence
	SUBS r7, #1				  ;subtract 1 from the loop iterator, and update the condition flags, for the following branch instruction
	BNE fib 		  		  ;branch back to the start of the fibonacci subroutine, if there are more iterations to complete (branches only if the zero condition flag was not set by the previous SUBS instruction)
	MOVS r0, #0               ;moves the literal 0 into the r0 register, and updates the condition flags, reporting a successful exit from program (return 0;)
	POP {pc, r4, r5, r6, r7}  ;restores the address from the link register to the program counter, restoring program execution the the line after the jump to this function
format:                   	  ;label to the format specifier string for printf
	.align 4                  ;align the data on 4 byte boundaries
	.cstring "%d\n"           ;cstring is an array of characters followed by a null-terminator
	.end                      ;end of the program
