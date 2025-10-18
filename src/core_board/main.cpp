#include "AllInclude.h"

String check_code = "<Es";
String ssid = check_code;
String password = check_code;
operation_state device_run_state = PASSIVE_RUN;//默认被动运行
int8_t check_right = -1;

void setup(){
    Serial.begin(115200);
    Wire.begin(kbSDA,kbSCL); // SDA:4 SCL:5
    StartCheck();
}

void loop(){
    //MainScheduler();
}