/* LIGHT SLEEP WITH TIMER */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h"
#include "esp_timer.h"

void app_main(void)
{
    ESP_LOGE("SLEEP", "I'M ABOUT TO FALL A SLEEP!!!");
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM); /* if instead pf a LOG printf was used, then this one is needed in order to print the message */

    esp_sleep_enable_timer_wakeup(5000000);
    
    uint64_t before = esp_timer_get_time();

    esp_light_sleep_start();

    uint64_t after = esp_timer_get_time();

    ESP_LOGI("SLEEP", "I have been sleeping for %lld seconds", (after-before)/1000000);
}