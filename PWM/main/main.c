#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


ledc_timer_config_t ledc_timer = 
{
    .duty_resolution = LEDC_TIMER_10_BIT, // resolution of PWM duty
    .freq_hz = 1000,                      // frequency of PWM signal
    .speed_mode = LEDC_HIGH_SPEED_MODE,    // timer mode
    .timer_num = LEDC_TIMER_0,            // timer index
    .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock.
};


ledc_channel_config_t ledc_channel = 
{
    .channel = LEDC_CHANNEL_0,
    .duty = 0,
    .gpio_num = 18,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .hpoint = 0,
    .timer_sel = LEDC_TIMER_0,
};

#define CHANNEL ADC_CHANNEL_0

#define LED_pin 18

void app_main(void)
{
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
    
    int potWaarde = 0;
    static esp_adc_cal_characteristics_t *adc_chars;
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(CHANNEL, ADC_ATTEN_DB_12);
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, adc_chars);

    while(1)
    {
        potWaarde = esp_adc_cal_raw_to_voltage(adc1_get_raw((adc1_channel_t)CHANNEL), adc_chars);
        printf("Potentiometer waarde: %d mV\n", potWaarde);
        ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, (potWaarde / 12));
        ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
    }

}
