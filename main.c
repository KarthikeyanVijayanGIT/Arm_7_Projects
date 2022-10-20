#include <lpc214x.h>
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "queue.h"


#define SBIT_WordLenght    0x00u
#define SBIT_DLAB          0x07u
#define SBIT_FIFO          0x00u
#define SBIT_RxFIFO        0x01u
#define SBIT_TxFIFO        0x02u

#define SBIT_RDR           0x00u
#define SBIT_THRE          0x05u

#define TX0_PINSEL            0
#define RX0_PINSEL            2

#define pclk  48000000


void led1();
void led2();
void PLL_Init(void);
void uart_init(uint32_t baudrate);
void uart_transmit(uint8_t data_buff);

long delay1 = 0;
long delay2 = 0;
int toggle[2] = {0};

uint8_t txbuff[100] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
uint8_t index = 0;

TaskHandle_t task1;
TaskHandle_t task2;
QueueHandle_t Queue_handle;

/* start the main program */
int main() 
{
	PLL_Init();
	uart_init(9600);
	IO0DIR = (1<<15);   // Configure P0.10 as Output
	IO1DIR = (1<<16);   // Configure P0.10 as Output
	PINSEL0 |= (1<<0) | (1<<2);
	Queue_handle = xQueueCreate(50, 1);
	if(Queue_handle != NULL)
	{
		
	}
	xTaskCreate(led1, "lcdscroll", 1000, 0, 2, &task1);
	xTaskCreate(led2, "ledblinking", 1000, 0, 1, &task2);
	prvInitialiseNewTimer("led2", 1000, 1, 0, led2);
	vTaskStartScheduler();
	while(1)
	{}
}


/* Function to initialize the UART0 at specifief baud rate */
void uart_init(uint32_t baudrate)
{
    uint32_t var_RegValue_u32;

    PINSEL0 |= (1<<RX0_PINSEL) | (1<<TX0_PINSEL);   //Configure P0.0/P0.1 as RX0 and TX0 

    U0FCR = (1<<SBIT_FIFO) | (1<<SBIT_RxFIFO) | (1<<SBIT_TxFIFO); // Enable FIFO and reset Rx/Tx FIFO buffers    
    U0LCR = (0x03<<SBIT_WordLenght) | (1<<SBIT_DLAB);             // 8bit data, 1Stop bit, No parity

    var_RegValue_u32 = ( pclk / (16 * baudrate )); 
    U0DLL =  var_RegValue_u32 & 0xFF;
    U0DLM = (var_RegValue_u32 >> 0x08) & 0xFF;

		U0LCR &= ~(1<<7);
	
    //util_BitClear(U0LCR,(SBIT_DLAB));  // Clear DLAB after setting DLL,DLM
}


void PLL_Init(void)
{
	PLL0CFG = (3<<0) | (1<<5);
	PLL0CON |= (1<<0);
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	PLL0CON |= (1<<1);
	while(!(PLL0STAT & (1<<10)));
	VPBDIV = 0x01;
}

void led1()
{

	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
		
		if(toggle[0] == 1)
		{
			IO0CLR = (1<<15);    // CLEAR (0) P0.10 to turn LED ON
		}
		else
		{
			IO0SET = (1<<15);    // CLEAR (0) P0.10 to turn LED ON
		}
		
    delay1++;
    if(delay1 > 100)
		{
			delay1 = 0;
			if(toggle[0] == 1)
			{
				toggle[0] = 0;
			}
			else
			{
				toggle[0] = 1;
			}
		}else{}
			
		/* queue */
		//xQueueSendToBack(Queue_handle, &txbuff[index], 0);
		//++index;
		//if(index > 10) index = 0;
			
		/* vtask delay - this will push the task to blocking state */
		//vTaskDelay(10);
		
			/* vtask delay until - this will not push the task to wait but this will wait till the given time */
		//vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 10 ) );
		
		/* task priority - change the task priority run time */
		//vTaskPrioritySet(task1, 1);
		//vTaskPrioritySet(task2, 2);
	}
}

void led2()
{
	TickType_t xLastWakeTime1;
	uint8_t data = 0;
	BaseType_t ret = 0;
	
	xLastWakeTime1 = xTaskGetTickCount();
	
	
	while(1)
	{
		if(toggle[1] == 1)
		{
			IO1CLR = (1<<16);    // CLEAR (0) P0.10 to turn LED ON
		}
		else
		{
			IO1SET = (1<<16);    // CLEAR (0) P0.10 to turn LED ON
		}
    delay2++;
    if(delay2 > 10)
		{
			delay2 = 0;
			if(toggle[1] == 1)
			{
				toggle[1] = 0;
			}
			else
			{
				toggle[1] = 1;
			}
		}else{}
		
		/* taskqueue recieve - this was used to recieve from queue */
		//ret = xQueueReceive(Queue_handle, &data, 0);
		//while(ret != errQUEUE_EMPTY)
		//{
		//	uart_transmit(data);
		//	ret = xQueueReceive(Queue_handle, &data, 0);
		//};
			
			
		/* this will set the task to block till timer elapse */
		//vTaskDelay(100);
			
			
		/* taskdelay until - this will wait to for given time */
		//vTaskDelayUntil( &xLastWakeTime1, pdMS_TO_TICKS( 10 ) );
		
		/* task priority - used to set the task priority */	
		//vTaskPrioritySet(task1, 2);
		//vTaskPrioritySet(task2, 1);
	}
}

void uart_transmit(uint8_t data_buff)
{
	U0THR = data_buff;                                  // Load the data to be transmitted
	while((U0LSR & (1<<5)));
}

