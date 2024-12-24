//该模块为TCP客户端程序
#ifndef __TCP_H__
#define __TCP_H__

#include "eth.h"
#include "socket.h"
#include "Com_Types.h"

// 宏定义
// 使用socket的编号
#define SN 0
// 当前的角色
#define CLIENT 0
#define SERVER 1

// 启动TCP客户端
CommonStatus TCP_ClientStart(void);

// 以TCP方式收发数据
void TCP_SendData(uint8_t data[], uint16_t len);

#endif /* __TCP_H__ */