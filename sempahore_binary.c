#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore;

void listenToHTTP(char *message){
    while (true)
    {
      printf("received http message\n");
      xSemaphoreGive(binSemaphore);
      printf("processed http message\n");
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void task1(void * param)
{
    while (true)
    {
        xSemaphoreTake(binSemaphore, portMAX_DELAY);
        printf("doing something with http\n");
    }
}

void app_main(void)
{
    mutexBus = xSemaphoreCreateMutex();
    xTaskCreate(&listenToHTTP, "get HTTP", 2048, NULL, 2, NULL); /* ctrl + shift + A makes this nice comment */
    xTaskCreate(&task1, "do something with HTTP", 2048, "task 2", 2, NULL);
}