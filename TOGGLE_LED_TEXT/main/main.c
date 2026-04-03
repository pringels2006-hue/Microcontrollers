#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_random.h"

#define LED_BL 25
#define LED_GR 26
#define LED_RE 27


void app_main(void)
{
    gpio_reset_pin(LED_BL);
    gpio_reset_pin(LED_GR);
    gpio_reset_pin(LED_RE);
    gpio_set_direction(LED_BL, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GR, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_RE, GPIO_MODE_OUTPUT);

    bool bl_state = false;
    bool gr_state = false;
    bool re_state = false;
    while(1)
    {
        printf("Red, Green or Blue? (R/G/B):\n");
        char input;

        while(input == 0)
        {
            scanf("%c", &input);
            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
        
        switch(input)
        {
            case 'r':
                re_state = !re_state;
                gpio_set_level(LED_RE, re_state);
                input = 0; // Clear the input buffer
                break;
            case 'g':
                gr_state = !gr_state;
                gpio_set_level(LED_GR, gr_state);
                input = 0; // Clear the input buffer
                break;
            case 'b':
                bl_state = !bl_state;
                gpio_set_level(LED_BL, bl_state);
                input = 0;
                break;
            default:
                printf("Invalid input. Please enter R, G, or B.\n");
                input = 0;
                break;
        }
            
    }
}
