  .text
  
  ; r0 will contain the source address to copy values from memory
source: .set r0

  ; r1 will contain the dest address to copy values into memory 
dest: .set r1

  ; r2 will contain the offset from source address to copy values up to
n: .set r2

copyDBbyte .macro source, dest, n
  LDRB r4, [source]
  STRB r4, [dest]
  
  SUB source, #1
  SUB dest, #1
  SUB n, #1
  .endm
  
  ; dest > source, so the memory addresses start at the end of the blocks to move 
  ; and the addresses are decremented each iteration
copyDB:
  PUSH {lr, r4 - r12}
  
  ; determine if source and destination are on 4-byte boundaries
  AND r3, source, #3
  AND r4, dest, #3
  
  ; find out which address is further away from being on 4-byte boundary 
  CMP r3, r4
  IT GE
  ; and move the number of bytes away from word boundary into r3
  MOVGE r3, r4
  
  ; if both addresses are word aligned, start doing bulk moves
  CBZ r3, copyDB168
  
  ; otherwise, do single byte moves until r3 is 0 (both addresses are word-aligned)
align:
  copyDBbyte source, dest, n
  SUBS r3, #1
  ; if r3 is not 0, keep iterating
  BNE align 
   
copyDB168:
  ; if there are greater than or equal to 168 bytes to copy, then copy 168 in one go
  CMP n, #168
  ; otherwise, copy 40 at a time
  BLT copyDB40
  
  ; loads the registers in the curly brackets with word values from memory addresses starting at the first operand
  ; and decrements the address by 40 and 128 each time
  LDMDB source!, {r3 - r12}
  VLDMDB.32 source!, {s0 - s31}
  
  ; stores the word values from the registers in the curly brackets to memory addresses starting at the first operand
  ; and decrements the address by 40 and 128 each time
  STMDB dest!, {r3 - r12}
  VSTMDB.32 dest!, {s0 - s31}
  
  ; decrement the number of bytes to be copied by the number that were copied (168)
  SUBS n, #168
  
  ; if there are no more bytes to copy, then return
  BEQ return
  
  ; otherwise, try to copy 168 bytes again
  B copyDB168
  
copyDB40:
  ; if there are greater than or equal to 40 bytes to copy, then copy 40 in one go
  CMP n, #40
  
  ; otherwise, copy 1 at a time
  BLT copyDB4
  
  ; copy over 10 values at a time, decrementing the addresses by 40 each time
  LDMDB source!, {r3 - r12}
  STMDB dest!, {r3 - r12}
  
  ; decrement the number of bytes to be copied by the number that were copied (40)
  SUB n, #40
  
  ; if there are no more bytes to copy, then return
  CBZ n, return
  
  ; otherwise, try to copy 40 bytes again
  B copyDB40
  
copyDB4:
  CMP n, #4
  BLT copyDB1
  ; copy over 1 value at at time, decrementing the address by 4 each time
  LDMDB source!, {r3}
  STMDB dest!, {r3}
  
  ; decrement the number of bytes to be copied by the number that were copied (4)
  SUB n, #4
  
  ; if there are no more bytes to copy, then return
  CBZ n, return
  
  ; otherwise, keep copying 4 bytes at a time
  B copyDB4
  
copyDB1:
  copyDBbyte source, dest, n
  
  CBZ n, return
  B copyDB1
  
return:
  POP {pc, r4 - r12}
  .end