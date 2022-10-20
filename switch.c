/* ARM7 - NXP LPC2148(INPUT SWITCH) */

/* INCLUDES */
#include<lpc214x.h>


int main()
{
	/* CONFIG INPUT */
	IO0DIR&=~(1<<15);
	/* CONFIG OUTPUT */
	IO1DIR|=(1<<16);
	
	/* INFINITE LOOP */
	while(1)
	{
		/* SET LED HIGH IF SWITCH PRESSED */
		if(!(IOPIN0&(1<<15)))
		{
			IOCLR1|=(1<<16);
		}
		else
		{
			IOSET1|=(1<<16);
		}
	}
return 0;
}