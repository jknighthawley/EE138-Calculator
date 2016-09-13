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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS CODE DOES NOT COMPLETE LAB 1 PART 1, IT IS JUST AN EXAMPLE SO THAT YOU MAY UNDERSTAND THE CODE SYNTAX
// This project shows how to perform Port Control. 
// It demonstrates how to set a pin as an input as well as output pin. 
// We toggle the LED on the SAMD20 whenever the button SW0 on the SAMD20 is pressed.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Include header files for all drivers
#include <asf.h>
#include <stdio.h>

#define A 1<<0
#define B 1<<1
#define C 1<<2
#define D 1<<3
#define E 1<<4
#define F 1<<5
#define G 1<<6
#define DP 1<<7

//Include void functions
void wait(int t);
void Simple_Clk_Init(void);
void initializePorts();
void print();
void initializePorts();
void initializeSevenSegmentDisplay();
void turnOffDisplay();
void clearDigits();
void setNumber(int);
void turnOnDigit(int);
void resetDisplay();

//global variables
volatile int count = 0;

Port *ports;
PortGroup *porA;
PortGroup *porB;

int characterMap[4][4] = {{1,2,3,0xA},{4,5,6,0xB},{7,8,9,0xC},{16,0,17,0xD}};
int DisplayNum[4]={1,2,3,4};
int firstNum;
int secondNum;
int numberCounter=0;

void shift (int num){
	for(int i = 0; i<3;i++){
		DisplayNum[i] = DisplayNum[i+1];
	}
	DisplayNum[3] = num;
}
void clear (){
	for(int i = 0; i<4;i++){
		DisplayNum[i] = 0;
	}
}
int pow(int base, int exp){
	if(exp == 0){
		return 1;
		}
	int temp = 1;
	for(int i = 0; i<exp; i++){
		temp = temp * base;
	}
	return temp;
}

int arrayToNum(int* array){
	int temp = 0;

	for(int i = 0; i<4; i++){
	temp += array[3-i] * (pow(10,i));
	}

	return  temp;
}
void initializePorts()
{
	ports = PORT;
	porA = &(ports->Group[0]);
	porB = &(ports->Group[1]);
}

void print(int in)
{	
	setNumber(in % 10);
	turnOnDigit(3);
	wait(1);
	
	resetDisplay();
	
	setNumber(((in - (in % 10)) % 100)/10);
	turnOnDigit(2);
	wait(1);

	resetDisplay();
	
	setNumber(((in - (in % 100)) % 1000)/100);
	turnOnDigit(1);
	wait(1);
	
	resetDisplay();
	
	setNumber(((in - (in % 1000)) % 10000)/1000);
	turnOnDigit(0);
	wait(1);

	resetDisplay();
}

void initializeSevenSegmentDisplay()
{
	porA->DIRSET.reg = 1<<4 | 1<<5 | 1<<6 | 1<<7;
	porB->DIRSET.reg = 1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7;
}

void turnOffDisplay()
{
	porA->OUTSET.reg = 1<<4 | 1<<5 | 1<<6 | 1<<7;
}

void clearDigits()
{
	porB->OUTSET.reg = 1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7;
}

void resetDisplay()
{
	clearDigits();
	turnOffDisplay();
}

void setNumber(int num)
{
	switch(num){
		case 1: 
			porB->OUTCLR.reg =  B | C;
			break;
		case 2:
			porB->OUTCLR.reg =  A | B | G | E | D;
			break;
		case 3: 
			porB->OUTCLR.reg =  A | B | G | C | D;
			break;
		case 4:
			porB->OUTCLR.reg =  F | G | B | C;
			break;
		case 5: 
			porB->OUTCLR.reg =  A | F | G | C | D;
			break;
		case 6:
			porB->OUTCLR.reg =  A | F | G | E | C | D;
			break;
		case 7:
			porB->OUTCLR.reg =  A | B | C;
			break;
		case 8:
			porB->OUTCLR.reg =  A | F | G | B | E | C | D;
			break;
		case 9:
			porB->OUTCLR.reg =  A | F | B | G | C;
			break;
		case 0:
			porB->OUTCLR.reg =  A | F | B | E | C | D;
			break;
		default:
			break;
	}
	
}

void turnOnDigit(int digit)
{
	porA->OUTCLR.reg = 1<<(7-digit);
}

