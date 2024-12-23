#include "key.h"

void key_init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start(&hadc1);
}

uint8_t key_GetKey(void)
{
    double v = HAL_ADC_GetValue(&hadc1) * 3.3 / 4095;
    // printf("v:%.2f\r\n", v);
    if (v < 0.1) {
        vTaskDelay(15);
        if (v < 0.1) {
            return 1;
        }
        return 0;
    } else if (v < 1.7 && v > 1.6) {
        vTaskDelay(15);
        if (v < 1.7 && v > 1.6) {
            return 2;
        }
        return 0;
    } else if (v < 2.2 && v > 2.1) {
        vTaskDelay(15);
        if (v < 2.2 && v > 2.1)
        {
            return 3;
        } 
        return 0;               
    } else if (v < 2.5 && v > 2.4) {
        vTaskDelay(15);
        if (v < 2.5 && v > 2.4)
        {
           return 4;
        }  
        return 0;     
    } else if (v < 2.7 && v > 2.59) {
        vTaskDelay(15);
        if (v < 2.7 && v > 2.59)
        {
           return 5;
        } 
        return 0;           
    } else {
        return 0;
    }
}
