#include "AllInclude.h"

Preferences preferences;

String check_code = "<Es";
String device_ssid = check_code;
String device_password = check_code;
String connect_ssid = check_code;
String connect_password = check_code;
operation_state device_run_state = PASSIVE_RUN; // 默认被动运行
int8_t check_right = -1;
int8_t channel = 2;
int8_t ssid_hidden = 0;
int8_t max_connection = 4;

void setup()
{
    preferences.begin("device_setting", false);
    Serial.begin(115200);
    Wire.begin(kbSDA, kbSCL); // SDA:4 SCL:5
    WiFi.mode(WIFI_AP_STA);   // 设置为AP+STA模式, 可能用不到AP或者STA, 但总之先开着
    WiFi.disconnect();        // 断开可能的连接
    WiFi.softAP(device_ssid.c_str(), device_password.c_str());
    WiFi.setSleep(false);
    StartCheck();
    if (device_run_state == AUTO_RUN)
    {
        AUTOScheduler();
    }
}

void loop()
{
    MainScheduler();
}