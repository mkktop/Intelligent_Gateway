#include "FreeRTOS_Task.h"
#include "TCP.h"


void TCP_Task(void *arg);
#define TCP_TASK_NAME     "TCP_Task"
#define TCP_TASK_STACK    128
#define TCP_TASK_PRIORITY 5
TaskHandle_t TCP_Task_Handler;
#define TCP_TASK_PERIOD 100

void FreeRTOS_Task_Start(void)
{
    // 初始化相关硬件

    // 创建任务

    // 启动调度器
    vTaskStartScheduler();
}

void TCP_Task(void *arg)
{
    ETH_Init(); // 初始化以太网
    // 启动TCP客户端
    TCP_ClientStart();
    while(1){
        vTaskDelay(1000);
    }
}
