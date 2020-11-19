#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#define  GPIO_BASE  	0xFFFF2000
#define  Button_Status	GPIO_BASE + 0
#define  SW_Status  	GPIO_BASE + 1
#define  LEDG       	GPIO_BASE + 2
#define  SevenSeg0  	GPIO_BASE + 3
#define  SevenSeg1  	GPIO_BASE + 4
#define  SevenSeg2  	GPIO_BASE + 5
#define  SevenSeg3  	GPIO_BASE + 6
#define  SEG_0      0x40    /* Display "0" on 7 Segment */
#define  SEG_1      0x79    /* Display "1" on 7 Segment */
#define  SEG_2      0x24    /* Display "2" on 7 Segment */
#define  SEG_3      0x30    /* Display "3" on 7 Segment */
#define  SEG_4      0x19    /* Display "4" on 7 Segment */
#define  SEG_5      0x12    /* Display "5" on 7 Segment */
#define  SEG_6      0x02    /* Display "6" on 7 Segment */
#define  SEG_7      0x78    /* Display "7" on 7 Segment */
#define  SEG_8      0x00    /* Display "8" on 7 Segment */
#define  SEG_9      0x10    /* Display "9" on 7 Segment */
#define  SEG_A      0x08    /* Display "A" on 7 Segment */
#define  SEG_B      0x03    /* Display "B" on 7 Segment */
#define  SEG_C      0x46    /* Display "C" on 7 Segment */
#define  SEG_D      0x21    /* Display "D" on 7 Segment */
#define  SEG_E      0x06    /* Display "E" on 7 Segment */
#define  SEG_F      0x0E    /* Display "F" on 7 Segment */
#define  SEG_       0x3F    /* Display "-" on 7 Segment */

#endif /* SEVENSEG_H_ */
