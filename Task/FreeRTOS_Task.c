//FreeRTOS������򣨺��ģ�
#include "FreeRTOS_Task.h"

uint8_t buff[100];
uint16_t bufflen;

Carbon_Dioxide carbon = {
    .temperature = 36,
    .co2         = 3500,
    .humidity    = 60};

//TCP����
void TCP_Task(void *arg);
#define TCP_TASK_NAME     "TCP_Task"
#define TCP_TASK_STACK    256
#define TCP_TASK_PRIORITY 5
TaskHandle_t TCP_Task_Handler;
//����51����
void TW51_Task(void *arg);
#define TW51_TASK_NAME     "TW51_Task"
#define TW51_TASK_STACK    256
#define TW51_TASK_PRIORITY 5
TaskHandle_t TW51_Task_Handler;
//����ɨ������
void KEY_Task(void *arg);
#define KEY_TASK_NAME     "KEY_Task"
#define KEY_TASK_STACK    100
#define KEY_TASK_PRIORITY 5
TaskHandle_t KEY_Task_Handler;
//��ȡ����������
void Read_Task(void *arg);
#define READ_TASK_NAME     "Read_Task"
#define READ_TASK_STACK    128
#define READ_TASK_PRIORITY 5
TaskHandle_t Read_Task_Handler;

//����ϵͳ��ʼ��
void FreeRTOS_Task_Start(void)
{
    // ��ʼ�����Ӳ��
    display_init();
    Voice_Init();
    ETH_Init();
    // ��������
    xTaskCreate(TCP_Task, TCP_TASK_NAME, TCP_TASK_STACK, NULL, TCP_TASK_PRIORITY, &TCP_Task_Handler);
    xTaskCreate(TW51_Task, TW51_TASK_NAME, TW51_TASK_STACK, NULL, TW51_TASK_PRIORITY, &TW51_Task_Handler);
    xTaskCreate(KEY_Task, KEY_TASK_NAME, KEY_TASK_STACK, NULL, KEY_TASK_PRIORITY, &KEY_Task_Handler);
    xTaskCreate(Read_Task, READ_TASK_NAME, READ_TASK_STACK, NULL, READ_TASK_PRIORITY, &Read_Task_Handler);
    // ����������
    vTaskStartScheduler();
}

void TCP_Task(void *arg)
{
    printf("TCP_Task\r\n");
    TCP_ClientStart();
    while (1) {
        TCP_SendData("hello world\r\n", 13);
        char buff[50];
        //����TCP���ʹ��������ݵ����������
        sprintf(buff, "temperature:%d\r\nco2:%d\r\nhumidity:%d\r\n", carbon.temperature, carbon.co2, carbon.humidity);
        TCP_SendData((uint8_t *)buff, strlen(buff));
        vTaskDelay(10000);
    }
}

void TW51_Task(void *arg)
{
    while (1) {
        TW51_ReadData(buff, &bufflen);
        if (bufflen > 0) {
            printf("%s\n", buff);
            ///aaa�����ȡ�¶ȣ�bbb�����ȡco2��ccc�����ȡʪ��
            if (strcmp((char *)buff, "bbb") == 0) {
                Voice_Send_temperature(carbon);
                display_temperature(carbon);
            } else if (strcmp((char *)buff, "aaa") == 0) {
                Voice_Send_co2(carbon);
                display_co2(carbon);
            } else if (strcmp((char *)buff, "ccc") == 0) {
                Voice_Send_humidity(carbon);
                display_humidity(carbon);
            }
        }
    }
}

void KEY_Task(void *arg)
{
    key_init();
    vTaskDelay(1000);
    while (1) {
        uint8_t key = key_GetKey();
        switch (key) {
            case 1:
                display_temperature(carbon);
                break;
            case 2:
                display_co2(carbon);
                break;
            case 3:
                display_humidity(carbon);
                break;
            case 4:
                display_all(carbon);
                break;
            case 5:
                LED1_Toggle();
                LED2_Toggle();
                break;
            default:
                break;
        }
        vTaskDelay(100);
    }
}

void Read_Task(void *arg)
{
    Modbus_Init();
    while (1)
    {
        Modbus_ReadCO2(&carbon);
        if (carbon.co2 >3000)
        {   
            //������̼Ũ�ȸ�������
            LED2_ON();
            LED1_DOWN();
        }else if (carbon.co2 >2000)
        {
            //������̼Ũ���е��̵���
            LED1_ON();
            LED2_DOWN();
        }else{
            //������̼Ũ�ȵͣ���ȫ��
            LED1_DOWN();
            LED2_DOWN();
        }       
        vTaskDelay(10000);
    }
    
}
