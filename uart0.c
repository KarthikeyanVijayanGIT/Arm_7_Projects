#include <lpc214x.h>
void initUART0(void);
void U0Write(char data);
void Send_String(char i);
unsigned char rx();
char String[]="HI DUDE!!! KARTHIKEYAN \n\r\n";
unsigned int delay;
unsigned char i;
int main(void)
{
 initUART0();
 while(1) 
 { 
	
 Send_String(String);//Pass the string to the USART_putstring function and sends it over the serial 
//for(delay=0; delay<500000; delay++); // dela 
 }
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
void Send_String(char i){
 
 while(*StringPtr != 0x00)
	 {
 U0Write(*StringPtr);
 StringPtr++;}
}
unsigned char rx()
{
	while(!(U0LSR&(1<<0)));
	return U0RBR;
}