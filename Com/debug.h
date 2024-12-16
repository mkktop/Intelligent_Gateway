#ifndef __DEBUG_H
#define __DEBUG_H

#include "usart.h"
#include <stdarg.h>
#include <string.h>

// 为了方便调试，定义一个“调试模式”的宏
#define DEBUG

// ------ 根据 DEBUG 是否定义，来实现不同的串口输出函数 ----
#ifdef DEBUG
// 调试模式（RELEASE）下的函数实现
#define debug_init() Debug_Init()
// 增加调试信息，[文件名:行号]--
#define _FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define FILENAME (strrchr(_FILENAME, '/') ? strrchr(_FILENAME, '/') + 1 : _FILENAME)

#define debug_printf(format, ...) printf("[%s:%d]--"format, FILENAME, __LINE__,##__VA_ARGS__)
#define debug_printfln(format, ...) printf("[%s:%d]--"format"\r\n", FILENAME, __LINE__,##__VA_ARGS__)

#else
// 发布模式（RELEASE）下的函数实现（空实现）
#define debug_init() 
#define debug_printf(format, ...)   
#define debug_printfln(format, ...)

#endif
// -----------------

// 声明初始化函数（根据宏定义判断是否调用）
void Debug_Init(void);

#endif
