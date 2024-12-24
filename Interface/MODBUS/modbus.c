//modbusЭ���
#include "modbus.h"

uint8_t MODBUS_rxBuff[MODBUS_INFO_BUFF_SIZE];
uint8_t MODBUS_rxSize;
void Modbus_Init(void)
{
    // 1.�����жϷ�ʽ���ձ䳤����
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, MODBUS_rxBuff, MODBUS_INFO_BUFF_SIZE);
}

void Modbus_UartCallback(uint16_t size)
{
    // ��ȡ���յ������ݳ���
    MODBUS_rxSize = size;
    // ���¿����жϽ��շ�ʽ
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, MODBUS_rxBuff, MODBUS_INFO_BUFF_SIZE);
}

void Modbus_ReadData(uint8_t data[], uint16_t *datalen)
{
    // �����Ҫ�������ݵ�����
    memset(data, 0, strlen((char *)data));
    *datalen = 0;
    // ����rxSize�ж��Ƿ���յ�����
    if (MODBUS_rxSize == 0) {
        return;
    }

    // �����յ������ݸ��Ƶ�data��
    memcpy(data, MODBUS_rxBuff, MODBUS_rxSize);
    *datalen = MODBUS_rxSize;
    // ����
    MODBUS_rxSize = 0;
}

/// @brief ��ȡ������̼Ũ�ȣ����ݸ�������̼�ṹ��
/// @param carbon ������̼�ṹ��
void Modbus_ReadCO2(Carbon_Dioxide *carbon)
{
    // ʹ�ܷ�������
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_SET);
     // ��ַ�� ������ ��ʼ��ַ(2�ֽ�) ��ȡ����(2�ֽ�) crcУ��(2�ֽ�)
    uint8_t buff[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
    HAL_UART_Transmit(&huart2, buff, 8, 1000);
    // ʹ�ܽ�������
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_RESET);
    uint8_t rx_buff[30] = {0};
    uint16_t rx_len     = 0;
    // ��ʱ����
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
    // У�������
    crcL = crc >> 8;
    printf("crcL:%d\n", crcL);
    crcH = crc & 0xFF;
    printf("crcH:%d\n", crcH);
    if ((rx_buff[rx_len - 2] != crcH) || (rx_buff[rx_len - 1] != crcL)) {
        return;
    }
     // �����ݴ��ݸ�������̼�ṹ��
    int co2 = ((int)rx_buff[3] << 8) + rx_buff[4];
    printf("co2:%d\n", co2);
    carbon->co2 = co2;
}

/// @brief ��ȡ������̼���������ݣ�����ʪ�ȣ��¶ȣ�������̼Ũ��
/// @param carbon ������̼�ṹ��
void Modbus_ReadAll(Carbon_Dioxide *carbon)
{
    // ʹ�ܷ�������
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_SET);
    // ��ַ�� ������ ��ʼ��ַ(2�ֽ�) ��ȡ����(2�ֽ�) crcУ��(2�ֽ�)
    uint8_t buff[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};
    HAL_UART_Transmit(&huart2, buff, 8, 1000);
    // ʹ�ܽ�������
    HAL_GPIO_WritePin(TR_485_GPIO_Port, TR_485_Pin, GPIO_PIN_RESET);
    // ��������������������
    uint8_t rx_buff[30] = {0};
    uint16_t rx_len     = 0;
    // ��ʱ����
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
    // ��֤��ַ
    if (rx_buff[0] != MODBUS_ADDR) {
        return;
    } else if (rx_buff[0] == MODBUS_ADDR) {
        crc = mb_crc16(rx_buff, rx_len - 2);
    }
    // У�������
    crcL = crc >> 8;
    crcH = crc & 0xFF;
    if ((rx_buff[rx_len - 2] != crcH) || (rx_buff[rx_len - 1] != crcL)) {
        return;
    }
    // �����ݴ��ݸ�������̼�ṹ��
    int16_t hum = ((int)rx_buff[3] << 8) + rx_buff[4];
    printf("hum:%d\n", hum);
    int16_t temp = ((int)rx_buff[5] << 8) + rx_buff[6];
    printf("temperature:%d\n", temp);
    int16_t co2 = ((int)rx_buff[7] << 8) + rx_buff[8];
    printf("co2:%d\n", co2);
    carbon->co2 = co2;
}
