#include "stm32f4xx.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "queue.h"

extern xQueueHandle xQueueUARTRecvie;
extern SemaphoreHandle_t xSemUSART1send;

/* Queue structure used for passing characters. */
typedef struct {
        char ch;
} serial_ch_msg;

/* IRQ handler to handle USART2 interruptss (both transmit and receive
* interrupts). */
void USART1_IRQHandler()
{
    static signed portBASE_TYPE xHigherPriorityTaskWoken;
    serial_ch_msg rx_msg;

    /* If this interrupt is for a transmit... */
    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
            
            xSemaphoreGiveFromISR(xSemUSART1send, NULL);
            /* Diables the transmit interrupt. */
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
            
    /* If this interrupt is for a receive... */
    }else if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
            /* Receive the byte from the buffer. */
            rx_msg.ch = USART_ReceiveData(USART1);

            /* Queue the received byte. */
            if(!xQueueSendToBackFromISR(xQueueUARTRecvie, &rx_msg, &xHigherPriorityTaskWoken)) {
                    /* If there was an error queueing the received byte,
                     * freeze. */
                    while(1);
            }
    
    }else {
            /* Only transmit and receive interrupts should be enabled.
             * If this is another type of interrupt, freeze.
             */
            while(1);
    }

    if (xHigherPriorityTaskWoken) {
            taskYIELD();
    }

}