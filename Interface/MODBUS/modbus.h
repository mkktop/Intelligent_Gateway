//modbus协议层
#ifndef __MODBUS_H__
#define __MODBUS_H__
#include "Com_Types.h"
#include "gpio.h"
#include "usart.h"
#include "string.h"
#include "mb_crc.h"
//宏定义
#define MODBUS_INFO_BUFF_SIZE 100
#define MODBUS_ADDR 0x01
void Modbus_Init(void);

void Modbus_UartCallback(uint16_t size);

void Modbus_ReadData(uint8_t data[], uint16_t *datalen);

void Modbus_ReadCO2(Carbon_Dioxide *carbon);
void Modbus_ReadAll(Carbon_Dioxide *carbon);
#endif /* __MODBUS_H__ */