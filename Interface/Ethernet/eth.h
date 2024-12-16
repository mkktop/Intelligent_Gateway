#ifndef __ETH_H__
#define __ETH_H__

#include "w5500.h"
#include <stdio.h>

// ��ʼ��
void ETH_Init(void);

// ��λ������500us����
void ETH_Reset(void);

// 4. ���������ַ��MAC��
void ETH_SetMac(uint8_t mac[]);

// 5. ����IP��ַ���Լ�������������أ�
void ETH_SetIP(uint8_t ip[]);
#endif /* __ETH_H__ */