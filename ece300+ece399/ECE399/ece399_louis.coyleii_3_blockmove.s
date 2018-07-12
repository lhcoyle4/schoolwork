; Louis Coyle II
; Email: lhcoyle4@gmail.com
; DigiPen login: louis.coyleii
; Course: ECE399
; Assignment: 3 - blockmove
; Date: 09/28/14

  .text
  ; the blockmove subroutine that is called in main.c is defined in this file
  .global blockmove

  ; r0 will contain the source address to copy values from memory
source: .set r0

  ; r1 will contain the dest address to copy values into memory 
dest: .set r1

  ; r2 will contain the offset from source address to copy values up to
n: .set r2

copyIAbyte .macro source, dest, n
  LDRB r5, [source]
  STRB r5, [dest]
  
  ADD source, #1
  ADD dest, #1
  SUBS n, #1
  BEQ return
  .endm 

copyDBbyte .macro source, dest, n
  SUB source, #1
  SUB dest, #1
  
  LDRB r5, [source]
  STRB r5, [dest]
 
  SUBS n, #1
  BEQ return
  .endm
  
blockmove:
  PUSH {lr, r4 - r12}
   
  ; compare the destination address to the start address, to check for special cases
  CMP dest, source
  
  ; if dest == source, then we don't need to copy anything, so return immediately
  BEQ return
  
  ; if source > dest, then we can copy starting at the beginning of both addresses
  BLT copyIA

  ; otherwise, if dest > source, then we should copy starting at the end (to deal with overlap)
  B copyDB
  
  ; source > dest, so we can copy starting at the beginning of source into the beginning of dest
  ; and increment the addresses each iteration
copyIA:  
  ; determine if source and destination are on 4-byte boundaries
  AND r3, source, #3
  AND r4, dest, #3
  
  ; if both addresses are word aligned, check to see if can do bulk reads and writes
  CMP r3, r4
  IT EQ
  CMPEQ r3, #0
  BEQ copyIA168
  
  ; otherwise, do single byte moves until r4 is 4 (at least destination address is word-aligned)
alignIA:
  copyIAbyte source, dest, n
  ADD r4, #1
  ADD r3, #1
  CMP r4, #4
  ; if r4 is not 4, keep iterating
  BNE alignIA
  
  ; determine if bulk reads can be made, if so, begin copying 168 bytes at a time
  CMP r3, #4
  BEQ copyIA168

  ; otherwise, do single word reads with bulk writes
wordread40:
  CMP n, #40
  BLT wordread20
  ; if not, then load the registers individually
  LDR r3, [source], #4
  LDR r4, [source], #4
  LDR r5, [source], #4
  LDR r6, [source], #4
  LDR r7, [source], #4
  LDR r8, [source], #4
  LDR r9, [source], #4
  LDR r10, [source], #4
  LDR r11, [source], #4
  LDR r12, [source], #4
  ; then store them in one go
  STMIA dest!, {r3 - r12}
  SUBS n, #40
  BEQ return
  B wordread40
  
wordread20:
  CMP n, #20
  BLT wordread4
  ; load up 20 bytes into registers
  LDR r3, [source], #4
  LDR r4, [source], #4
  LDR r5, [source], #4
  LDR r6, [source], #4
  LDR r7, [source], #4
  ; then store all 20 bytes in one go
  STMIA dest!, {r3 - r7}
  SUBS n, #20
  BEQ return
  B wordread20
  
wordread4:
  CMP n, #4
  ; if there are less than 4 bytes left, then move to load/storing 1 at a time
  BLT copyIA1
  ; load up 4 bytes into one register
  LDR r3, [source], #4
  ; then store them
  STMIA dest!, {r3}
  SUBS n, #4
  BEQ return
  B wordread4
  
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
  SUBS n, #40
  
  ; if there are no more bytes to copy, then return
  BEQ return
  
  ; otherwise, try to copy 40 bytes again
  B copyIA40
  
