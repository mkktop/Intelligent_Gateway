//��ģ��Ϊ debugģ�飬���ڵ��ԣ�������Ϣͨ���������
#include "debug.h"

void Debug_Init()
{
    MX_USART1_UART_Init();
}

int fputc(int ch, FILE *file)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
    return ch;
}
