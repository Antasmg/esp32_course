#include <stdio.h>
#include "connect.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TAG "WiFi"

void wifi_connect(void *params){
    wifi_connect_ap("esp-ap", "12345678");
    for (int i = 45; i > 0; i--)
    {
        ESP_LOGW(TAG, "Disabling AP in %d, seconds", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    wifi_disconnect();

    esp_err_t err = wifi_connect_sta("WizzDEV", "JestemSzczesliwyWPracy", 10000);
    if(err)
    {
        ESP_LOGE(TAG, "Failed to connect!");
        vTaskDelete(NULL); /* NULL because this is the current task */
    }

    for (int i = 5; i > 0; i--)
    {
        ESP_LOGW(TAG, "Disconnecting in %d, seconds", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    wifi_disconnect();
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init();
    xTaskCreate(wifi_connect, "wifi_connect",1024*5,NULL,5,NULL);
}