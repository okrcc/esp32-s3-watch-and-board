#pragma once
#include "AllInclude.h"

#define kbSDA 4
#define kbSCL 5
#define kbAddress 0x5F
extern const uint8_t MAC[6];
extern String check_code;
extern int8_t check_right; // 此项为0则检测通过 1则键盘不通过(注意自跳)
extern int8_t channel;
extern int8_t ssid_hidden;
extern int8_t max_connection;
extern Preferences preferences;
extern String device_ssid;
extern String device_password;
extern String connect_ssid;
extern String connect_password;

enum operation_state
{
    AUTO_RUN,
    PASSIVE_RUN
};

extern operation_state device_run_state;