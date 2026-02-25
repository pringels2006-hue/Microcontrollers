#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "myGPIO.h"

#define LED_PIN 12
#define KNOP_PIN 26
int currentState = 0;
int previousState = 0;
int amountPressed = 0;
void app_main(void)
{
    myGPIO_LED_setup(LED_PIN);
    myGPIO_knop_setup(KNOP_PIN);
    
    /* initialize previousState to the current input to avoid a spurious edge */
    previousState = myGPIO_knop_read_value(KNOP_PIN);

    while(1)
    {
        currentState = myGPIO_knop_read_value(KNOP_PIN);

        /* detect rising edge only: previous 0 -> current 1 */
        if (previousState == 0 && currentState == 1)
        {
            amountPressed++;
            if (amountPressed == 5) 
            {
                myGPIO_LED_aan(LED_PIN);
                amountPressed = 0; // reset counter after reaching 5
            } 
            else 
            {
                myGPIO_LED_uit(LED_PIN);
            }
        }

        /* update previous state for next iteration */
        previousState = currentState;

        /* small delay to avoid busy-waiting */
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
