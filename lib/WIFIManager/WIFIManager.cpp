#include "AllInclude.h"

// 连接到指定网络的函数
void connectToNetwork(int networkIndex) // 这个函数由deepseek编写,
{
    String ssid = WiFi.SSID(networkIndex);
    int32_t rssi = WiFi.RSSI(networkIndex);

    Serial.printf("尝试连接到: %s (信号强度: %ddBm)\n", ssid.c_str(), rssi);
    Serial.print("请输入密码（如为开放网络直接按回车）: ");

    String password = Getinput_blocking();
    password.trim();

    // 开始连接[2](@ref)
    WiFi.begin(ssid.c_str(), password.c_str());

    Serial.print("连接中");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\n连接成功！");
        Serial.print("IP地址: ");
        Serial.println(WiFi.localIP()); // 获取本地IP地址[1](@ref)
    }
    else
    {
        Serial.println("\n连接失败，请检查密码或网络状态");
        WiFi.disconnect(); // 断开连接[2](@ref)
    }
}
// 扫描网络并处理交互的函数
void interactiveScan() // 此函数由deepseek编写
{
    Serial.println("开始扫描WiFi网络...（输入任意两个字符即可立即停止扫描）");

    // 设置为STA模式并断开当前连接以确保扫描准确性[2,5](@ref)
    // WiFi.mode(WIFI_STA); 臭ai不要改我设置啊
    WiFi.disconnect();
    delay(100);

    // 启动异步扫描[3](@ref)
    int16_t scanResult = WiFi.scanNetworks(/*async*/ true, /*show_hidden*/ false);
    if (scanResult == -2)
    {
        Serial.println("扫描启动失败！");
        return;
    }

    String keyboardInput = "";
    bool scanInterrupted = false;
    bool scanCompleted = false;

    // 扫描监控循环
    while (!scanCompleted && !scanInterrupted)
    {
        int16_t scanStatus = WiFi.scanComplete();

        // 检查扫描状态[3](@ref)
        if (scanStatus == -1)
        {
            // 扫描仍在进行中，检查键盘输入
            if (Wire.requestFrom(kbAddress, 1) > 0)
            {
                while (Wire.available())
                {
                    char c = Wire.read();
                    if (c != '\r' && c != '\n' && c != 0x00)
                    {
                        keyboardInput += c;
                        Serial.print("*"); // 回显输入，但不显示具体字符
                    }

                    // 输入超过两个字符则中断扫描
                    if (keyboardInput.length() >= 2)
                    {
                        scanInterrupted = true;
                        Serial.println("\n扫描已被用户中断");
                        WiFi.scanDelete(); // 清理扫描结果[3](@ref)
                        break;
                    }
                }
            }
            delay(100); // 短暂延迟避免过于频繁的检查
        }
        else if (scanStatus >= 0)
        {
            // 扫描完成
            scanCompleted = true;
            Serial.println("\n扫描完成！");
        }
    }

    // 如果扫描完成（非中断），显示结果
    if (scanCompleted)
    {
        int networkCount = WiFi.scanComplete();

        if (networkCount == 0)
        {
            Serial.println("未发现任何WiFi网络");
        }
        else
        {
            Serial.printf("共发现 %d 个网络:\n", networkCount);
            Serial.println("================================");

            // 打印所有网络信息[5](@ref)
            for (int i = 0; i < networkCount; ++i)
            {
                Serial.printf("%2d: %-32s RSSI:%4ddBm",
                              i + 1,
                              WiFi.SSID(i).c_str(),
                              WiFi.RSSI(i));

                // 显示加密状态[5](@ref)
                if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
                {
                    Serial.print(" [开放]");
                }
                else
                {
                    Serial.print(" [加密]");
                }
                Serial.println();
            }
            Serial.println("================================");

            // 提供联网选择
            Serial.println("\n请选择操作:");
            Serial.println("1. 输入网络编号进行连接");
            Serial.println("2. 输入 0 返回主菜单");
            Serial.print("您的选择: ");

            String choice = Getinput_blocking();
            choice.trim();

            if (choice.toInt() > 0 && choice.toInt() <= networkCount)
            {
                int selectedIndex = choice.toInt() - 1;
                connectToNetwork(selectedIndex);
            }
            else if (choice == "0")
            {
                Serial.println("返回主菜单");
            }
            else
            {
                Serial.println("无效选择，返回主菜单");
            }
        }

        // 清理扫描结果[3](@ref)
        WiFi.scanDelete();
    }
}
