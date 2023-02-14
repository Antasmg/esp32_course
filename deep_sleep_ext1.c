#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "esp_log.h"

#define BUTTON1 GPIO_NUM_25
#define BUTTON2 GPIO_NUM_26

RTC_DATA_ATTR int timesWokenUp = 0;
void app_main(void)
{
  rtc_gpio_deinit(BUTTON1);          /* This method allows to use the pin as a normal GPIO */
  rtc_gpio_deinit(BUTTON2);

  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

  rtc_gpio_pullup_en(BUTTON1);       /* This function only works for RTC IOs */
  rtc_gpio_pulldown_dis(BUTTON1);    /* This function only works for RTC IOs */
  rtc_gpio_pullup_en(BUTTON2);       /* This function only works for RTC IOs */
  rtc_gpio_pulldown_dis(BUTTON2);    /* This function only works for RTC IOs */
  
  uint64_t mask = (1ULL << BUTTON1) | (1ULL << BUTTON2);
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW); /* to use any high, we would need to connect buttons to 3.3V, enable pull down and disable pullup  */
    
    ESP_LOGW("SLEEP", "Good night ;)! Went to sleep %d times", timesWokenUp++);

  esp_deep_sleep_start();
}