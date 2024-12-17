#include "voice.h"

void Voice_Init(void)
{
    TW51_Init();
}

void Voice_Send_temperature(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%dt", carbon.temperature);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
}

void Voice_Send_humidity(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%ds", carbon.humidity);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
}

void Voice_Send_co2(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%dc", carbon.co2);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
}
