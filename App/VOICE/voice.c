//��ģ��Ϊ����51����������Ҫ��������51ʹ��
#include "voice.h"
#include "debug.h"

/// @brief ��ʼ������
/// @param  ��
void Voice_Init(void)
{
    TW51_Init();
}

/// @brief ������51�����¶���Ϣ���¶���Ϣ��t��β
/// @param carbon ������̼��Ϣ�ṹ��
void Voice_Send_temperature(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%dt", carbon.temperature);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
    debug_printfln("%s", buff);
}

/// @brief ������51����ʪ����Ϣ��ʪ����Ϣ��s��β
/// @param carbon ������̼��Ϣ�ṹ��
void Voice_Send_humidity(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%ds", carbon.humidity);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
}

/// @brief ������51����SO2��Ϣ��SO2��Ϣ��s��β
/// @param carbon ������̼��Ϣ�ṹ��
void Voice_Send_co2(Carbon_Dioxide carbon)
{
    uint8_t buff[20];
    sprintf((char *)buff, "%dc", carbon.co2);
    HAL_UART_Transmit(&huart3, buff, strlen((char *)buff), 2000);
}
