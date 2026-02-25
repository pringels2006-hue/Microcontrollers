#include <stdio.h>
#include "myGPIO.h"
#include "driver/gpio.h"                                                                                                

//LED

void myGPIO_LED_aan(int pin)
{
    gpio_set_level(pin, 1);
}

void myGPIO_LED_uit(int pin)
{
    gpio_set_level(pin, 0);
}
void myGPIO_LED_toggle(int pin)
{
    int current_value = gpio_get_level(pin);
    int new_value = !current_value;
    gpio_set_level(pin, new_value);
}
void myGPIO_LED_setup(int pin)
{
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT);
}
void myGPIO_LED_write_value(int pin, int value);

//INPUT KNOP

void myGPIO_knop_setup(int pin)
{
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT); 
    gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
}
int myGPIO_knop_read_value(int pin)
{
    return gpio_get_level(pin);
}
int myGPIO_knop_edge(int pin)
{
    static int last_value = 0;
    int current_value = gpio_get_level(pin);
    int edge_detected = 0;

    if (current_value != last_value) 
    {
        edge_detected = 1; 
    }

    last_value = current_value; 
    return edge_detected;
}


