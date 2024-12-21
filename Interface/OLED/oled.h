#ifndef __OLED_H__
#define __OLED_H__
#include "i2c.h"

#define DEV_ADDR  0x78
#define DATA_MODE 0x40
#define CMD_MODE  0x00

void OLED_WriteData(uint8_t bytes[], uint8_t length);
void OLED_WriteCmd(uint8_t bytes[], uint8_t length);
void OLED_Init(void);
void OLED_Clear();
// void OLED_address(uint8_t x, uint8_t y);
void OLED_SetPointer(uint8_t page, uint8_t column);
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t *str);

void OLED_ShowNum(uint8_t x, uint8_t y,int32_t num);
#endif /* __OLED_H__ */