copyIA4:
  ; try to copy 4 bytes at a time
  CMP n, #4
  ; if there are less than 4 bytes to copy, then copy 1 at a time
  BLT copyIA1
  
  ; copy over 4 bytes at a time, incrementing the addresses by 4 each time
  LDMIA source!, {r3}
  STMIA dest!, {r3}
  
  ; decrement the number of bytes to be copied by the number of bytes that were copied (4)
  SUBS n, #4
  
  ; if there are no more bytes to copy, then return
  BEQ return
  
  ; otherwise, keep copying 4 bytes at a time
  B copyIA4
  
copyIA1:
  ; copy single bytes at a time, branching to return if n becomes 0
  copyIAbyte source, dest, n
  
  ; if there are more bytes to copy, keep doing so
  B copyIA1

  
  ; dest > source, so the memory addresses start at the end of the blocks to move 
  ; and the addresses are decremented each iteration
copyDB:
  ; add the offset to source and dest, and then branch to the loop which decrements from the address
  ADD source, n
  ADD dest, n

  ; determine if source and destination are on 4-byte boundaries
  AND r3, source, #3
  AND r4, dest, #3
  
  ; if both addresses are word aligned, check to see if can do bulk reads and writes
  CMP r3, r4
  IT EQ
  CMPEQ r3, #0
  BEQ copyDB168
 
  ; otherwise, do single byte moves until r3 is 0 (both addresses are word-aligned)
alignDB:
  copyDBbyte source, dest, n
  SUB r3, #1
  SUBS r4, #1
  ; if r3 is not 0, keep iterating
  BNE alignDB
 
  ; if source and dest both are aligned, do a bulk copy
  CMP r3, #0
  BEQ copyDB168
  
  ; otherwise, do single word reads with bulk writes
wordreadDB40:
  CMP n, #40
  BLT wordreadDB20
  ; if not, then load the registers individually
  LDR r3, [source], #-4
  LDR r4, [source], #-4
  LDR r5, [source], #-4
  LDR r6, [source], #-4
  LDR r7, [source], #-4
  LDR r8, [source], #-4
  LDR r9, [source], #-4
  LDR r10, [source], #-4
  LDR r11, [source], #-4
  LDR r12, [source], #-4
  ; then store them in one go
  STMDB dest!, {r3 - r12}
  SUBS n, #40
  BEQ return
  B wordreadDB40
  
wordreadDB20:
  CMP n, #20
  BLT wordreadDB4
  ; load up 20 bytes into registers
  LDR r3, [source], #-4
  LDR r4, [source], #-4
  LDR r5, [source], #-4
  LDR r6, [source], #-4
  LDR r7, [source], #-4
  ; then store all 20 bytes in one go
  STMDB dest!, {r3 - r7}
  SUBS n, #20
  BEQ return
  B wordreadDB20
wordreadDB4:
  CMP n, #4
  ; if there are less than 4 bytes left, then move to load/storing 1 at a time
  BLT copyDB1
  ; load up 4 bytes into one register
  LDR r3, [source], #-4
  ; then store them
  STMDB dest!, {r3}
  SUBS n, #4
  BEQ return
  B wordreadDB4  
    
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
  SUBS n, #40
  
  ; if there are no more bytes to copy, then return
  BEQ return
  
  ; otherwise, try to copy 40 bytes again
  B copyDB40
  
copyDB4:
  ; if there are greater than or equal to 4 bytes to copy, then copy 4 in one go
  CMP n, #4
  ; otherwise copy 1 byte at a time
  BLT copyDB1
  ; copy over 1 value at at time, decrementing the address by 4 each time
  LDMDB source!, {r3}
  STMDB dest!, {r3}
  
  ; decrement the number of bytes to be copied by the number that were copied (4)
  SUBS n, #4
  
  ; if there are no more bytes to copy, then return
  BEQ return
  
  ; otherwise, keep copying 4 bytes at a time
  B copyDB4
  
copyDB1:
  ; copy a single byte at a time, branching to return if n becomes 0
  copyDBbyte source, dest, n

  ; if n did not become 0 from the single byte copy, then copy more bytes
  B copyDB1  
  
return:
  POP {pc, r4 - r12}
  .end