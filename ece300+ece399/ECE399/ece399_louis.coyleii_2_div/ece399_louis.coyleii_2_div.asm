; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Assignment: 2 - Shift-Sub Divider
; Date: 09/21/14

  .data
dividend: .space 4
divisor:  .space 4

  .text
  .global printf
  .global scanf
  .global main

dividendp: .word dividend
divisorp:  .word divisor
quotient  .set r1
remainder .set r2
dividendreg .set r3
divisorreg  .set r4
bittester .set r5

printhelp:
  .align 4
  .cstring "Enter two numbers to divide, dividend followed by divisor (e.g. - 8 4 will return 2), then hit enter.\n"

scan:
  .align 4
  .cstring "%d %d"

printret:
  .align 4
  .cstring "Quotient is: %d, remainder is: %d.\n"

printdiv0:
  .align 4
  .cstring "Cannot divide by 0.\n"

main:
  PUSH {lr, r4, r5}

  ; inform the user how to use the program
  ADR r0, printhelp
  BL printf

  ; read in their input
  ADR r0, scan
  LDR r1, dividendp
  LDR r2, divisorp
  BL scanf

  ; store their input in registers for calculation
  LDR r1, dividendp
  LDR r2, divisorp
  LDR divisorreg, [r2]
  LDR dividendreg, [r1]

  ; we need to know the msb that is set of the dividend, so we will CLZ of the dividend
  CLZ r0, dividendreg

  ; if bit[31] is set, CLZ will return 0, if bit[8] is set, CLZ will return 23
  ; in order to store the actual position of the msb that is set, we move the total number of bits (0-indexed) into a temp register
  MOV r1, #31

  ; and subtract the number of leading zeroes from it
  SUB r1, r0

  ; left shift the bittester by the number of bits in dividend, for testing whether a bit in the dividend is set
  MOV bittester, #1
  LSL bittester, r1

  ; now, we should check the msb that is set of the divisor
  CLZ r0, divisorreg

  ; move the total number of bits into a different temp register
  MOV r2, #31

  ; and subtract the number of leading zeroes from it
  SUB r2, r0

  ; if the divisor is bigger than the dividend (the divisor has fewer leading zeroes)
  CMP r2, r1

  ITTT GT
  ; then the divisor can't go into the dividend, and the remainder is the dividend
  MOVGT quotient, #0
  MOVGT remainder, dividendreg
  BGT return

  ; if dividing by 1, then the quotient is the value of dividend (x/1 = x)
  CMP divisorreg, #1
  ITTT EQ
  MOVEQ quotient, dividendreg
  MOVEQ remainder, #0
  BEQ return

  ; if dividend is 1 then the remainder is 1 (already checked for divisor = 1), and quotient is 0 (1/x = 0 [x > 1], r = x)
  CMP dividendreg, #1
  ITTT EQ
  MOVEQ quotient, #0
  MOVEQ remainder, #1
  BEQ return

  ; if dividend register is 0, then return 0, if divisor is 0, then print divide by 0 error
  MOV quotient, #0
  MOV remainder, #0
  CBZ dividendreg, return
  CBZ divisorreg, div0

div:
  ; check if the bit at each position in the dividend is set
  TST dividendreg, bittester

  IT NE
  ; if the bit is set, add it to the remainder
  ADDNE remainder, #1

  ; compare the divisor to the shifted remainder + extracted field
  CMP divisorreg, remainder

  ITT LE
  ; if the divisor is less than the remainder, then subtract it, storing result in remainder
  SUBLE remainder, remainder, divisorreg

  ; add bittester to quotient in order to record that the divisor is subtracted from this field
  ADDLE quotient, bittester

  ; right shift the bittester, to look at the next bit in the dividend
  LSR bittester, #1

  ; if bittester is 0 then the loop is done
  CBZ bittester, return

  ; shift the remainder over by one each iteration, so that the extracted bit can be added to it in the correct position
  LSL remainder, remainder, #1

  ; keep iterating
  B div

div0:
  ADR r0, printdiv0
  BL printf
  B end

return:
  ADR r0, printret
  BL printf

end:
  MOVS r0, #0
  POP {pc, r4, r5}
  .end
