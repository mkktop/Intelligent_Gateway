#include "tw51.h"

// �����������51���ݵĻ������ͳ���
uint8_t rxBuff[TW51_INFO_BUFF_SIZE];
uint8_t rxSize;
void TW51_Init(void)
{
    // 1.��ʼ������3
   // MX_USART3_UART_Init();
    // 2.�����жϷ�ʽ���ձ䳤����
    HAL_UARTEx_ReceiveToIdle_IT(&huart3, rxBuff, TW51_INFO_BUFF_SIZE);
}

void TW51_UartCallback(uint16_t size)
{
    // ��ȡ���յ������ݳ���
    rxSize = size;
    // ���¿����жϽ��շ�ʽ
    HAL_UARTEx_ReceiveToIdle_IT(&huart3, rxBuff, TW51_INFO_BUFF_SIZE);
}

void TW51_ReadData(uint8_t data[], uint16_t *datalen)
{
    // �����Ҫ�������ݵ�����
    memset(data, 0, strlen((char *)data));
    *datalen = 0;
    // ����rxSize�ж��Ƿ���յ�����
    if (rxSize == 0) {
        return;
    }

    // �����յ������ݸ��Ƶ�data��
    memcpy(data, rxBuff, rxSize);
    *datalen = rxSize;
    // ����
    rxSize = 0;
}
