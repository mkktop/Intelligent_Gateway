//该模块为天问51播报程序，需要搭配天问51使用
#include "voice.h"
#include "debug.h"

/// @brief 初始化程序
/// @param  无
void Voice_Init(void)
{
    TW51_Init();
}

/// @brief 向天问51发送温度信息，温度信息以t结尾
/// @param carbon 二氧化碳信息结构体
void Voice_Send_temperature(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%dt", carbon.temperature);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
    debug_printfln("%s", buff);
}

/// @brief 向天问51发送湿度信息，湿度信息以s结尾
/// @param carbon 二氧化碳信息结构体
void Voice_Send_humidity(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%ds", carbon.humidity);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
}

/// @brief 向天问51发送SO2信息，SO2信息以s结尾
/// @param carbon 二氧化碳信息结构体
void Voice_Send_co2(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%dc", carbon.co2);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
}
