/* ARM7 - NXP LPC2148(PLL - 60MHZ) */
#include <lpc214x.h>

/* FUNCTION DECLARATION */
void PLL_Init(void);
void delay();

/* FUNCTION DEFINITION */
int main()
{
	/* INIT PLL */
	PLL_Init();
	
	/* ENABLE OUTPUT PIN TO CHECK THE REFLECTED CLOCK */
	IODIR1=(1<<16);
	
	/* INFINITE LOOP */
	while(1)
	{
		/* TOGGLE PIN */
		IOSET1=(1<<16);
		delay();
		IOCLR1=(1<<16);
		delay();
	}
return 0;
}

/* PLL INITILAZATION */
void PLL_Init(void)
{
	PLL0CON = 0x01;					//Enable PLL
	PLL0CFG = 0x24;					//Multiplier and divider setup
	PLL0FEED = 0xAA;				//Feed sequence
	PLL0FEED = 0x55;
	
	while(!(PLL0STAT & 0x00000400)); //is locked?
		
	PLL0CON = 0x03;					//Connect PLL after PLL is locked
	PLL0FEED = 0xAA;				//Feed sequence
	PLL0FEED = 0x55;
	VPBDIV = 0x01;					// PCLK is same as CCLK i.e.60 MHz
}

/* NEED TO CHECK THE DELAY RATE */
void delay()
{
	unsigned long i;
	//for(i=62500000;i>0;i--);
	for(i=0;i<12000048;i++);
}