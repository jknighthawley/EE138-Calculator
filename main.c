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

//Decode key push
int key_push(int row, int column){
//Column 1 = 5 from schematic
	int digit = 0;
	switch(row){
		case 1:
			switch(column){
				case 1:
					digit = 1;
				break;
				case 2:
					digit = 2;
				break;
				case 3:
					digit = 3;
				break;
				case 4:
					digit = 10; //A
				break;
			}
		case 2:
			switch(column){
				case 1:
				break;
				case 2:
				break;
				case 3:
				break;
				case 4:
				break;
			}
		case 3:
			switch(column){
				case 1:
				break;
				case 2:
				break;
				case 3:
				break;
				case 4:
				break;
			}
		case 4:
			switch(column){
				case 1:
				break;
				case 2:
				break;
				case 3:
				break;
				case 4:
				break;
			}


	}


}

//Pass in a number to display on 7-Segment
void display(int number){
	//turn on all 7-segments-OUTCLR setting a 1 clears the out to 0
	unsigned int *OUT_CLR_B = (unsigned int*) (0x41004494);
	*OUT_CLR_B = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	//OUTSET/9offset 0x18)-setting a 1 sets out to 1(maybe ust do a OUT(offset 0x10)
	unsigned int *OUT_B = (unsigned int*) (0x41004498);
	switch(number){
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
	//Simple_Clk_Init();
	//Config PA04-PA07 to output Config PA16-PA19 to input
	unsigned int *DIR_SET_A = (unsigned int*)(0x41004408);
	*DIR_SET_A = (1<<4)|(1<<5)|(1<<6)|(1<<7);
	unsigned int *DIR_CLR_A = (unsigned int*)(0x41004404);
	*DIR_CLR_A = (0<<16)|(0<<17)|(0<<18)|(0<<19);
	//Config PB00 -PB07 to output and add PB08 as output (dots)
	unsigned int *DIR_SET_B = (unsigned int*)(0x41004488);
	*DIR_SET_B = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8);

	//init inen = 0 pullen = 1 PA04-PA07
// 	unsigned int *4_CFG = (unsigned int*)(0x41004444);
// 	*4_CFG = (0<<1)|(1<<2);
// 	unsigned int *5_CFG = (unsigned int*)(0x41004445);
// 	*5_CFG = (0<<1)|(1<<2);
// 	unsigned int *6_CFG = (unsigned int*)(0x41004446);
// 	*6_CFG = (0<<1)|(1<<2);
// 	unsigned int *7_CFG = (unsigned int*)(0x41004447);
// 	*7_CFG = (0<<1)|(1<<2);
	//init inen = 0 pullen = 0 PA04-PA07
	unsigned int *CFG_4 = (unsigned int*)(0x41004444);
	*CFG_4 = (0<<1)|(0<<2);
	unsigned int *CFG_5 = (unsigned int*)(0x41004445);
	*CFG_5 = (0<<1)|(0<<2);
	unsigned int *CFG_6 = (unsigned int*)(0x41004446);
	*CFG_6 = (0<<1)|(0<<2);
	unsigned int *CFG_7 = (unsigned int*)(0x41004447);
	*CFG_7 = (0<<1)|(0<<2);
	unsigned int *CFG_8 = (unsigned int*)(0x41004488);
	*CFG_8 = (0<<1)|(0<<2);
	//init inen = 1 pullen = 0 PA04-PA07
	unsigned int *CFG_16 = (unsigned int*)(0x41004456);
	*CFG_16 = (1<<1)|(0<<2);
	unsigned int *CFG_17 = (unsigned int*)(0x41004457);
	*CFG_17 = (1<<1)|(0<<2);
	unsigned int *CFG_18 = (unsigned int*)(0x41004458);
	*CFG_18 = (1<<1)|(0<<2);
	unsigned int *CFG_19 = (unsigned int*)(0x41004459);
	*CFG_19 = (1<<1)|(0<<2);

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	while (1) {
		//while button push is not +/*-= read button push and store in array
		//Scan thru the 4 7-Segments
		unsigned int *OUT_SET = (unsigned int*)(0x41004458);
		//while(number ==20)
		//only incrmenting thru 7-seg not dots
		for(int i = 4; i < 8; i++){
			*OUT_SET = 1 << i;//output set high
			//do stuff
			//scan button push inputs
			//for(int j = 0, j <20,j++){
				unsigned int *INPUT_VAL = 0x41004420;//PIN input register offset 0x20
				//unsigned int *temp = *INPUT_VAL & 0x10; //ignore all but 16th pin
				int number = 20;//number = 20 indicates no button push;
				if (*INPUT_VAL & 0x10){//look at PA16
					number = key_push(i,4);
				}
				if (*INPUT_VAL & 0x11){//look at PA17
					number = key_push(i,3);
				}
				if (*INPUT_VAL & 0x12){//look at PA18
					number = key_push(i,2);
				}
				if (*INPUT_VAL & 0x13){//look at PA19
					number = key_push(i,1);
				}
			//display digit-debug force number 5
			display(5);
			*OUT_SET = 0 << i;//output back t0 low
		}
		//While on one 7-segment, scan key pushes by pulling up input pins in different combos-decode button push if any
		//If a certain button is pushed, it will cause the input value to go high, depending on which LED(ROW)is selected will give the button pushed
	}
}
