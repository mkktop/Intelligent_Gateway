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
    // ��ʼ�����Ӳ��

    // ��������

    // ����������
    vTaskStartScheduler();
}

void TCP_Task(void *arg)
{
    ETH_Init(); // ��ʼ����̫��
    // ����TCP�ͻ���
    TCP_ClientStart();
    while(1){
        vTaskDelay(1000);
    }
}
