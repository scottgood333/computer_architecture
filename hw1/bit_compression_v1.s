.data
    num0: .word 0x0fffffff 0xffffffff # big endian num = 1152921504606846975
    num1: .word 0x00000000 0x00003567 # big endian num = 13671
    num2: .word 0x00000000 0x0000000a # big endian num = 10
    str0:  .string "\noriginal bit count: 64"
    str1:  .string "\nleading zeros of test data: "
    str2:  .string "\nbit count after compressed: "
    str3:  .string "\nbit reduced after compressed: "
.text

main:
load_nums:
    # s2 stores num0
    la  t0, num0
    lwu  s2, 0(t0)
    slli s2, s2, 32
    lwu t0, 4(t0)
    or  s2, s2, t0
    
    # s3 stores num1
    la  t0, num1
    lwu  s3, 0(t0)
    slli s3, s3, 32
    lwu t0, 4(t0)
    or  s3, s3, t0
    
    # s4 stores num2
    la  t0, num2
    lwu  s4, 0(t0)
    slli s4, s4, 32
    lwu t0, 4(t0)
    or  s4, s4, t0
CLZ:
    # t0 stores x
    mv t0, s3
    
    # t1 stores temp　 
    srli t1, t0, 1
    
    # t2 stores shamt
    addi t2, t2, 2
    
    # t3 stores end loop index(32)
    addi t3, t3, 64
  
    # x |= (x>>1)
    or t0, t1, t0 
   
    loop:    
        #x |= (x>>2, 4, 8, 16, 32)
        srl t1, t1, t2
        or t0, t1, t0  
        slli t2, t2, 1
        bne t2, t3, loop
    
    # t0 stores x
    # t1, t3 stores temp
    
    # x -= ((x >> 1) & 0x5555555555555555)
    srli t1, t0, 1  #t1 = x >> 1
    li t2, 0x55555555
    mv t3, t2
    slli t2, t2,32
    or t2, t3, t2 # t2 = 0x5555555555555555
    and t1, t1, t2
    sub t0, t0, t1
    
    # x = ((x >> 2) & 0x3333333333333333) + (x & 0x3333333333333333)
    srli t1, t0, 2 # t1 = x >> 2
    li t2, 0x33333333
    mv t3, t2
    slli t2, t2, 32
    or t2, t3, t2 # t2 = 0x3333333333333333
    and t1, t1, t2 # t1 = (x >> 2) & 0x3333333333333333
    and t3, t0, t2 # t3 = x & 0x3333333333333333
    add t0, t1, t3
    
    # x = ((x >> 4) + x) & 0x0f0f0f0f0f0f0f0f
    srli t1, t0, 4 
    add t1, t1, t0 # t1 = (x >> 4) + x 
    li t2, 0x0f0f0f0f
    mv t3, t2
    slli t2, t2, 32
    or t2, t3, t2 # t2 = 0x0f0f0f0f0f0f0f0f
    and t0, t1, t2
    
    # x += (x >> 8)
    srli t1, t0, 8 # t1 = (x >> 8)
    add t0, t1, t0
    
    # x += (x >> 16)
    srli t1, t0, 16 # t1 = (x >> 16)
    add t0, t1, t0
    
    # x += (x >> 32)
    srli t1, t0, 32 # t1 = (x >> 32)
    add t0, t1, t0
    
    # x = 64 - (x & 0x7f) 
    andi t0, t0, 0x7f
    li t2, 64
    sub t0, t2, t0
    
compress:
    li t3, 32
    li t2, 48
    li t1, 64
    bgt t3, t0, print
    bge t0, t2, to_uint16

to_uint32:
    li t1, 32
    j print
to_uint16:
    li t1, 16
    j print



print:
    la a0, str0
    li a7, 4
    ecall
    
    la a0, str1
    li a7, 4
    ecall
    
    mv a0, t0
    li a7, 1
    ecall
    
    la a0, str2
    li a7, 4
    ecall
    
    mv a0, t1
    li a7, 1
    ecall