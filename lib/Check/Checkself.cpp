#include "AllInclude.h"

void StartCheck()
{
    Serial.println("启动自检, 包括信息设备以及键盘等");
    Serial.printf("Flash 大小: %d MB\n", spi_flash_get_chip_size() / (1024 * 1024));
    Serial.printf("PSRAM 大小: %d MB\n", esp_spiram_get_size() / (1024 * 1024));
    uint8_t mac[6];
    esp_efuse_mac_get_default(mac);
    Serial.printf("MAC 地址: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    ESP.getSdkVersion();
}