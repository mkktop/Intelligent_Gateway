//��ģ��Ϊ����51����������Ҫ��������51ʹ��
#ifndef __VOICE_H__
#define __VOICE_H__

#include "tw51.h"
#include "Com_Types.h"
#include "usart.h"
void Voice_Init(void);

//������51�����ض���ʽ������
//1.�¶���t��β
void Voice_Send_temperature(Carbon_Dioxide carbon);
//2.ʪ����s��β
void Voice_Send_humidity(Carbon_Dioxide carbon);
//3.CO2��c��β
void Voice_Send_co2(Carbon_Dioxide carbon);

#endif /* __VOICE_H__ */