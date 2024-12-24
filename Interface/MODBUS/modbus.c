//modbus协议层
#include "modbus.h"

uint8_t MODBUS_rxBuff[MODBUS_INFO_BUFF_SIZE];
uint8_t MODBUS_rxSize;
void Modbus_Init(void)
{
    // 1.配置中断方式接收变长数据
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, MODBUS_rxBuff, MODBUS_INFO_BUFF_SIZE);
}

void Modbus_UartCallback(uint16_t size)
{
    // 读取接收到的数据长度
    MODBUS_rxSize = size;
    // 重新开启中断接收方式
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, MODBUS_rxBuff, MODBUS_INFO_BUFF_SIZE);
}

void Modbus_ReadData(uint8_t data[], uint16_t *datalen)
{
    // 先清空要保存数据的数组
    memset(data, 0, strlen((char *)data));
    *datalen = 0;
    // 根据rxSize判断是否接收到数据
    if (MODBUS_rxSize == 0) {
        return;
    }

    // 将接收到的数据复制到data中
    memcpy(data, MODBUS_rxBuff, MODBUS_rxSize);
    *datalen = MODBUS_rxSize;
    // 清零
    MODBUS_rxSize = 0;
}

/// @brief 获取二氧化碳浓度，传递给二氧化碳结构体
/// @param carbon 二氧化碳结构体
void Modbus_ReadCO2(Carbon_Dioxide *carbon)
{
    // 使能发送引脚
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_SET);
     // 地址码 功能码 起始地址(2字节) 读取长度(2字节) crc校验(2字节)
    uint8_t buff[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
    HAL_UART_Transmit(&huart2, buff, 8, 1000);
    // 使能接收引脚
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_RESET);
    uint8_t rx_buff[30] = {0};
    uint16_t rx_len     = 0;
    // 超时机制
    uint16_t count = 0;
    while (1) {
        Modbus_ReadData(rx_buff, &rx_len);
        count++;
        if (count > 60000) {
            return;
        }
        if (rx_len > 0) {
            break;
        }
    }
    HAL_UART_Transmit(&huart2, rx_buff, rx_len, 1000);
    uint16_t crc;
    uint8_t crcH, crcL;
    if (rx_buff[0] != MODBUS_ADDR) {
        return;
    } else if (rx_buff[0] == MODBUS_ADDR) {
        crc = mb_crc16(rx_buff, rx_len - 2);
    }
    // 校验码检验
    crcL = crc >> 8;
    printf("crcL:%d\n", crcL);
    crcH = crc & 0xFF;
    printf("crcH:%d\n", crcH);
    if ((rx_buff[rx_len - 2] != crcH) || (rx_buff[rx_len - 1] != crcL)) {
        return;
    }
     // 将数据传递给二氧化碳结构体
    int co2 = ((int)rx_buff[3] << 8) + rx_buff[4];
    printf("co2:%d\n", co2);
    carbon->co2 = co2;
}

/// @brief 获取二氧化碳传感器数据，包括湿度，温度，二氧化碳浓度
/// @param carbon 二氧化碳结构体
void Modbus_ReadAll(Carbon_Dioxide *carbon)
{
    // 使能发送引脚
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_SET);
    // 地址码 功能码 起始地址(2字节) 读取长度(2字节) crc校验(2字节)
    uint8_t buff[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};
    HAL_UART_Transmit(&huart2, buff, 8, 1000);
    // 使能接收引脚
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_RESET);
    // 创建数组用来接收数据
    uint8_t rx_buff[30] = {0};
    uint16_t rx_len     = 0;
    // 超时机制
    uint16_t count = 0;
    while (1) {
        Modbus_ReadData(rx_buff, &rx_len);
        count++;
        if (count > 60000) {
            return;
        }
        if (rx_len > 0) {
            break;
        }
    }
    HAL_UART_Transmit(&huart2, rx_buff, rx_len, 1000);

    uint16_t crc;
    uint8_t crcH, crcL;
    // 验证地址
    if (rx_buff[0] != MODBUS_ADDR) {
        return;
    } else if (rx_buff[0] == MODBUS_ADDR) {
        crc = mb_crc16(rx_buff, rx_len - 2);
    }
    // 校验码检验
    crcL = crc >> 8;
    crcH = crc & 0xFF;
    if ((rx_buff[rx_len - 2] != crcH) || (rx_buff[rx_len - 1] != crcL)) {
        return;
    }
    // 将数据传递给二氧化碳结构体
    int16_t hum = ((int)rx_buff[3] << 8) + rx_buff[4];
    printf("hum:%d\n", hum);
    int16_t temp = ((int)rx_buff[5] << 8) + rx_buff[6];
    printf("temperature:%d\n", temp);
    int16_t co2 = ((int)rx_buff[7] << 8) + rx_buff[8];
    printf("co2:%d\n", co2);
    carbon->co2 = co2;
}
