#include "FreeRTOS_Task.h"
#include "TCP.h"

void TCP_Task(void *arg);
#define TCP_TASK_NAME     "TCP_Task"
#define TCP_TASK_STACK    100
#define TCP_TASK_PRIORITY 5
TaskHandle_t TCP_Task_Handler;
#define TCP_TASK_PERIOD 2000

void OLED_Task(void *arg);
#define OLED_TASK_NAME     "OLED_Task"
#define OLED_TASK_STACK    256
#define OLED_TASK_PRIORITY 5
TaskHandle_t OLED_Task_Handler;

void TW51_Task(void *arg);
#define TW51_TASK_NAME     "TW51_Task"
#define TW51_TASK_STACK    256
#define TW51_TASK_PRIORITY 5
TaskHandle_t TW51_Task_Handler;

void FreeRTOS_Task_Start(void)
{
    // 初始化相关硬件
    display_init();
    Voice_Init();
    // 创建任务
    xTaskCreate(TCP_Task, TCP_TASK_NAME, TCP_TASK_STACK, NULL, TCP_TASK_PRIORITY, &TCP_Task_Handler);
    //xTaskCreate(OLED_Task, OLED_TASK_NAME, OLED_TASK_STACK, NULL, OLED_TASK_PRIORITY, &OLED_Task_Handler);
    xTaskCreate(TW51_Task, TW51_TASK_NAME, TW51_TASK_STACK, NULL, TW51_TASK_PRIORITY, &TW51_Task_Handler);
    // 启动调度器
    vTaskStartScheduler();
}

void TCP_Task(void *arg)
{
    // ETH_Init(); // 初始化以太网
    //  启动TCP客户端
    // TCP_ClientStart();
    while (1) {
        //printf("TCP_Task\r\n");
        vTaskDelay(1000);
    }
}

void OLED_Task(void *arg)
{
    int32_t n = 0;
    OLED_ShowStr(0, 0, (uint8_t *)"Hello World!");
    while (1) {
        OLED_ShowNum(0, 1, n++);
        // printf("OLED_Task\r\n");
        //printf("%d\n", n);
        vTaskDelay(50);
    }
}

uint8_t buff[100];
uint16_t bufflen;


Carbon_Dioxide carbon = {
    .temperature = 36,
    .co2         = 3564,
    .humidity    = 60};
void TW51_Task(void *arg)
{
    while (1) {
        TW51_ReadData(buff, &bufflen);
        if (bufflen > 0) {
            printf("%s\n", buff);
            if (strcmp((char *)buff, "bbb") == 0) {                
                Voice_Send_temperature(carbon);
                display_temperature(carbon);                
            } else if (strcmp((char *)buff, "aaa") == 0) {
                Voice_Send_co2(carbon);
                display_co2(carbon);                
            }else if (strcmp((char *)buff, "ccc") == 0)
            {
                Voice_Send_humidity(carbon);
                display_humidity(carbon);
            }
            
        }
    }
}
