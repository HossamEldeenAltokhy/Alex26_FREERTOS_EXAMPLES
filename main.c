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

char str1[] = "Task1 is running\r";
char str2[] = "Task2 is running\r";
char str3[] = "Task3 is running\r";
char str4[] = "Task4 is running\r";


TaskHandle_t Task1_Handler;
TaskHandle_t Task2_Handler;
TaskHandle_t Task3_Handler;
TaskHandle_t Task4_Handler;





void Task1(void * pv) {


    while (1) {

        UART_send_str((char *) pv);
        vTaskDelay(5);
    }
}

void Task2(void * pv) {

    int i = 0;
    while (1) {
        i++;
        UART_send_str((char *) pv);
        vTaskDelay(2);
        if (i == 5) {
            vTaskDelete(Task1_Handler);
        }
        if (i == 10) {
            xTaskCreate(Task1, "Task1", 100, (void *) str1, 1, &Task1_Handler);
        }


    }


}

int main(void) {
    /* Replace with your application code */
    DDRA = 0xFF;
    DDRC = 0xFF;


    init_UART(9600);
    xTaskCreate(Task1, "Task1", 100, (void *) str1, 1, &Task1_Handler);
    xTaskCreate(Task1, "Task2", 100, (void *) str2, 1, &Task2_Handler);
    xTaskCreate(Task1, "Task3", 100, (void *) str3, 1, &Task3_Handler);
    xTaskCreate(Task2, "Task4", 100, (void *) str4, 1, &Task4_Handler);

    _delay_ms(200);
    vTaskStartScheduler();
    // There is an error happened

    PORTA = 0xFF;
    while (1) {
    }
}
