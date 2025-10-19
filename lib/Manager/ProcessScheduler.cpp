#include "AllInclude.h"

// 主调度, 由主程序调用, 用于运行分配所有功能, 包括阻塞与非阻塞的模块
void MainScheduler()
{
    Serial.println("主调度器接管, 负责管理所有调度");
    if (device_run_state == AUTO_RUN)
    {
        Serial.println("检测运行模式切换, 进入自动模式");
        AUTOScheduler();
    }
    // 以下列表包含调度所有需求内容
    String list[] = {
        "cle",
        "rst",
        "check",
        "wifi",
        "espnow"};
    Serial.println("调度列表:");
    for (int i = 0; i < sizeof(list) / sizeof(list[0]); i++)
    {
        Serial.println(list[i]);
    }
    for (int i = 0; i < sizeof(list) / sizeof(list[0]); i++)
    {
        if (list[i] == "cle")
        {
            Clearscreen();
        }
        else if (list[i] == "rst")
        {
            ESP.restart();
        }
        else if (list[i] == "check")
        {
            DoubleCheck();
        }
        else if (list[i] == "wifi")
        {
            WIFIScheduler();
        }
        else if (list[i] == "espnow")
        {
            ESPNOWScheduler();
        }
    }
}

void AUTOScheduler() // 自动模式调度, 使用auto_run作运行指定内容
{
    Serial.println("自动调度器接管, 负责管理所有调度");
}

void WIFIScheduler() // 向学习项目复用
{
    bool inWifiSetting = true;

    while (inWifiSetting)
    {
        Serial.println("\n=== WiFi设置菜单 ===");
        Serial.println("1. AP模式设置");
        Serial.println("2. STA模式设置");
        Serial.println("3. 返回主菜单");
        Serial.print("请选择操作 (1-3): ");

        String mode = Getinput_blocking();
        mode.trim();

        if (mode == "1")
        {
            // AP模式子菜单
            bool inAPMode = true;
            while (inAPMode)
            {
                Serial.println("\n--- AP模式设置 ---");
                Serial.println("1. 配置AP参数");
                Serial.println("2. 查看AP状态");
                Serial.println("3. 返回上一级");
                Serial.print("请选择操作 (1-3): ");

                String ap_mode = Getinput_blocking();
                ap_mode.trim();

                if (ap_mode == "1")
                {
                    // AP参数配置
                    Serial.print("请输入新的SSID(当前: " + ssid + "), 留空跳过: ");
                    String new_ssid = Getinput_blocking();
                    new_ssid.trim();
                    if (new_ssid.length() > 0)
                        ssid = new_ssid;

                    Serial.print("请输入新的密码(当前: " + password + "), 留空跳过: ");
                    String new_password = Getinput_blocking();
                    new_password.trim();
                    if (new_password.length() > 0)
                        password = new_password;

                    Serial.print("请输入新的信道(当前: " + String(channel) + "), 留空跳过: ");
                    String new_channel = Getinput_blocking();
                    new_channel.trim();
                    if (new_channel.length() > 0)
                        channel = new_channel.toInt();

                    Serial.print("是否隐藏SSID? (1=隐藏, 其他=显示), 留空默认隐藏: ");
                    String hidden_input = Getinput_blocking();
                    hidden_input.trim();
                    ssid_hidden = (hidden_input == "1") ? 1 : 0;

                    WiFi.softAP(ssid.c_str(), password.c_str(), channel, ssid_hidden, max_connection);
                    Serial.println("AP参数已更新并重启!");
                }
                else if (ap_mode == "2")
                {
                    // AP状态查询
                    Serial.println("\n--- AP状态信息 ---");
                    Serial.print("主机名: ");
                    Serial.println(WiFi.softAPgetHostname());
                    Serial.print("IP地址: ");
                    Serial.println(WiFi.softAPIP());
                    Serial.print("连接设备数: ");
                    Serial.println(WiFi.softAPgetStationNum());
                    Serial.print("MAC地址: ");
                    Serial.println(WiFi.softAPmacAddress());
                }
                else if (ap_mode == "3")
                {
                    inAPMode = false;
                }
                else
                {
                    Serial.println("无效选择，请重新输入!");
                }
            }
        }
        else if (mode == "2")
        {
            // STA模式子菜单
            bool inSTAMode = true;
            while (inSTAMode)
            {
                Serial.println("\n--- STA模式设置 ---");
                Serial.println("1. 扫描并连接网络");
                Serial.println("2. 查看当前连接状态");
                Serial.println("3. 断开当前连接");
                Serial.println("4. 返回上一级");
                Serial.print("请选择操作 (1-4): ");

                String sta_mode = Getinput_blocking();
                sta_mode.trim();

                if (sta_mode == "1")
                {
                    // 扫描并连接网络
                    interactiveScan();
                }
                else if (sta_mode == "2")
                {
                    // 查看当前连接状态
                    wl_status_t status = WiFi.status();
                    Serial.print("连接状态: ");
                    switch (status)
                    {
                    case WL_CONNECTED:
                        Serial.println("已连接");
                        Serial.print("SSID: ");
                        Serial.println(WiFi.SSID());
                        Serial.print("IP地址: ");
                        Serial.println(WiFi.localIP());
                        Serial.print("信号强度: ");
                        Serial.print(WiFi.RSSI());
                        Serial.println(" dBm");
                        break;
                    case WL_NO_SSID_AVAIL:
                        Serial.println("SSID不可用");
                        break;
                    case WL_CONNECT_FAILED:
                        Serial.println("连接失败");
                        break;
                    case WL_CONNECTION_LOST:
                        Serial.println("连接丢失");
                        break;
                    case WL_DISCONNECTED:
                        Serial.println("未连接");
                        break;
                    default:
                        Serial.println("未知状态");
                    }
                }
                else if (sta_mode == "3")
                {
                    // 断开连接
                    WiFi.disconnect();
                    Serial.println("已断开当前连接");
                }
                else if (sta_mode == "4")
                {
                    inSTAMode = false;
                }
                else
                {
                    Serial.println("无效选择，请重新输入!");
                }
            }
        }
        else if (mode == "3")
        {
            inWifiSetting = false;
            Serial.println("返回主菜单");
        }
        else
        {
            Serial.println("无效选择，请重新输入!");
        }
    }
}

void ESPNOWScheduler()
{
}