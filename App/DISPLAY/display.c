//显示模块，用于向OLED屏幕显示数据
#include "display.h"

/**
 * @brief 显示屏初始化函数
 * 
 */
void display_init(void)
{
    OLED_Init();
    OLED_Clear();
    OLED_ShowStr(0, 0, "  CO2_gateway");
    OLED_ShowStr(0, 1, " Welcome to use");
    OLED_ShowStr(0, 2, " up up stady!");
    OLED_ShowStr(0, 3, " day day up!");
}

/**
 * @brief 显示温度
 * 
 * @param carbon 二氧化碳传感器信息结构体
 */
void display_temperature(Carbon_Dioxide carbon)
{
    OLED_Clear();
    OLED_ShowStr(0, 0, "  CO2_gateway");
    OLED_ShowStr(0, 1, " temperature:");
    OLED_ShowStr(0, 2, " ");
    OLED_ShowNum(1, 2, carbon.temperature);
    //获取数值长度
    int count = 0;
    while (carbon.temperature != 0) {
        carbon.temperature /= 10;
        count++;
    }
    OLED_ShowStr(count+1, 2, "^C");
}

/**
 * @brief 显示湿度
 * 
 * @param carbon 二氧化碳传感器信息结构体
 */
void display_humidity(Carbon_Dioxide carbon)
{
    OLED_Clear();
    OLED_ShowStr(0, 0, "  CO2_gateway");
    OLED_ShowStr(0, 1, " humidity:");
    OLED_ShowStr(0, 2, " ");
    OLED_ShowNum(1, 2, carbon.humidity);
    int count = 0;
    while (carbon.humidity != 0) {
        carbon.humidity /= 10;
        count++;
    }
    OLED_ShowStr(count+1, 2, " %RH");
}

/**
 * @brief 显示二氧化碳
 * 
 * @param carbon 二氧化碳传感器信息结构体
 */
void display_co2(Carbon_Dioxide carbon)
{
    OLED_Clear();
    OLED_ShowStr(0, 0, "  CO2_gateway");
    OLED_ShowStr(0, 1, " co2:");
    OLED_ShowStr(0, 2, " ");
    OLED_ShowNum(1, 2, carbon.co2);
    int count = 0;
    while (carbon.co2 != 0) {
        carbon.co2 /= 10;
        count++;
    }
    OLED_ShowStr(count+1, 2, " PPM");
}

/**
 * @brief 显示所有数据，综合数据面板
 * 
 * @param carbon 二氧化碳传感器信息结构体
 */
void display_all(Carbon_Dioxide carbon){
    OLED_Clear();
    OLED_ShowStr(0, 0, "  CO2_gateway");
    OLED_ShowStr(0, 1, "co2:");
    OLED_ShowNum(4, 1, carbon.co2);
    int count = 0;
    while (carbon.co2 != 0) {
        carbon.co2 /= 10;
        count++;
    }
    OLED_ShowStr(count+4, 1, " PPM");

    OLED_ShowStr(0, 2, "tem:");
    OLED_ShowNum(4, 2, carbon.temperature);
    count = 0;
    while (carbon.temperature != 0) {
        carbon.temperature /= 10;
        count++;
    }
    OLED_ShowStr(count+4, 2, "^C");

    OLED_ShowStr(0, 3, "hum:");
    OLED_ShowNum(4, 3, carbon.humidity);
    count = 0;
    while (carbon.humidity != 0) {
        carbon.humidity /= 10;
        count++;
    }
    OLED_ShowStr(count+4, 3, "%RH");
}
