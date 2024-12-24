//该模块为ADC按键模块，定义了5个按键
#include "key.h"

/// @brief 初始化程序
/// @param  
void key_init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start(&hadc1);
}

/// @brief 获取按键
/// @param  无
/// @return 按下的按键
uint8_t key_GetKey(void)
{
    double v = HAL_ADC_GetValue(&hadc1) * 3.3 / 4095;
    // printf("v:%.2f\r\n", v);//打印电压
    if (v < 0.1) {
        //按键1
        vTaskDelay(15);
        if (v < 0.1) {
            return 1;
        }
        return 0;
    } else if (v < 1.7 && v > 1.6) {
        //按键2
        vTaskDelay(15);
        if (v < 1.7 && v > 1.6) {
            return 2;
        }
        return 0;
    } else if (v < 2.2 && v > 2.1) {
        //按键3
        vTaskDelay(15);
        if (v < 2.2 && v > 2.1)
        {
            return 3;
        } 
        return 0;               
    } else if (v < 2.5 && v > 2.4) {
        //按键4
        vTaskDelay(15);
        if (v < 2.5 && v > 2.4)
        {
           return 4;
        }  
        return 0;     
    } else if (v < 2.7 && v > 2.59) {
        //按键5
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
