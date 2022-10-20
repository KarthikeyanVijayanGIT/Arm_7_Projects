#include <lpc214x.h>
void initUART0();
void U0Write(char data);
unsigned char rx();
unsigned char i,j;
int main()
{
	IODIR1|=(1<<16);
	initUART0();
	while(1)
	{
	i=rx();
	for(j=5000;j>0;j--);
	U0Write(i);
		if(i=='a')
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
void initUART0()
{
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=93;
	U0DLM=00;
	U0FDR =0x20;
	U0LCR=0x03;
}
void U0Write(char data)
{
	U0THR=data;
	while(!(U0LSR&(1<<5)));
}
unsigned char rx()
{
	while(!(U0LSR&(1<<0)));
	return U0RBR;
}