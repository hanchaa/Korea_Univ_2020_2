#include "SevenSeg.h"

int SevenSeg()
{
	unsigned int * seg0_addr = (unsigned int *) SevenSeg0;

	*seg0_addr = SEG_5;

	while(1);

	return 0;
}
