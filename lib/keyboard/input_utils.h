#pragma once

String Getinput_blocking(bool display = true);
String Getinput_quick(bool display = true, int8_t end_char = 0x1B, const String &exit_word = ""); // 保留功能待实现

