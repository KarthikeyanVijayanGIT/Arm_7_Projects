/* ARM7 - NXP LPC2148(INPUT LATCH SWITCH) */

/* INCLUDES */
#include<lpc214x.h>

/* FUCNTION DECLARATION */
void delay();


int main()
{
	IODIR0&=~(1<<15);
	IODIR1|=(1<<16);
	while(1)
	{
		delay();
		while((IOPIN0&(1<<15)));
		IOCLR1|=(1<<16);
		delay();
		while((IOPIN0&(1<<15)));
		IOSET1|=(1<<16);
	}
return 0;
}
void delay()
{
	unsigned int i;
	for(i=700000;i>0;i--);
}