.text
.align 4
main:

	addi x3, x0, 0x400
	slli x3, x3, 1
	add x3, x3, x3
	add x3, x3, x3
	lui x4, 0xFFFF0
	or  x4, x3, x4     /* x4 contains 0xFFFF_2000, which is GPIO base address */
	bne x4, x4, error
	
	la  sp, my_stack
	sw  x4, 0(sp)     /* store 0xFFFF_2000 to stack */
	
	/* display 8 on HEX0 */
	la  x9, SEG8
	lw  x10, (x9)
	lw  x3, (sp)
	sw  x10, 0xC(x3)
	
	/* display 7 on HEX1 */
	lw  x10, -4(x9)
	lw  x3, (sp)
	add x3, x3, 0x10   /* x3 contains 0xFFFF_2010 */
	sw  x10, (x3)
	
	beq x3, x0, error  /* x3:0xFFFF_2010, should be not-taken */
	
	/* display 6 on HEX2 */
	lw  x3, (sp)
	add x3, x3, 0x14   /* x3 contains 0xFFFF_2014 */
	lw  x10, -8(x9)
	sw  x10, (x3)
	
	/* display 5 on HEX3 */
	lw   x10, -12(x9)
	addi x3, x3, 4     /* x3 contains 0xFFFF_2018 */
	sw   x10, (x3)
	
	j   HEX3
	add  x9, x9, 8     /* should not be executed */
	
HEX0:
	/* display 4 on HEX0 */
	lw  x10, -16(x9)
	lw  x3, (sp)
	add x3, x3, 0xC   	/* x3 contains 0xFFFF_200C */
	sw  x10, (x3)
	
	/* display 3 on HEX1 */
	lw   x10, -20(x9)
	addi x3, x3, 4     /* x3 contains 0xFFFF_2010 */
	sw   x10, (x3)
	
	/* display 2 on HEX2 */
	lw   x10, -24(x9)
	addi x4, x0, 4
	add  x3, x3, x4    /* x3 contains 0xFFFF_2014 */
	sw   x10, (x3)
	
	ret                /* return to forever */
	
HEX3:
	/* display 1 on HEX3 */
	lw   x10, -28(x9)
	lw   x3, (sp)
	addi x3, x3, 0x8
	addi x3, x3, 0x10   /* x3 contains 0xFFFF_2018 */
	sw   x10, (x3)
	
	call HEX0
	
forever:
	j forever

error:
	j error

.data
.align 4
SEG0:  .word  0x40
SEG1:  .word  0x79
SEG2:  .word  0x24
SEG3:  .word  0x30
SEG4:  .word  0x19
SEG5:  .word  0x12
SEG6:  .word  0x02
SEG7:  .word  0x78
SEG8:  .word  0x00

my_stack:
       .space 1024
