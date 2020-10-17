#include "SevenSeg.h"

int SevenSeg()
{
	unsigned int * seg0_addr = (unsigned int *) SevenSeg0;
	unsigned int * seg1_addr = (unsigned int *) SevenSeg1;
	unsigned int * seg2_addr = (unsigned int *) SevenSeg2;
	unsigned int * seg3_addr = (unsigned int *) SevenSeg3;

	*seg0_addr = SEG_6;
	*seg1_addr = SEG_1;
	*seg2_addr = SEG_0;
	*seg3_addr = SEG_0;

	while(1);

	return 0;
}
