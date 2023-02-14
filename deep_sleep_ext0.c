#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "esp_log.h"

#define BUTTON GPIO_NUM_25

RTC_DATA_ATTR int timesWokenUp = 0;
void app_main(void)
{
  rtc_gpio_deinit(BUTTON);          /* This method allows to use the pin as a normal GPIO */

  rtc_gpio_pullup_en(BUTTON);       /* This function only works for RTC IOs */
  rtc_gpio_pulldown_dis(BUTTON);    /* This function only works for RTC IOs */
  esp_sleep_enable_ext0_wakeup(BUTTON,0);
    
    ESP_LOGW("SLEEP", "Good night ;)! Went to sleep %d times", timesWokenUp++);

  esp_deep_sleep_start();
}