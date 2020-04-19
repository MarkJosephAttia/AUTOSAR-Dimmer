#include "Std_Types.h"
#include "Gpio.h"
#include "Led.h"

const led_t Led_leds[LED_NUMBER_OF_LEDS] = {
    {GPIO_PIN_0, GPIO_PORTA, GPIO_PIN_SET}
};
