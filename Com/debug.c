/*
 * @Author: wushengran
 * @Date: 2024-10-15 15:31:37
 * @Description: 
 * 
 * Copyright (c) 2024 by atguigu, All Rights Reserved. 
 */
#include "debug.h"

void Debug_Init()
{
    MX_USART1_UART_Init();
}

int fputc(int ch, FILE *file)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);
    return ch;
}
