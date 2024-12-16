#ifndef __DEBUG_H
#define __DEBUG_H

#include "usart.h"
#include <stdarg.h>
#include <string.h>

// Ϊ�˷�����ԣ�����һ��������ģʽ���ĺ�
#define DEBUG

// ------ ���� DEBUG �Ƿ��壬��ʵ�ֲ�ͬ�Ĵ���������� ----
#ifdef DEBUG
// ����ģʽ��RELEASE���µĺ���ʵ��
#define debug_init() Debug_Init()
// ���ӵ�����Ϣ��[�ļ���:�к�]--
#define _FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define FILENAME (strrchr(_FILENAME, '/') ? strrchr(_FILENAME, '/') + 1 : _FILENAME)

#define debug_printf(format, ...) printf("[%s:%d]--"format, FILENAME, __LINE__,##__VA_ARGS__)
#define debug_printfln(format, ...) printf("[%s:%d]--"format"\r\n", FILENAME, __LINE__,##__VA_ARGS__)

#else
// ����ģʽ��RELEASE���µĺ���ʵ�֣���ʵ�֣�
#define debug_init() 
#define debug_printf(format, ...)   
#define debug_printfln(format, ...)

#endif
// -----------------

// ������ʼ�����������ݺ궨���ж��Ƿ���ã�
void Debug_Init(void);

#endif
