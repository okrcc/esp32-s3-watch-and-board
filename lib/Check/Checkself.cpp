#include "AllInclude.h"

void StartCheck()
{
    // 检测直跳激活, 选择激活方式
    if (testForShort(12, 13) == true)
    {
        device_run_state = AUTO_RUN;
        Serial.println("\nGPIO12与GPIO13短接通过, 设备默认自动运行, 将会以flash中auto_run文件作为运行依据, 键盘将作辅助运行工具");
        // 自动模式下, 设备不应当也不应该使用键盘控制和选择设备功能, 应该由功能主动请求键盘输入作为运行资料
        // 调度器应当首先选择主动调度, 而非被动调度模式
        return;
    }
    Serial.println("\n启动自检, 包括信息设备以及键盘等");
    Serial.printf("Flash 大小: %d MB\n", spi_flash_get_chip_size() / (1024 * 1024));
    Serial.printf("PSRAM 大小: %d MB\n", esp_spiram_get_size() / (1024 * 1024));
    uint8_t mac[6];
    esp_efuse_mac_get_default(mac);
    Serial.printf("MAC 地址: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf("键盘将在 SDA: %d SCL: %d 接入设备\n", kbSDA, kbSCL);
    check_right = 1;
    while (check_right)
    {
        Serial.printf("请输入以下自检码实现自检: %s\n", check_code);
        String inputcode = Getinput_blocking();
        inputcode.trim();
        if (inputcode.indexOf(check_code) != -1)
        {
            Serial.println("键盘验证通过");
            check_right = 0;
        }
        else
        {
            Serial.println("设备被动性运行验证不通过, 键盘是交互模式必要设备, 无键盘或者错误返回值将无法被动调度, 请重新输入以确保功能完善");
        }
    }
    Serial.println("自检完成, 激活使用");
}
void DoubleCheck(){//未实现功能, 使用startcheck代替
    StartCheck();
};