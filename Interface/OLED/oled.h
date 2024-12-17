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
#endif /* __OLED_H__ */