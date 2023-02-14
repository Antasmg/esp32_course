#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define PIN_SWITCH 18

// xQueueHandle interruptQueue;
QueueHandle_t interruptQueue; /* creating a queue */

static void IRAM_ATTR gpio_isr_handler(void *args)
{
    int pinNumber = (int)args; /* converting from void to int */
    xQueueSendFromISR(interruptQueue, &pinNumber, NULL); /* from ISR to queue */
}

void buttonPushedTask(void *params)
{
    int pinNumber, count = 0;
    while (true)
    {
        if (xQueueReceive(interruptQueue, &pinNumber, portMAX_DELAY)) /* waiting MAX time to receive something to queue */
        {
            printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(PIN_SWITCH));
        }
    }
}

void app_main()
{
    // gpio_pad_select_gpio(PIN_SWITCH);
    gpio_config_t config;
    config.intr_type = GPIO_INTR_POSEDGE;
    config.mode = GPIO_MODE_INPUT;
    config.pull_down_en = false;
    config.pull_up_en = true;
    config.pin_bit_mask = ((1ULL << PIN_SWITCH) | (1ULL << 5)); /* OR ("|") to add more pins */

    gpio_config(&config);

    interruptQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(buttonPushedTask, "buttonPushedTask", 2048, NULL, 1, NULL);

    gpio_install_isr_service(0); /* enable global interrupts */
    gpio_isr_handler_add(PIN_SWITCH, gpio_isr_handler, (void *)PIN_SWITCH); /* PIN_SWITCH IS AN ARGUMENT CHANGED TO VOID AND PASSED TO gpio_isr_handler_add */
}