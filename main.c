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

int main(void)
{

	/*a queue for tansfer the senddate to USART task*/
	xQueueUARTSend = xQueueCreate(15, sizeof(serial_str_msg));
	xQueueUARTRecvie = xQueueCreate(15, sizeof(serial_ch_msg));

	vSemaphoreCreateBinary(serial_tx_wait_sem);
	
	/* initialize hardware... */
	prvSetupHardware();
	return 0;
}
