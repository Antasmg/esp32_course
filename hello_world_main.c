/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "esp_log.h"

void app_main(void)
{
  // don't forget to set the minimum level in the menuconfig
  esp_log_level_set("LOGGING", ESP_LOG_VERBOSE);
  int myNumber = 5;
  ESP_LOGE("LOGGING", "This is an error %d", myNumber++);
  ESP_LOGW("LOGGING", "This is a warning %d", myNumber++);
  ESP_LOGI("LOGGING", "This is a info %d", myNumber++);
  ESP_LOGD("LOGGING", "This is a debug %d", myNumber++);
  ESP_LOGV("LOGGING", "This is verbose %d", myNumber++);
}