#include "FreeRTOS.h"
#include "task.h"

void vATask(void *pvParameters)
{
	while(1){
		GPIOA->ODR = 0x00000000;
//		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void vBTask(void *pvParameters)
{
	while(1){
		GPIOA->ODR = 0x00000f00;
	}
}

int main(void)
{
	
	prvSetupHardware();
	GPIOA->ODR = 0x00000f00;
	xTaskCreate(vATask, "A", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	xTaskCreate(vBTask, "B", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

	vTaskStartScheduler();

	while(1);
	return 0;
}
