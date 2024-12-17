#ifndef __COM_TYPES_H__
#define __COM_TYPES_H__
#include "gpio.h"

// ��������״̬����
typedef enum {
    COMMON_OK    = 0x00U, 
    COMMON_ERROR = 0x01U,
    COMMON_OTHER = 0x02U
} CommonStatus;


// ������̼��������Ϣ�ṹ��
typedef struct
{
    int temperature;  // �¶�
    uint8_t humidity; // ʪ��
    uint16_t co2;     // ������̼
} Carbon_Dioxide;

#endif /* __COM_TYPES_H__ */