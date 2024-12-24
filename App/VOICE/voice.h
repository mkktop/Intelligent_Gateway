//该模块为天问51播报程序，需要搭配天问51使用
#ifndef __VOICE_H__
#define __VOICE_H__

#include "tw51.h"
#include "Com_Types.h"
#include "usart.h"
void Voice_Init(void);

//向天问51发送特定格式的数据
//1.温度以t结尾
void Voice_Send_temperature(Carbon_Dioxide carbon);
//2.湿度以s结尾
void Voice_Send_humidity(Carbon_Dioxide carbon);
//3.CO2以c结尾
void Voice_Send_co2(Carbon_Dioxide carbon);

#endif /* __VOICE_H__ */