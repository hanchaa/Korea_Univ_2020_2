#include "SevenSeg.h"

void display (int);

void SevenSeg()
{
	unsigned int * led_addr  = (unsigned int *) LEDG;
	unsigned int i, data;

	data = 0x155;


	while (1){

		display(SEG_1);
		*led_addr  = data;
	    data = data ^ 0x3FF;

		//for (i=0; i<0xFFFFF; i++) ;
		for (i=0; i<0x2; i++) ;

		display(SEG_2);
		*led_addr  = data;
	    data = data ^ 0x3FF;

		//for (i=0; i<0xFFFFF; i++) ;
		for (i=0; i<0x2; i++) ;

	}

	return;

}


void display (int num)
{
	unsigned int * seg0_addr = (unsigned int *) SevenSeg0;

	*seg0_addr = num;

	return;
}
