#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle mutexBus;

void writeToBus(char *message){
    printf(message);
}

void task1(void * param)
{
    while (true)
    {
        printf("Reading temperature from %s\n", (char *) param); /* changing void type to char type */
        if(xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS)){
            writeToBus("Temperature is 22C\n");
            xSemaphoreGive(mutexBus); /* to release the semaphore */
        }
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task2(void * param)
{
    while (true)
    {
        printf("Reading humidity from %s\n", (char *) param);
        if(xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS)){
            writeToBus("Humidity is 35\n");
            xSemaphoreGive(mutexBus);
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    mutexBus = xSemaphoreCreateMutex();
    xTaskCreate(&task1, "Temperature read", 2048, "task 1", 2, NULL); /* ctrl + shift + A makes this nice comment */
    xTaskCreate(&task2, "Humidity read", 2048, "task 2", 2, NULL);
}