int main(void)
{
	//set micro-controller clock to 8Mhz
	Simple_Clk_Init();
	
	initializePorts();
	initializeSevenSegmentDisplay();
	
	resetDisplay();
	
	wait(1000);

	clearDigits();
	turnOffDisplay();
	
	porA->OUTSET.reg = 1<<04;
	
	for(int i = 16; i<20 ; i++)
	{
	porA -> PINCFG[i].reg = PORT_PINCFG_INEN|PORT_PINCFG_PULLEN;
	porA->DIRCLR.reg = 1<<i;
	porA->OUTCLR.reg = 1<<i;		
	}


	int count =0;
	while(1)
	{
		
		porA->OUTCLR.reg = 1<<04;
		unsigned int *INPUT_VAL = (unsigned int *) 0x41004420;
		porA->OUTCLR.reg = 1<<19 | 1<<18 | 1<<17 | 1<<16;
		
		for(int i = 4; i<8; i++)
		{
			porA->OUTCLR.reg = 1<<i;
			
			for(int j = 16; j<20; j++)
			{
				//idle
				if(*INPUT_VAL & 1<<j)
				{
				//debouncing 
					
					int pressed = characterMap[7-i][19-j];
					if (count < 4 && pressed < 10){
						shift(pressed);
						wait(1500);
						count++;
					}
					if(pressed > 9){
					int* displayNumPtr = &DisplayNum;
					if(numberCounter == 0){
						firstNum = arrayToNum(displayNumPtr);
						numberCounter++;
					}
					else
						secondNum = arrayToNum(displayNumPtr);

						
					switch (pressed){
						case 10:
							break;	
						case 11:
							break;
						case 12:
							break;
						case 13:
							break;
						case 16:
							break;
						case 17:
							break;
						default:
							break;
					}
					clear();
					count = 0;	

			

					}
				}
			}
				porA->OUTSET.reg = 1<<i;
 
				int temp2 = 7-i;
 				int temp = DisplayNum[i-4];
 				setNumber(temp);
 				turnOnDigit(i-4);
 				wait(10);
 				resetDisplay();
 				porA->OUTSET.reg = 1<<i;
 				porA->OUTSET.reg = 1<<temp2;
		}
	
		clearDigits();
		turnOffDisplay();
	}	
}

//time delay function
void wait(int t)
{
	count = 0;
    while (count < t*100)
	{
		count++;
	}
}

//Simple Clock Initialization - Do Not Modify -//
void Simple_Clk_Init(void)
{
	/* Various bits in the INTFLAG register can be set to one at startup.
	   This will ensure that these bits are cleared */
	
	SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET |
			SYSCTRL_INTFLAG_DFLLRDY;
			
	system_flash_set_waitstates(0);  		//Clock_flash wait state =0

	SYSCTRL_OSC8M_Type temp = SYSCTRL->OSC8M;      	/* for OSC8M initialization  */

	temp.bit.PRESC    = 0;    			// no divide, i.e., set clock=8Mhz  (see page 170)
	temp.bit.ONDEMAND = 1;    			// On-demand is true
	temp.bit.RUNSTDBY = 0;    			// Standby is false
	
	SYSCTRL->OSC8M = temp;

	SYSCTRL->OSC8M.reg |= 0x1u << 1;  		// SYSCTRL_OSC8M_ENABLE bit = bit-1 (page 170)
	
	PM->CPUSEL.reg = (uint32_t)0;    		// CPU and BUS clocks Divide by 1  (see page 110)
	PM->APBASEL.reg = (uint32_t)0;     		// APBA clock 0= Divide by 1  (see page 110)
	PM->APBBSEL.reg = (uint32_t)0;     		// APBB clock 0= Divide by 1  (see page 110)
	PM->APBCSEL.reg = (uint32_t)0;     		// APBB clock 0= Divide by 1  (see page 110)

	PM->APBAMASK.reg |= 01u<<3;   			// Enable Generic clock controller clock (page 127)

	/* Software reset Generic clock to ensure it is re-initialized correctly */

	GCLK->CTRL.reg = 0x1u << 0;   			// Reset gen. clock (see page 94)
	while (GCLK->CTRL.reg & 0x1u ) {  /* Wait for reset to complete */ }
	
	// Initialization and enable generic clock #0

	*((uint8_t*)&GCLK->GENDIV.reg) = 0;  		// Select GCLK0 (page 104, Table 14-10)

	GCLK->GENDIV.reg  = 0x0100;   		 	// Divide by 1 for GCLK #0 (page 104)

	GCLK->GENCTRL.reg = 0x030600;  		 	// GCLK#0 enable, Source=6(OSC8M), IDC=1 (page 101)
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* end of sample code for Lab 1 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
