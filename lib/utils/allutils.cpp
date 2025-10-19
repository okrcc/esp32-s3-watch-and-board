#include "AllInclude.h"

bool testForShort(int pinOutput, int pinInput)
{
    pinMode(pinOutput, OUTPUT);
    pinMode(pinInput, INPUT_PULLUP); // 启用内部上拉电阻

    // 测试场景1: 输出高电平，读取输入
    digitalWrite(pinOutput, HIGH);
    delayMicroseconds(10); // 短暂延时确保电平稳定
    int valueHigh = digitalRead(pinInput);

    // 测试场景2: 输出低电平，读取输入
    digitalWrite(pinOutput, LOW);
    delayMicroseconds(10);
    int valueLow = digitalRead(pinInput);
    return (valueHigh == HIGH && valueLow == LOW ) ? true : false;
}

void Clearscreen(){ // 本段需要实现串口输出清屏以及屏幕清屏功能
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");// 面向结果编程.jpg
    // 屏幕清屏功能保留
}

void getkv(){
    String key = Getinput_blocking();
    String value = preferences.getString(key.c_str(), "无值");
    Serial.println(value);
}

void setkv(){
    String key = Getinput_blocking();
    String value = Getinput_blocking();
    preferences.putString(key.c_str(), value);
}