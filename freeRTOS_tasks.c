#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void * param)
{
    while (true)
    {
        printf("Reading temperature from %s\n", (char *) param); /* changing void type to char type */
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task2(void * param)
{
    while (true)
    {
        printf("Reading humidity from %s\n", (char *) param);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(&task1, "Temperature read", 2048, "task 1", 2, NULL); /* ctrl + shift + A makes this nice comment */
    xTaskCreate(&task2, "Humidity read", 2048, "task 2", 2, NULL);
}