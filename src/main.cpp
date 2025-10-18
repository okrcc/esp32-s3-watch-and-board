#include "AllInclude.h"

String check_code = "<Es";
String ssid = check_code;
String password = check_code;

void setup(){
    Serial.begin(115200);
    Wire.begin(kbSDA,kbSCL); // SDA:4 SCL:5
    StartCheck();
}

void loop(){
    
}