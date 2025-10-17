#include "AllInclude.h"

String Getinput_blocking(bool display)
{
    String inputString = "";
    bool stringComplete = false;

    while (!stringComplete)
    {
        if (Wire.requestFrom(kbAddress, 1) > 0)
        {
            while (Wire.available())
            {
                char getone = Wire.read();

                // 处理退格键
                if (getone == 0x08)
                {
                    if (inputString.length() > 0)
                    {
                        inputString.remove(inputString.length() - 1);
                        if (display)
                            Serial.print("\b \b");
                    }
                    continue;
                }

                // 处理正常字符
                if (getone != '\r' && getone != 0x00)
                {
                    inputString += getone;
                    if (display)
                        Serial.print(getone);
                }

                // 处理回车键
                if (getone == '\r')
                {
                    stringComplete = true;
                    if (display)
                        Serial.println();
                }
            }
        }
        delay(10);
    }
    return inputString;
}
