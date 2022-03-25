/*
 * File:   main.c
 * Author: hossa
 *
 * Created on March 19, 2022, 1:38 PM
 */
#define F_CPU  16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "FreeRTOS/FreeRTOSConfig.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"

#include "mUART.h"
#include "FreeRTOS/queue.h"






QueueHandle_t Q_Handler;



void SenderTask(void * pv) {


    int pData  = (int ) pv;
    while (1) {

        xQueueSendToFront(Q_Handler, &pData, 10);
        
        vTaskDelay(5);
    }
}

void ReceiverTask(void * pv) {

    int pData;
    while (1) {
    
        xQueueReceive(Q_Handler, &pData , 10);
        
        UART_send_num(pData);
        UART_send('\r');

    }


}

int main(void) {
    /* Replace with your application code */



    Q_Handler = xQueueCreate(1, sizeof(int));
    init_UART(9600);
    xTaskCreate(SenderTask, "Task1", 100, (void *) 50, 1, NULL);
    xTaskCreate(SenderTask, "Task2", 100, (void *) 200, 1, NULL);
    xTaskCreate(ReceiverTask, "Task3", 100, NULL, 2, NULL);
   

    vTaskStartScheduler();
    // There is an error happened

    PORTA = 0xFF;
    while (1) {
    }
}
