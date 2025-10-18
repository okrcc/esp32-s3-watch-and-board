#include "AllInclude.h"

void StartCheck()
{
    int8_t check_right = 0;
    Serial.println("启动自检, 包括信息设备以及键盘等");
    Serial.printf("Flash 大小: %d MB\n", spi_flash_get_chip_size() / (1024 * 1024));
    Serial.printf("PSRAM 大小: %d MB\n", esp_spiram_get_size() / (1024 * 1024));
    uint8_t mac[6];
    esp_efuse_mac_get_default(mac);
    Serial.printf("MAC 地址: %02X:%02X:%02X:%02X:%02X:%02X\n",
                    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf("键盘将在SDA:%d SCL:%d 上面I2C接入开发板\n", kbSDA, kbSCL);
    Serial.printf("请输入以下自检码实现自检: %s\n", check_code);
    if (check_right == 0)
    {
        String inputcode = Getinput_blocking(); // 本部分需要使用非阻塞输入或者直跳激活, 目前使用阻塞方式代替, 但是需要适配无键盘的开启模式
        inputcode.trim();
        if (inputcode.indexOf(check_code) != -1)
        {
            Serial.println("键盘验证通过");
        }
        else
        {
            Serial.println("设备验证不通过, 键盘是操作模式必要设备, 无键盘将使用自动化模式");
            check_right = 1;
            return;
        }
    }

    Serial.println("自检完成, 激活使用");
}