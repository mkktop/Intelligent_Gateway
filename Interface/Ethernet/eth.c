#include "eth.h"

// ȫ�ֱ���������MAC��ַ��IP��ַ���������롢���ص�ַ
uint8_t mac[6]     = {110, 126, 130, 140, 150, 37};
uint8_t ip[4]      = {192, 168, 34, 137};
uint8_t submask[4] = {255, 255, 255, 0};
uint8_t gateway[4] = {192, 168, 34, 1};

void ETH_Init(void)
{
    // 1. ��ʼ��SPI2
    MX_SPI2_Init();

    // 2. ע�ắ��
    user_reg_func();

    // 3. ��λ������500us����
    ETH_Reset();

    // 4. ���������ַ��MAC��
    ETH_SetMac(mac);

    // 5. ����IP��ַ���Լ�������������أ�
    ETH_SetIP(ip);
}

void ETH_Reset(void)
{
    // 1. ��λ����
    // ����������800us
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_RESET);
    vTaskDelay(1);
    // ������
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET);
    printf("��̫��W5500��λ���!\r\n");
}

void ETH_SetMac(uint8_t mac[])
{
    printf("��ʼ���� MAC ��ַ...\n");
    // �Ե���ķ�ʽ���мĴ�������
    setSHAR(mac);
    printf("MAC ��ַ������ɣ� %X.%X.%X.%X.%X.%X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void ETH_SetIP(uint8_t ip[])
{
    printf("��ʼ���� IP ��ַ...\n");
    // �Ե���ķ�ʽ���мĴ������� IP
    setSIPR(ip);
    printf("IP ��ַ������ɣ� %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
    // ������������
    setSUBR(submask);
    // ��������
    setGAR(gateway);
}
