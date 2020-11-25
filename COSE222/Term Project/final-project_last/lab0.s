.text
.align 4

	la sp, stack
	j	SevenSeg


.data
.align 4
stack:
	.space 1024
