//天问51模块接口
#ifndef __TW51_H__
#define __TW51_H__

#include "usart.h"
#include "debug.h"

//宏定义
#define TW51_INFO_BUFF_SIZE 128

void TW51_Init(void);

void TW51_ReadData(uint8_t data[], uint16_t *datalen);
#endif /* __TW51_H__ */