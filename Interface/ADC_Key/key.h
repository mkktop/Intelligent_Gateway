//该模块为ADC按键模块，定义了5个按键
#ifndef __KEY_H__
#define __KEY_H__
#include "adc.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
void key_init(void);

uint8_t key_GetKey(void);
#endif /* __KEY_H__ */