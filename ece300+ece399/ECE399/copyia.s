  .text
  
  ; r0 will contain the source address to copy values from memory
source: .set r0

  ; r1 will contain the dest address to copy values into memory 
dest: .set r1

  ; r2 will contain the offset from source address to copy values up to
n: .set r2

copyIAbyte .macro source, dest, n
  LDRB r4, [source]
  STRB r4, [dest]
  
  ADD source, #1
  ADD dest, #1
  SUB n, #1
  .endm 
  
  ; source > dest, so we can copy starting at the beginning of source into the beginning of dest
  ; and increment the addresses each iteration
copyIA:
  PUSH {lr, r4 - r12}
  
  ; determine if source and destination are on 4-byte boundaries
  AND r3, source, #3
  AND r4, dest, #3
  
  ; find out which address is further away from being on 4-byte boundary 
  CMP r3, r4
  IT LE
  ; and move the number of bytes away from word boundary into r3
  MOVLE r3, r4
  
  ; if both addresses are word aligned, start doing bulk moves
  CBZ r3, copyIA168
  
  ; otherwise, do single byte moves until r3 is 0 (both addresses are word-aligned)
align:
  copyIAbyte source, dest, n
  SUBS r3, #1
  ; if r3 is not 0, keep iterating
  BNE align
  
copyIA168:
  ; if there are greater than or equal to 42 values (168 bytes) to copy, then copy 42 of them in one go
  CMP n, #168
  ; otherwise, copy 40 at a time
  BLT copyIA40 
  
  ; loads the registers in the curly brackets with word values from memory addresses starting at the first operand
  ; and writes the final address that is loaded from source back into source 
  LDMIA source!, {r3 - r12}
  VLDMIA.32 source!, {s0 - s31}
  
  ; stores the word values from the registers in the curly brackets to memory addresses starting at the first operand
  ; and writes the final address that is stored to dest back into dest
  STMIA dest!, {r3 - r12}
  VSTMIA.32 dest!, {s0 - s31}
  
  ; decrement the number of bytes to be copied by the number of bytes that were copied (168)
  SUBS n, #168
  
  ; if there are no more bytes to copy, then return
  BEQ return
  
  ; otherwise, try to copy 168 bytes again
  B copyIA168
  
copyIA40:
  ; if there are greater than or equal to 10 values (40 bytes) to copy, then copy 10 in one go
  CMP n, #40
  
  ; otherwise copy 1 at a time
  BLT copyIA4
  
  ; copy over 10 values at a time, incrementing the addresses by 40 each time
  LDMIA source!, {r3 - r12}
  STMIA dest!, {r3 - r12}
  
  ; decrement the number of bytes to be copied by the number of bytes that were copied (40)
  SUB n, #40
  
  ; if there are no more bytes to copy, then return
  CBZ n, return
  
  ; otherwise, try to copy 40 bytes again
  B copyIA40
  
copyIA4:
  CMP n, #4
  BLT copyIA1
  
  ; copy over 4 bytes at a time, incrementing the addresses by 4 each time
  LDMIA source!, {r3}
  STMIA dest!, {r3}
  
  ; decrement the number of bytes to be copied by the number of bytes that were copied (4)
  SUB n, #4
  
  ; if there are no more bytes to copy, then return
  CBZ n, return
  
  ; otherwise, keep copying 4 bytes at a time
  B copyIA4
  
copyIA1:
  copyIAbyte source, dest, n
  
  CBZ n, return
  B copyIA1

return:
  POP {pc, r4 - r12}
  .end