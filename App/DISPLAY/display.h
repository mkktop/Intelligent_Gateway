#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "stdio.h"
#include "oled.h"
#include "string.h"
#include "Com_Types.h"
void display_init(void);

void display_temperature(Carbon_Dioxide carbon);

void display_humidity(Carbon_Dioxide carbon);

void display_co2(Carbon_Dioxide carbon);

void display_all(Carbon_Dioxide carbon);
#endif /* __DISPLAY_H__ */