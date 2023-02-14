#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#define TAG "Memory"

void app_main(void){
    int DRam = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    int IRam = heap_caps_get_free_size(MALLOC_CAP_32BIT) - heap_caps_get_free_size(MALLOC_CAP_8BIT);

    ESP_LOGI(TAG, "DRAM \t\t %d", DRam);
    ESP_LOGI(TAG, "IRam \t\t %d", IRam);

    int free = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
    void *memoryPointer = malloc(free);
    ESP_LOGI(TAG, "Free: %d", free);

    if(memoryPointer == NULL){
        ESP_LOGE(TAG, "Failed to allocate the memory!");
    }
    else{
        ESP_LOGW(TAG, "Memory allocated!");
    }
}