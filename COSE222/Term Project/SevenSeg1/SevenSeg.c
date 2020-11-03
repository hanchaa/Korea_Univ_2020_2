#include "SevenSeg.h"

void SevenSeg()
{
	unsigned int * seg0_addr = (unsigned int *) SevenSeg0;
	unsigned int * led_addr  = (unsigned int *) LEDG;
	unsigned int i, data;

	data = 0x155;

	while (1){

		*seg0_addr = SEG_5;
		*led_addr  = data;
		data = data ^ 0x3FF;

		for (i=0; i<0xFFFFF; i++) ;
		//for (i=0; i<0x2; i++) ;

		*seg0_addr = SEG_A;
		*led_addr  = data;
		data = data ^ 0x3FF;

		for (i=0; i<0xFFFFF; i++) ;
		//for (i=0; i<0x2; i++) ;

	}

	return;

}
