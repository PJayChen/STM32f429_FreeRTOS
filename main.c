#include "stm32f4xx.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "queue.h"

#include "hw_conf.h"
#include "myio.h"

/* semaphores, queues declarations */
xQueueHandle xQueueUARTRecvie;
xQueueHandle xQueueUSARTSend;
SemaphoreHandle_t xSemUSART1send;

/* Queue structure used for passing messages. */
typedef struct {
	char str[50];
} serial_str_msg;

typedef struct {
	char ch;
} serial_ch_msg;

extern char* pUSARTtxData;

/* Private functions ---------------------------------------------------------*/
char receive_byte()
{
	serial_ch_msg msg;

	/* Wait for a byte to be queued by the receive interrupts handler. */
	while (!xQueueReceive(xQueueUARTRecvie, &msg, portMAX_DELAY));
	return msg.ch;
}

void vATask(void *pvParameters)
{
	while(1){
		vTaskDelay(1000);
		uprintf("Task A run... \n");
		uprintf("Task A 123... \n");
		
	}
}

void vBTask(void *pvParameters)
{
	while(1){
		vTaskDelay(1000);
		uprintf("Task B run... \n");
		
	}
}

int main(void)
{
	/* initialize hardware... */
	prvSetupHardware();

	/*a queue for tansfer the senddate to USART task*/
	xQueueUARTRecvie = xQueueCreate(15, sizeof(serial_ch_msg));
	xQueueUSARTSend = xQueueCreate(15, sizeof(serial_ch_msg));
	xSemUSART1send = xSemaphoreCreateBinary();

	uprintf("Hardware initialize finish...\n");
	
	xTaskCreate( vATask, "send", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	//xTaskCreate( vBTask, "send", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	
	vTaskStartScheduler();
	while(1);
	return 0;
}
