#pragma once
#include "AllInclude.h"

#define kbSDA 4
#define kbSCL 5
#define kbAddress 0x5F
extern const uint8_t MAC[6];
extern String check_code;
extern String ssid;
extern String password;
extern int8_t check_right; // 此项为0则检测通过