#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h"
#include "esp_timer.h"
#include "driver/rtc_io.h" /* use GPIO pins normaly + when they are sleeping */

#define INPUT_PIN 0

void app_main(void)
{
    gpio_pad_select_gpio(INPUT_PIN);
    gpio_set_direction(INPUT_PIN, GPIO_MODE_INPUT);
    gpio_wakeup_enable(INPUT_PIN, GPIO_INTR_LOW_LEVEL);

    esp_sleep_enable_gpio_wakeup();
    esp_sleep_enable_timer_wakeup(5000000);
    
    while (true)
    {
        if (rtc_gpio_get_level(INPUT_PIN) == 0)
        {
            printf("please release button\n");
            do
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            } while (rtc_gpio_get_level(INPUT_PIN) == 0);
        }

        ESP_LOGE("SLEEP", "I'M ABOUT TO FALL A SLEEP!!!");
        uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

        uint64_t before = esp_timer_get_time();

        esp_light_sleep_start();

        uint64_t after = esp_timer_get_time();

        esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();

        ESP_LOGI("SLEEP", "I have been sleeping for %lld seconds", (after-before)/1000000);
        ESP_LOGI("WAKE UP", "The reason for wake up was: %s", reason == ESP_SLEEP_WAKEUP_TIMER? "timer": "button");
    }
}