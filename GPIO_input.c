#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define PIN_SWITCH 18

// xQueueHandle interruptQueue;
QueueHandle_t interruptQueue;

static void IRAM_ATTR gpio_isr_handler(void *args)
{
    int pinNumber = (int)args;
    xQueueSendFromISR(interruptQueue, &pinNumber, NULL);
}

void buttonPushedTask(void *params)
{
    int pinNumber, count = 0;
    while (true)
    {
        if (xQueueReceive(interruptQueue, &pinNumber, portMAX_DELAY))
        {
            printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(PIN_SWITCH));
        }
    }
}

void app_main()
{
    // gpio_pad_select_gpio(PIN_SWITCH);
    gpio_set_direction(PIN_SWITCH, GPIO_MODE_INPUT);
    gpio_pullup_en(PIN_SWITCH);   /* enable pull-down - is LOW when not pressed */
    gpio_pulldown_dis(PIN_SWITCH);    /* disable pull-up (they are other way round because I changed them)*/ 
    gpio_set_intr_type(PIN_SWITCH, GPIO_INTR_NEGEDGE); /* interrupt will be fired when PIN_SWITCH is on positive edge */

    interruptQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(buttonPushedTask, "buttonPushedTask", 2048, NULL, 1, NULL);

    gpio_install_isr_service(0); /* enable global interrupts */
    gpio_isr_handler_add(PIN_SWITCH, gpio_isr_handler, (void *)PIN_SWITCH); /* PIN_SWITCH IS AN ARGUMENT CHANGED TO VOID AND PASSED TO gpio_isr_handler_add */
}