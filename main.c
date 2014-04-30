#include "stm32f4xx.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "queue.h"

/* semaphores, queues declarations */
xQueueHandle xQueueUARTSend;
xQueueHandle xQueueUARTRecvie;

xSemaphoreHandle serial_tx_wait_sem;


/* Queue structure used for passing messages. */
typedef struct {
	char str[50];
} serial_str_msg;

typedef struct {
	char ch;
} serial_ch_msg;

/* Private functions ---------------------------------------------------------*/
char receive_byte()
{
	serial_ch_msg msg;

	/* Wait for a byte to be queued by the receive interrupts handler. */
	while (!xQueueReceive(xQueueUARTRecvie, &msg, portMAX_DELAY));
	return msg.ch;
}

void puts_str(char* s)
{
	while(*s){
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, *s);
		s++;
	}
}

void vUsartSendTask(void *pvParameters)
{
	char get;
	while(1){

//		get = receive_byte();
//		send_str("task!!\n\r");
//		send_byte(get);
		puts_str("task test\n\r");
		vTaskDelay(1000);
		
	}
}


int main(void)
{

	/*a queue for tansfer the senddate to USART task*/
	xQueueUARTSend = xQueueCreate(15, sizeof(serial_str_msg));
	xQueueUARTRecvie = xQueueCreate(15, sizeof(serial_ch_msg));

	vSemaphoreCreateBinary(serial_tx_wait_sem);
	
	/* initialize hardware... */
	prvSetupHardware();
	puts_str("Hardware initial finish...\n\r");
	xTaskCreate( vUsartSendTask, "send", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	puts_str("Start scheduling...\n\r");
	vTaskStartScheduler();
	while(1);
	return 0;
}
