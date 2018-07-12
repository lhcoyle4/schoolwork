; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Lab: 1
; Date: 09/18/14


	.global main
	.global gcd
gcd:
	CMP r0, r1
	IT EQ
	MOVEQ pc, lr
	ITE GT
	SUBGT r0,r1
	SUBLE r1,r0
	B gcd
	.end
