#include <stdio.h>
#include "connect.h"
#include "esp_http_client.h"
#include "nvs_flash.h"
#include "esp_log.h"

esp_err_t on_client_data (esp_http_client_event_t *evt)
{

}

void fetch_quote()
{
    esp_http_client_config_t esp_http_client_config = {
        .url = "https://quotes.rest/qod?language=en",
        .method = HTTP_METHOD_GET,
        .event_handler = on_client_data
    };

    esp_http_client_handle_t http_client = esp_http_client_init(&esp_http_client_config);
}

void app_main(void)
{
    wifi_init();
    ESP_ERROR_CHECK(wifi_connect_sta("WizzDEV", "JestemSzczesliwyWPracy", 10000));
    fetch_quote();
}