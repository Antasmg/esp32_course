#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/dac.h"

void app_main(void)
{
    dac_output_enable(DAC_CHANNEL_1); /* enabling DAC on Channel 1 (port25) */
    dac_output_voltage(DAC_CHANNEL_1, 155); /* 255 is a maximum; it corresponds to 3.3V; the lower the value, the dimmer the light */
}