#include <stdio.h>
#include "esp_log.h"

#define TAG "CONFIG"

void app_main(void){
    ESP_LOGI(TAG, "My int: %d", CONFIG_MY_INT);
    ESP_LOGI(TAG, "My string: %s", CONFIG_MY_STRING);

    bool myBool;
    #ifdef CONFIG_MY_BOOL
    myBool = true;
    #else
    myBool = false;
    #endif

    ESP_LOGI(TAG, "My bool: %s", myBool? "yes" : "no");

    int option;

    #ifdef CONFIG_OPTION_1
    option = 1;
    #elif CONFIG_OPTION_2
    option = 2;
    #else
    option = 3;
    #endif

    ESP_LOGI(TAG, "My option: %d", option);

}