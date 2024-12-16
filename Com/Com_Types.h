#ifndef __COM_TYPES_H__
#define __COM_TYPES_H__
#include "gpio.h"

// 操作返回状态类型
typedef enum {
    COMMON_OK    = 0x00U,
    COMMON_ERROR = 0x01U,
    COMMON_OTHER = 0x02U
} CommonStatus;


#endif /* __COM_TYPES_H__ */