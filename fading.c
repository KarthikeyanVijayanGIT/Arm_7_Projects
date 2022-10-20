/* ARM7 - NXP LPC2148(FADING LED) */

/* INCLUDES */
#include <lpc214x.h>

/* FUNCTION DECLARATION */
void delay(uint32_t c);


int main()
{
	/* LOCAL VARIABLE */
	uint32_t j,k=0;

	/* SET DIRECTION FOR THE PIN TO BE USED */
	IO1DIR|=(1<<16);
	
	/* INFINITE LOOP */
	while(1)
	{
		/* LOW TO HIGH */
		k=1;
		for(j=3500;j>0;j--)
		{
			k++;
			IO1SET|=(1<<16);
			delay(j);
			IO1CLR|=(1<<16);
			delay(k);
		}
		
		/* HIGH TO LOW */
		k=1;
		for(j=3500;j>0;j--)
		{
			k++;
			IO1SET|=(1<<16);
			delay(k);
			IO1CLR|=(1<<16);
			delay(j);
		}
	}
return 0;
}

/* DUMMY SOFTWARE LOOP */
void delay(uint32_t c)
{
	uint32_t i,t=0;

	for(i=c;i>0;i--)
	{
		t++;
	}
}