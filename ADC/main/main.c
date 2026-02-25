#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define LED_Groen 16
#define LED_Geel 17
#define LED_Rood 15

#define CHANNEL ADC_CHANNEL_0
void app_main(void)
{
    gpio_reset_pin(LED_Groen);
    gpio_reset_pin(LED_Geel);
    gpio_reset_pin(LED_Rood);
    gpio_set_direction(LED_Groen, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_Geel, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_Rood, GPIO_MODE_OUTPUT);
    int potWaarde = 0; 

    static esp_adc_cal_characteristics_t *adc_chars;
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(CHANNEL, ADC_ATTEN_DB_12);
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, adc_chars);
    while (1)
    {
      potWaarde = esp_adc_cal_raw_to_voltage(adc1_get_raw((adc1_channel_t)CHANNEL), adc_chars);
    
      printf("Potentiometer waarde: %d mV\n", potWaarde);
      if (potWaarde < 700) {
        gpio_set_level(LED_Groen, 1);
        gpio_set_level(LED_Geel, 0);
        gpio_set_level(LED_Rood, 0);
      }
      else if (potWaarde > 700 && potWaarde < 2000) {
        gpio_set_level(LED_Groen, 0);
        gpio_set_level(LED_Geel, 1);
        gpio_set_level(LED_Rood, 0);
      }
      else {
        gpio_set_level(LED_Groen, 0);
        gpio_set_level(LED_Geel, 0);
        gpio_set_level(LED_Rood, 1);
      }
    }
    
    


}
