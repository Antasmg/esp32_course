#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "esp_sntp.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_log.h"

void onGotTime(struct timeval *tv) /* tv is a pointer to timeval structure (I believe) */
{
    ESP_LOGI("NTP", "Secs : %ld", tv->tv_sec);
    struct tm *timeinfo = localtime(&tv->tv_sec);

    char buffer[50];
    setenv("TZ","CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00",1); /* https://community.progress.com/s/article/P129473 */ 
                                                                   /* last argument (overwrite) - 1 if yes, 0 if no to overwrite the ntp time */
        
    strftime(&buffer, sizeof(buffer), "%c", timeinfo); /* https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm -> formats */
    ESP_LOGW("NTP", "Current time is: %s", buffer);

    example_disconnect();
}


void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    esp_event_loop_create_default();
    example_connect();

    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_setservername(0, "pool.ntp.org"); /* if more ntp servers are used, then the value of 0 needs to be changed */
    sntp_init();

    sntp_set_time_sync_notification_cb(onGotTime); /* when received a callback from ntp server about the time, the onGotTime function is called */
}