#include "tw51.h"

// 定义接收天问51数据的缓冲区和长度
uint8_t rxBuff[TW51_INFO_BUFF_SIZE];
uint8_t rxSize;
void TW51_Init(void)
{
    // 1.初始化串口3
   // MX_USART3_UART_Init();
    // 2.配置中断方式接收变长数据
    HAL_UARTEx_ReceiveToIdle_IT(&huart3, rxBuff, TW51_INFO_BUFF_SIZE);
}

void TW51_UartCallback(uint16_t size)
{
    // 读取接收到的数据长度
    rxSize = size;
    // 重新开启中断接收方式
    HAL_UARTEx_ReceiveToIdle_IT(&huart3, rxBuff, TW51_INFO_BUFF_SIZE);
}

void TW51_ReadData(uint8_t data[], uint16_t *datalen)
{
    // 先清空要保存数据的数组
    memset(data, 0, strlen((char *)data));
    *datalen = 0;
    // 根据rxSize判断是否接收到数据
    if (rxSize == 0) {
        return;
    }

    // 将接收到的数据复制到data中
    memcpy(data, rxBuff, rxSize);
    *datalen = rxSize;
    // 清零
    rxSize = 0;
}
