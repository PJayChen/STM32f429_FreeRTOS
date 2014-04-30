#include "FreeRTOS.h"
#include "task.h"

void vATask(void *pvParameters)
{
	while(1){
		GPIOA->ODR = 0x00000001;
		vTaskDelay(1000);
	}
}

void vBTask(void *pvParameters)
{
	while(1){
		GPIOA->ODR = 0x00000002;
	}
}

int main(void)
{
	
	prvSetupHardware();
	
	xTaskCreate(vATask, "A", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(vBTask, "B", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

	vTaskStartScheduler();

	while(1);
	return 0;
}
