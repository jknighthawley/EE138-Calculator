/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <port.h>

//Include void functions
void wait(int t);
void Simple_Clk_Init(void);

//global variables
volatile int count = 0;


//Pass in a number to display on 7-Segment
void display(int number){
	//turn on all 7-segments-OUTCLR setting a 1 clears the out to 0
	unsigned int *OUT_CLR_B = unsigned int* (0x0x41004494)
	*OUT_CLR_B = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	//OUTSET-setting a 1 sets out to 1(maybe ust do a SET
	unsigned int *OUT_B = unsigned int* (0x0x41004498)
	switch(number)
	{
		case 0:
		//0x11000000;
		*OUT_B = (0<<0)|(0<<1)|(0<<2)|(0<<3)|(0<<4)|(0<<5)|(1<<6)|(1<<7);
		break;
		case 1:
		//11111001
		*OUT_B = (1<<0)|(0<<1)|(0<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
		break;
		case 2:
		//0x10100100
		*OUT_B = (0<<0)|(0<<1)|(1<<2)|(0<<3)|(0<<4)|(1<<5)|(0<<6)|(1<<7);
		break;
		case 3:
		//0x10110000
		*OUT_B = (0<<0)|(0<<1)|(0<<2)|(0<<3)|(1<<4)|(1<<5)|(0<<6)|(1<<7);
		break;
		case 4:
		//0x10011001
		*OUT_B = (1<<0)|(0<<1)|(0<<2)|(1<<3)|(1<<4)|(0<<5)|(0<<6)|(1<<7);
		break;
		case 5:
		//0x10010010
		*OUT_B = (0<<0)|(1<<1)|(0<<2)|(0<<3)|(1<<4)|(0<<5)|(0<<6)|(1<<7);
		break;
		case 6:
		//0x10000010
		*OUT_B = (0<<0)|(1<<1)|(0<<2)|(0<<3)|(0<<4)|(0<<5)|(0<<6)|(1<<7);
		break;
		case 7:
		//0x11111000
		*OUT_B = (0<<0)|(0<<1)|(0<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
		break;
		case 8:
		//0x10000000
		*OUT_B = (0<<0)|(0<<1)|(0<<2)|(0<<3)|(0<<4)|(0<<5)|(0<<6)|(1<<7);
		break;
		case 9:
		//0x10011000
		*OUT_B = (0<<0)|(0<<1)|(0<<2)|(1<<3)|(1<<4)|(0<<5)|(0<<6)|(1<<7);
		break;
		default:
		//0x00000000;
		*OUT_B = (0<<0)|(0<<1)|(0<<2)|(0<<3)|(0<<4)|(0<<5)|(0<<6)|(0<<7);
	}

}

int main (void)
{
	//set micro-controller clock to 8Mhz
	Simple_Clk_Init();
	//Config PA04-PA07 to output Config PA16-PA19 to input
	unsigned int *DIR_SET_A = (unsigned int*)(0x41004408);
	*DIR_SET_A = (1<<4)|(1<<5)|(1<<6)|(1<<7);
	unsigned int *DIR_CLR_A = (unsigned int*)(0x41004404);
	*DIR_CLR_A = (0<<16)|(0<<17)|(0<<18)|(0<<19);
	//Config PB00 -PB07 to output
	unsigned int *DIR_SET_B = (unsigned int*)(0x41004488);
	*DIR_SET_B = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);

	//init inen = 0 pullen = 1 PA04-PA07
	unsigned int *4_CFG = (unsigned int*)(0x41004444);
	*4_CFG = (0<<1)|(1<<2);
	unsigned int *5_CFG = (unsigned int*)(0x41004445);
	*5_CFG = (0<<1)|(1<<2);
	unsigned int *6_CFG = (unsigned int*)(0x41004446);
	*6_CFG = (0<<1)|(1<<2);
	unsigned int *7_CFG = (unsigned int*)(0x41004447);
	*7_CFG = (0<<1)|(1<<2);
	//init inen = 1 pullen = 0 PA04-PA07
	unsigned int *16_CFG = (unsigned int*)(0x41004450);
	*16_CFG = (1<<1)|(0<<2);
	unsigned int *17_CFG = (unsigned int*)(0x41004451);
	*17_CFG = (1<<1)|(0<<2);
	unsigned int *18_CFG = (unsigned int*)(0x41004452);
	*18_CFG = (1<<1)|(0<<2);
	unsigned int *19_CFG = (unsigned int*)(0x41004453);
	*19_CFG = (1<<1)|(0<<2);

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	while (1) {
		//Scan thru the 4 7-Segments
		//While on one 7-segment, scan key pushes by pulling up input pins in different combos-decode button push if any
		//If a certain button is pushed, it will cause the input value to go high, depending on which LED(ROW)is selected will give the button pushed
	}
}
