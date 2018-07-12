; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Lab: 1
; Date: 09/18/14

	.data
term1: .space 4
term2: .space 4
	.text
term1p: .word term1
term2p: .word term2
	.global printf
	.global scanf
	.global main
	.global gcd
main:
	ADR r0, scan
	LDR r1, term1p
	LDR r2, term2p
	BL scanf
	LDR r1, term1p
	LDR r2, term2p
	LDR r0, [r1]
	LDR r1, [r2]
	BL gcd
	ADR r0, print
	BL printf
scan:
	.align 4
	.cstring "%d %d"
print:
	.align 4
	.cstring "GCD is: %d\n"
	.end
