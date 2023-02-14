/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "math.h"

#define TAG "DICE"

int randomNumber(){
    int random = esp_random();
    int positive = abs(random);
    int diceRoll = (positive % 6) + 1;
    return diceRoll;
}

void app_main(void)
{
    while (1){
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "Dice: %d", randomNumber());
    }
}