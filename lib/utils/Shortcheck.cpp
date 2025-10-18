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