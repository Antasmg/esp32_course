#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL;

void sender(void * param)
{
    while (true)
    {
        xTaskNotify(receiverHandler, (1<<0), eSetValueWithOverwrite);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<1), eSetValueWithOverwrite); /* these two will not be added */
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<2), eSetBits); /* this one will be added to 2 (2+4=6) */
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        xTaskNotify(receiverHandler, (1<<3), eSetValueWithOverwrite); /* this one will overwrite 6 with 8 */
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void receiver(void * param)
{
    uint state;
    while (true)
    {
        xTaskNotifyWait(0,0,&state,portMAX_DELAY);
        printf("Received notification %d\n", state);
    }
}

void app_main(void)
{
    xTaskCreate(&receiver, "Sender", 2048, NULL, 2, &receiverHandler); /* ctrl + shift + A makes this nice comment */
    xTaskCreate(&sender, "Receiver", 2048, NULL, 2, NULL);
}