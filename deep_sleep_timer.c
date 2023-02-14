#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"

#define TAG "SLEEP"

RTC_DATA_ATTR int timesWokenUp = 0; /* RTC_DATA_ATTR allows to store a value even during deep sleep */

void app_main(void)
{
    esp_sleep_enable_timer_wakeup(5 * 1000000);
    ESP_LOGW(TAG, "Good night! ;). Went to sleep %d times", timesWokenUp++);

    esp_deep_sleep_start();
}