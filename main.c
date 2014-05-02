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
	/* initialize hardware... */
	prvSetupHardware();

	/*a queue for tansfer the senddate to USART task*/
	xQueueUARTRecvie = xQueueCreate(15, sizeof(serial_ch_msg));

	uprintf("Hardware initialize finish...\n");
	
	while(1);
	return 0;
}
