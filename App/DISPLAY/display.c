#include "display.h"

void display_init(void)
{
    OLED_Init();
    OLED_Clear();
    OLED_ShowStr(0, 0, "  CO2_gateway");
    OLED_ShowStr(0, 1, " Welcome to use");
    OLED_ShowStr(0, 2, " up up stady!");
    OLED_ShowStr(0, 3, " day day up!");
}

void display_temperature(Carbon_Dioxide carbon)
{
    OLED_Clear();
    OLED_ShowStr(0, 0, "  CO2_gateway");
    OLED_ShowStr(0, 1, " temperature:");
    OLED_ShowStr(0, 2, " ");
    OLED_ShowNum(1, 2, carbon.temperature);
    int count = 0;
    while (carbon.temperature != 0) {
        carbon.temperature /= 10;
        count++;
    }
    OLED_ShowStr(count+1, 2, "^C");
}

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
