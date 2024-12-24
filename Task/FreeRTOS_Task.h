//FreeRTOS任务程序（核心）
#ifndef __FREERTOS_TASK_H__
#define __FREERTOS_TASK_H__
#include "FreeRTOS.h"
#include "task.h"
#include "Com_Types.h"
#include "oled.h"
#include "tw51.h"
#include "voice.h"
#include "display.h"
#include "TCP.h"
#include "key.h"
#include "led.h"
#include "modbus.h"

void FreeRTOS_Task_Start(void);

#endif /* __FREERTOS_TASK_H__ */