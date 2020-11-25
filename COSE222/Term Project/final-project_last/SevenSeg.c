
#include "SevenSeg.h"

void display (int);
int  my_addition (int *, int *);

int SevenSeg()
{
	unsigned int i;
	int in1, in2, out;

	in1 = 5;

	while (1){

		for (in2 = -5; in2 < 5 ; in2++) {

			out = my_addition (&in1, &in2);

			display(out);                 // Display a number on HEX0

			for (i=0; i<0x50000; i++) ;  // delay for roughly 0.5 second

		}
	}

	return 0;
}


int my_addition (int * a, int * b)
{
	int sum;

	sum = *a + *b;

	return sum;
}


void display (int num)
{
	unsigned int * seg0_addr = (unsigned int *) SevenSeg0;

	if      (num == 0) *seg0_addr = SEG_0;
	else if (num == 1) *seg0_addr = SEG_1;
	else if (num == 2) *seg0_addr = SEG_2;
	else if (num == 3) *seg0_addr = SEG_3;
	else if (num == 4) *seg0_addr = SEG_4;
	else if (num == 5) *seg0_addr = SEG_5;
	else if (num == 6) *seg0_addr = SEG_6;
	else if (num == 7) *seg0_addr = SEG_7;
	else if (num == 8) *seg0_addr = SEG_8;
	else if (num == 9) *seg0_addr = SEG_9;
	else               *seg0_addr = SEG_;
/*
	switch (num)
	{
	case 0: *seg0_addr = SEG_0;
			break;
	case 1: *seg0_addr = SEG_1;
			break;
	case 2: *seg0_addr = SEG_2;
			break;
	case 3: *seg0_addr = SEG_3;
			break;
	case 4: *seg0_addr = SEG_4;
			break;
	case 5: *seg0_addr = SEG_5;
			break;
	case 6: *seg0_addr = SEG_6;
			break;
	case 7: *seg0_addr = SEG_7;
			break;
	case 8: *seg0_addr = SEG_8;
			break;
	case 9: *seg0_addr = SEG_9;
			break;
	default: *seg0_addr = SEG_;
			break;
	}
*/
}
