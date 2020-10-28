.text
.align 4

	li t0, 1
	li t1, 2
	bne t0, t1, 20
	sub t2, t1, t0

myloop:
	add t2, t1, t0


.data
.align 4
stack:
	.space 1024
