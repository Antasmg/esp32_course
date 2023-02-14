
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore;

void listenForHTTP(void *params)
{
  while (true)
  {
    printf("received http message\n"); /* first */
    xSemaphoreGive(binSemaphore);
    printf("processed http message\n"); /* third, because they have the same priority (if this task had higher priority, then this would be second) */
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void task1(void *params)
{
  while (true)
  {
    xSemaphoreTake(binSemaphore, portMAX_DELAY);
    printf("doing something with http\n"); /* second */
  }
}

void app_main(void)
{
  binSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(&listenForHTTP, "get http", 2048, NULL, 1, NULL);
  xTaskCreate(&task1, "do something with http", 2048, NULL, 1, NULL);
}