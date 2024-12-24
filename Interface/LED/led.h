//led灯模块，实现了开灯关灯以及翻转
#ifndef __LED_H__
#define __LED_H__
#include "gpio.h"

void LED1_ON(void);

void LED1_DOWN(void);

void LED2_ON(void);

void LED2_DOWN(void);

void LED1_Toggle(void);

void LED2_Toggle(void);

#endif /* __LED_H__ */