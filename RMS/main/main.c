#include <stdio.h>
#include "driver/ledc.h"

ledc_timer_config_t myConfig = 
{
    .timer_num = 0,
};

void app_main(void)
{
    //SETUP
    ledc_timer_config(&myConfig);
}
