/* OUTPUT_ARCH(mips) */
/* ENTRY(begin) */
SECTIONS
{
	. = 0x00000000;
	.text : 
	{
		*(.text) 
		*(.rodata)
	}

	. = ALIGN(1024);

	.data : {*(.data)}

	.bss : {*(.bss)}

}