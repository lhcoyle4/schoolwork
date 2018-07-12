
  
  ; dest > source, so the memory addresses start at the end of the blocks to move 
  ; and the addresses are decremented each iteration
copyDB:
  ; add the offset to source and dest, and then branch to the loop which decrements from the address
  SUB n, #1
  ADD source, n
  ADD dest, n
  ADD n, #1

  ; determine if source and destination are on 4-byte boundaries
  AND r3, source, #3
  AND r4, dest, #3
  
  ; if both addresses are word aligned, then do bulk reads and writes
  CMP r3, r4
  IT EQ
  CMPEQ r3, #0
  BEQ copyDB168
  
  ; if just the dest address is already aligned, then do single reads and bulk writes
  CMP r4, #0
  BEQ wordreadDB40
 
  ; otherwise, do single byte moves until r3 is 0 (both addresses are word-aligned)
alignDB:
  copyDBbyte source, dest, n
  SUB r3, #1
  SUBS r4, #1
  ; if r3 is not 0, keep iterating
  BNE alignDB
 
  ; if source and dest are now both aligned, do a bulk copy
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