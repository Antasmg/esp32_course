/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define PIN 2

void app_main(void)
{
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
    uint32_t isOn = 0;

    while (1){
        isOn = !isOn;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(PIN, isOn);
        ESP_LOGI("LED", "LED status %d", isOn);
    }
}