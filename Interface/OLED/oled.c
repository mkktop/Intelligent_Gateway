#include "oled.h"

void OLED_WriteData(uint8_t bytes[], uint8_t length)
{
    HAL_I2C_Mem_Write(&hi2c1, DEV_ADDR, DATA_MODE, I2C_MEMADD_SIZE_8BIT, bytes, length, 1000);
}

void OLED_WriteCmd(uint8_t bytes[], uint8_t length)
{
    HAL_I2C_Mem_Write(&hi2c1, DEV_ADDR, CMD_MODE, I2C_MEMADD_SIZE_8BIT, bytes, length, 1000);
}

// 屏幕初始化
void OLED_Init(void)
{
    uint8_t cmd_bytes[6];
    // 关闭屏幕
    cmd_bytes[0] = 0xAE;
    // 行重映射
    cmd_bytes[1] = 0xC8;
    // 列重映射
    cmd_bytes[2] = 0xA1;
    // 电荷泵
    cmd_bytes[3] = 0x8D;
    cmd_bytes[4] = 0x14;
    // 开启屏幕
    cmd_bytes[5] = 0xAF;
    OLED_WriteCmd(cmd_bytes, 6);
}

void OLED_Clear()
{
    uint8_t cmd_bytes[3];
    uint8_t data_bytes[1];
    data_bytes[0] = 0x00;
    uint8_t i, n;
    for (i = 0; i < 8; i++) {
        cmd_bytes[0] = 0xb0 + i;
        cmd_bytes[1] = 0x00;
        cmd_bytes[2] = 0x10;
        OLED_WriteCmd(cmd_bytes, 3);
        for (n = 0; n < 128; n++) {
            OLED_WriteData(data_bytes, 1);
        }
    }
}

