#ifndef __KEY_H__
#define __KEY_H__
#include "adc.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
void key_init(void);

uint8_t key_GetKey(void);
#endif /* __KEY_H__ */