#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"

#define TAG "SLEEP"
RTC_DATA_ATTR int timesWokenUp = 0;

void app_main(void)
{
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
        esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF); /* if this one is off, the value of timesWokenUp will be odd */
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);

    esp_sleep_enable_timer_wakeup(5 * 1000000);
    ESP_LOGW(TAG, "Good night! ;). Went to sleep %d times", timesWokenUp++);
    esp_deep_sleep_start();
}