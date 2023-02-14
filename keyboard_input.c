/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"

void app_main(void)
{
  char c = 0;
  char str[100];
  memset(str, 0, sizeof(str));
  
  while (c != '\n')
  {
    c = getchar();
    if (c != 0xff)
    {
      str[strlen(str)] = c;
      printf("%c", c);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  printf("you typed: %s\n", str);
}