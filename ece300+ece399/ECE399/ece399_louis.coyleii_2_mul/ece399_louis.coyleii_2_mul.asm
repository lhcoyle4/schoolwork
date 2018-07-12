; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Assignment: 2 - Shift-Add Multiplier
; Date: 09/21/14

; Question: What changes need to be made to make this algorithm work for negative numbers?
; Allow the input of negative numbers. Use LDRS when loading the scanned values from memory into registers.
; Check the N flag after loading each one, if it is set after loading the first value, then store 1 in a register.
; If the N flag is set again after storing the second value, then clear the register. Convert the values to positive #'s.
; Multiply as normal, then before printing the product, check your 'negative register'. If it is set
; (only one value was negative), then convert the product to a negative number before printing it.
; The reverse subtract instruction can be used to convert between negative and positive:
; RSB r0, r0, #0 ; subtracts r0 from 0 and puts the result into r0 - effectively does a unary negate of r0

; 4/11/15 - actually, nothing needs to be done for it to work with negatives.

  .data
mul1: .space 4
mul2: .space 4

  .text
  .global printf
  .global scanf
  .global main

mul1p: .word mul2
mul2p: .word mul1
multiplier .set r2
multiplicand .set r3

printhelp:
  .align 4
  .cstring "Enter two numbers to multiply (e.g. - 4 2), then hit enter.\n"

scan:
  .align 4
  .cstring "%d %d"

printret:
  .align 4
  .cstring "Product is: %d\n"

main:
  PUSH {lr, r4}

  ; inform the user how to use the program
  ADR r0, printhelp
  BL printf

  ; read in their input
  ADR r0, scan
  LDR r1, mul1p
  LDR r2, mul2p
  BL scanf

  ; store their input in registers for calculation
  LDR r1, mul1p
  LDR r2, mul2p
  LDR r3, [r1]
  LDR r2, [r2]

  ; if r2 is 1, then return the value of r3
  CMP r2, #1
  ITT EQ
  MOVEQ r1, r3
  BEQ return

  ; if r3 is 1 then return the value of r2
  CMP r3, #1
  ITT EQ
  MOVEQ r1, r2
  BEQ return

  ; if either register is 0, then return 0
  MOV r1, #0
  CBZ r2, return
  CBZ r3, return

  ; determine which term is smaller, by counting leading zeroes
  CLZ r0, r2
  CLZ r1, r3

  ; and comparing the number of leading zeroes for each term
  CMP r1, r0
  ITTTT GT

  ; if r3 has more leading zeroes than r2, then r3 should be the multiplier
  ; so we can throw away the number of leading zeroes for r2, overwriting r0 with r2
  MOVGT r0, r2

  ; then store r3 into r2, now using the name 'multiplier' for the register
  MOVGT multiplier, r3

  ; then restore the multiplicand to its register
  MOVGT multiplicand, r0

  ; and use r0 as the register to minimize iterations for the loop (contains number of leading zeroes for the mulitiplier)
  ; this way, we'll be able to add 1 to r0 each iteration of the loop, so that we only check bits of the multiplier up to the msb that is set
  ; i.e. - if bit[31] of the multiplier is set, CLZ returns 0, so we will have to do 32 iterations
  ; but if bit[8] is the msb that is set, then CLZ returns 23, so we only need to do 9 iterations
  MOVGT r0, r1

  ; otherwise r3 had less than or equal leading zeroes than r2, so r2 is the multiplier, and everything is already in its right place
  ; but, r1 still contains the number of leading zeroes for r3, and we want to use it for the product, so we clear it
  MOV r1, #0

  ; we also need a register for the bit position to check, r0 - r3 are in use, so we choose r4
  ; the first bit must be set so that it can be used with the TST instruction, we will be left shifting this register each iteration
  MOV r4, #1

mul:
  ; if the current bit of multiplier is 1
  TST multiplier, r4
  IT NE

  ; then add the shifted multiplicand to the product
  ADDNE r1, multiplicand

  ; then increment the loop iterator
  ADD r0, #1

  ; left shift the bit testing register
  LSL r4, r4, #1

  ; left shift the multiplicand
  LSL multiplicand, multiplicand, #1

  ; and determine if we must return to the start of the loop
  CMP r0, #32
  IT LT
  BLT mul

return:
  ADR r0, printret
  BL printf
  MOVS r0, #0
  POP {pc, r4}
  .end
