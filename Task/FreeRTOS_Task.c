#include "FreeRTOS_Task.h"
#include "TCP.h"

uint8_t buff[100];
uint16_t bufflen;

Carbon_Dioxide carbon = {
    .temperature = 36,
    .co2         = 3564,
    .humidity    = 60};


void TCP_Task(void *arg);
#define TCP_TASK_NAME     "TCP_Task"
#define TCP_TASK_STACK    256
#define TCP_TASK_PRIORITY 5
TaskHandle_t TCP_Task_Handler;


void TW51_Task(void *arg);
#define TW51_TASK_NAME     "TW51_Task"
#define TW51_TASK_STACK    256
#define TW51_TASK_PRIORITY 5
TaskHandle_t TW51_Task_Handler;


void FreeRTOS_Task_Start(void)
{
    // ��ʼ�����Ӳ��
    display_init();
    Voice_Init();
    ETH_Init();
    // ��������
    xTaskCreate(TCP_Task, TCP_TASK_NAME, TCP_TASK_STACK, NULL, TCP_TASK_PRIORITY, &TCP_Task_Handler);
    xTaskCreate(TW51_Task, TW51_TASK_NAME, TW51_TASK_STACK, NULL, TW51_TASK_PRIORITY, &TW51_Task_Handler);
    // ����������
    vTaskStartScheduler();
}

void TCP_Task(void *arg)
{
    printf("Client_Task\r\n");
    TCP_ClientStart();
    while (1) {
        
        TCP_SendData("hello world\r\n",13);
        char buff[50];
        sprintf(buff,"temperature:%d\r\nco2:%d\r\nhumidity:%d\r\n",carbon.temperature,carbon.co2,carbon.humidity);
        TCP_SendData((uint8_t*)buff,strlen(buff));
        vTaskDelay(10000);
    }
}


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
