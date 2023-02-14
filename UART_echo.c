#include <stdio.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "esp_log.h"

#define TXD_PIN 4
#define RXD_PIN 5

#define RX_BUF_SIZE 1024 /* 1kB */

void app_main(void)
{
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .stop_bits = UART_STOP_BITS_1
    };
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE,0,0,NULL,0);

    char message[] = "ping";
    ESP_LOGI("UART TX", "Sending message: %s", message);
    uart_write_bytes(UART_NUM_1, &message, sizeof(message));

    char incomingMessage[RX_BUF_SIZE];
    memset(incomingMessage, 0, RX_BUF_SIZE); /* fill the array with 0s */
    uart_read_bytes(UART_NUM_1, &incomingMessage, RX_BUF_SIZE, pdMS_TO_TICKS(500));
    ESP_LOGI("UART RX", "Receive message: %s", incomingMessage);
}