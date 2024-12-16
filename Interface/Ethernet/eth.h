#ifndef __ETH_H__
#define __ETH_H__

#include "w5500.h"
#include <stdio.h>

// 初始化
void ETH_Init(void);

// 复位，保持500us以上
void ETH_Reset(void);

// 4. 设置物理地址（MAC）
void ETH_SetMac(uint8_t mac[]);

// 5. 设置IP地址（以及子网掩码和网关）
void ETH_SetIP(uint8_t ip[]);
#endif /* __ETH_H__ */