; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Assignment: 6 - arm16 strcpy
; Date: 11/25/14

  .text
  .state16

  MOV r0, #0   ; source address
  MOV r1, #10  ; dest address
  MOV r2, #0   ; to store each word of the string
  MOV r3, #0   ; to save each word during byte testing
  MOV r6, #0   ; to count the number of words copied
  MOV r7, #0   ; number of bits to rotate word by

copy:

  MOV r4, #255  ; initialize register to and words with to get bytes
  MOV r5, #0    ; and register to count number of bytes checked

  LDR r2, [r0]    ; load and store 1 word
  STR r2, [r1]

  ADD r0, #4    ; increment source and dest addresses to next word
  ADD r1, #4
  ADD r6, #1    ; increment the number of words copied

checknull:

  MOV r3, r2  ; save loaded value
  ROR r3, r7  ; rotate the word to check the next byte for null terminator

  AND r3, r4  ; select the rightmost byte

  CMP r3, #0  ; check if it is the null terminator
  BEQ verify  ; if so, end program

  ADD r7, #8
  ADD r5, #1  ; increment the counter for number of bytes checked

  CMP r5, #4  ; if all bytes have been checked and there is no null
  BEQ copy    ; then return to the start of the program (after initialization)
  B checknull

verify:
  LDR r2, [r0]  ; load r2 with the source word
  LDR r3, [r1]  ; and r3 with the dest word

  SUB r0, #4  ; decrement source and dest addresses to previous word
  SUB r1, #4  ; they are at the last word because of previous instructions

  SUB r6, #1  ; decrement the number of words that have been copied

  CMP r2, r3  ; cmp the two
  BNE fail    ; if they are not equivalent, the strcpy failed
  CMP r6, #0  ; if there are no words left to copy, and strcpy didnt fail
  BEQ success ; then report a success
  B verify    ; otherwise there are still words to check


fail:
  MOV r0, #1 ; 1 is exit failure

success:
  MOV r0, #0  ; 0 is exit success
