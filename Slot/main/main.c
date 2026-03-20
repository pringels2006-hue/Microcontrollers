#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


#define LED_LOCK 18
#define BTN_LOCK 26

#define CHANNEL ADC_CHANNEL_0
void app_main(void)
{
    gpio_reset_pin(LED_LOCK);
    gpio_set_direction(LED_LOCK, GPIO_MODE_OUTPUT);

    gpio_reset_pin(BTN_LOCK);
    gpio_set_direction(BTN_LOCK, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_LOCK, GPIO_PULLDOWN_ONLY);

    int potWaarde = 0;
    static esp_adc_cal_characteristics_t *adc_chars;
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(CHANNEL, ADC_ATTEN_DB_12);
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, adc_chars);

    int code[] = {0, 0, 0, 0};
    int guess[] = {0, 0, 0, 0};
    bool codeIsEmpty = false;
    while (1)
    {
        if(((code[0] == 0) && (code[1] == 0) && (code[2] == 0) && (code[3] == 0)) || (codeIsEmpty == true))
        {
            potWaarde = esp_adc_cal_raw_to_voltage(adc1_get_raw((adc1_channel_t)CHANNEL), adc_chars);
            int getal = potWaarde / 311;
            printf("%d\n", getal);
            codeIsEmpty = true;
            int i = 0;
            if(gpio_get_level(BTN_LOCK) == 1)
            {
                code[i] = getal;
                i++;
                if(code[3] != 0)
                {
                    codeIsEmpty = false;
                }
            }
            
        }
        else
        {
            gpio_set_level(LED_LOCK, 1);
            potWaarde = esp_adc_cal_raw_to_voltage(adc1_get_raw((adc1_channel_t)CHANNEL), adc_chars);
            int getal = potWaarde / 102.3;
            printf("%d\n", getal);
            int i = 0;
            if(gpio_get_level(BTN_LOCK) == 1)
            {
                guess[i] = getal;
                i++;
            }
            
            if(guess[3] != 0)
            {
                if((code[0] == guess[0]) && (code[1] == guess[1]) && (code[2] == guess[2]) && (code[3] == guess[3]))
                {
                    gpio_set_level(LED_LOCK, 0);
                }
                else
                {
                    gpio_set_level(LED_LOCK, 0);
                    vTaskDelay(200 / portTICK_PERIOD_MS);
                    gpio_set_level(LED_LOCK, 1);
                    vTaskDelay(200 / portTICK_PERIOD_MS);
                    gpio_set_level(LED_LOCK, 0);
                    vTaskDelay(200 / portTICK_PERIOD_MS);
                    gpio_set_level(LED_LOCK, 1);

                    

                }
            }
        }
        
        
    }
    
}
