#ifndef __COM_TYPES_H__
#define __COM_TYPES_H__
#include "gpio.h"

// 操作返回状态类型
typedef enum {
    COMMON_OK    = 0x00U, 
    COMMON_ERROR = 0x01U,
    COMMON_OTHER = 0x02U
} CommonStatus;


// 二氧化碳传感器信息结构体
typedef struct
{
    int temperature;  // 温度
    uint8_t humidity; // 湿度
    uint16_t co2;     // 二氧化碳
} Carbon_Dioxide;

#endif /* __COM_TYPES_H__ */