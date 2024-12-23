#include "led.h"

void LED1_ON(void)
{
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
}

void LED1_DOWN(void)
{
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
}

void LED2_ON(void)
{
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
}

void LED2_DOWN(void)
{
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
}

void LED1_Toggle(void)
{
    HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
}

void LED2_Toggle(void)
{
    HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
}
