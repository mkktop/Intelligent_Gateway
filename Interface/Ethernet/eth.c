#include "eth.h"

// 全局变量，定义MAC地址、IP地址、子网掩码、网关地址
uint8_t mac[6]     = {110, 126, 130, 140, 150, 37};
uint8_t ip[4]      = {192, 168, 34, 137};
uint8_t submask[4] = {255, 255, 255, 0};
uint8_t gateway[4] = {192, 168, 34, 1};

void ETH_Init(void)
{
    // 1. 初始化SPI2
    MX_SPI2_Init();

    // 2. 注册函数
    user_reg_func();

    // 3. 复位，保持500us以上
    ETH_Reset();

    // 4. 设置物理地址（MAC）
    ETH_SetMac(mac);

    // 5. 设置IP地址（以及子网掩码和网关）
    ETH_SetIP(ip);
}

void ETH_Reset(void)
{
    // 1. 复位引脚
    // 先拉低最少800us
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_RESET);
    vTaskDelay(1);
    // 再拉高
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET);
    printf("以太网W5500复位完成!\r\n");
}

void ETH_SetMac(uint8_t mac[])
{
    printf("开始设置 MAC 地址...\n");
    // 以调库的方式进行寄存器设置
    setSHAR(mac);
    printf("MAC 地址设置完成！ %X.%X.%X.%X.%X.%X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void ETH_SetIP(uint8_t ip[])
{
    printf("开始设置 IP 地址...\n");
    // 以调库的方式进行寄存器设置 IP
    setSIPR(ip);
    printf("IP 地址设置完成！ %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
    // 设置子网掩码
    setSUBR(submask);
    // 设置网关
    setGAR(gateway);
}
