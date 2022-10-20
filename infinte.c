/* ARM7 - NXP LPC2148(LED BLINKING) */

/* INCLUDES */
#include <lpc214x.h>

/* FUNCTION DECLARATION */
void delay();


int main()
{
	/* SET DIRECTION FOR THE PIN TO BE USED */
	IODIR1=(1<<16);

	/* INFINITE LOOP */
	while(1)
	{
		/* PIN HIGH */
		IO1SET=(1<<16);
		/* DUMMY SOFWARE DELAY */
		delay();
		/* PIN LOW */
		IO1CLR=(1<<16);
		/* DUMMY SOFWARE DELAY */
		delay();
	}
return 0;
}

/* DUMMY DELAY */
void delay()
{
	unsigned long i=0,j,k;
	while(i!=6000000)
	{i++;}
}