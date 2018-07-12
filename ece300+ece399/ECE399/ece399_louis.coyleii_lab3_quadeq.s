	.data
arg1: .float 0
arg2: .float 0
arg3: .float 0

    .text
argp1: .word arg1
argp2: .word arg2
argp3: .word arg3
    .global main
    .global printf
    .global scanf
main:
    PUSH {lr}

	; read three values from console using scanf 
    LDR r1, argp1
    LDR r2, argp2
    LDR r3, argp3
    ADR r0, read_format
    BL scanf

	; restore the addresses of the terms to the registers
    LDR r1, argp1
    LDR r2, argp2
    LDR r3, argp3

	; load the floating point values into the floating point registers
    VLDR s1, [r1]
    VLDR s2, [r2]
    VLDR s3, [r3]
    
    ; sqr b by multiplying it with itself, store in a temporary register
    VMUL.F32 s4, s2, s2
    
    ; multiply a and c together, storing them in another temp register
    VMUL.F32 s5, s1, s3
    
    ; move 4 into a fpu register
    VMOV.F32 s6, #4.0
    
    ; multiply 4ac
    VMUL.F32 s5, s5, s6
    
    ; subtract 4ac from b^2 and store in the register previously being used for b^2
    VSUB.F32 s4, s4, s5
    
    ; test if the result of this subtraction is negative
    VCMP.F32 s4, #0.0
    VMRS APSR_nzcv, FPSCR
   	ITTT LT
   	ADRLT r0, print_complex
   	BLLT printf
   	BLT exit
    
    ; find the square root of this subtraction
    VSQRT.F32 s4, s4
    
    ; find the opposite of b
    VNEG.F32 s2, s2
    
    ; add the square root to the opposite of b and store in a temporary
    VADD.F32 s5, s2, s4
    
    ; subtract the square root from the opposite of b and store in a temp
    VSUB.F32 s6, s2, s4
    
    ; move 2 into a fpu register
    VMOV.F32 s7, #2.0
    
    ; multiply a by 2
    VMUL.F32 s1, s1, s7
    
    ; divide s5 and s6 by 2a, these are the answers
    VDIV.F32 s5, s5, s1
    VDIV.F32 s6, s6, s1
    
    ; move the first root into r2
    VMOV r2, s5
    
    ; convert root 1 to double
    LSL r1, r2, #29
    ASR r2, #3
    BIC r2, #0x70000000
    ADD r2, #0x38000000
    
    ; print the sum
    ADR r0, format
    BL printf
    
    ; move the second root into r4
    VMOV r2, s6
 
    ; convert root 2 to double
    LSL r1, r2, #29
    ASR r2, #3
    BIC r2, #0x70000000
    ADD r2, #0x38000000
    
    ; print the sum
    ADR r0, format
    BL printf
    
exit:

    POP {pc}    ; return
    
    .align 4
format:
    .cstring "%f\n"
    
    .align 4
print_complex:
	.cstring "Negative under the square root, answer will be complex.\n"
    
    .align 4
read_format: 
    .cstring "%f %f %f"
pi:
    .float 3.1415926535
    