/* ARM7 - NXP LPC2148(HARDWARE TIME WITH PLL CONFIGURED FOR 60MHZ) */

/* INCLUDES */
#include <lpc214x.h>

/* FUNCTION DECLARATION */
void timer_delay();


int main(void)
{
	PLL0CON = 0x01;//Enable PLL
	PLL0CFG = 0x24;//Multiplier and divider setup
	PLL0FEED = 0xAA;//Feed sequence
	PLL0FEED = 0x55;
 
	while(!(PLL0STAT & 0x00000400)); //is locked?
 
	PLL0CON = 0x03;//Connect PLL after PLL is locked
	PLL0FEED = 0xAA;//Feed sequence
	PLL0FEED = 0x55;
	VPBDIV = 0x01;// PCLK is same as CCLK i.e.60 MHz
	IODIR1=(1<<16);

	while(1)
	{
		/* BLINK ONCE THE TIME EXPIRED */
		IOCLR1=(1<<16);
		timer_delay();
		IOSET1=(1<<16);
		timer_delay();
	}
return 0;
}


/* HARDWARE TIMER TEST FUNCTION */
void timer_delay()
{
	T0TC=1000000;
	T0PR= 60;
	T0CTCR=0x00000000;
	T0MCR|=(1<<1);
	T0TCR|=(1<<0);
	while(!(T0IR&(1<<0)));
	T0TCR&=~(1<<0);
}
