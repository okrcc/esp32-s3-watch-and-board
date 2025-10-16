# ESP32-S3 协同设备开发项目

本仓库用于学习与实践基于 ESP32-S3 的协同设备开发。目标是通过一个“微雪手表”（显示端）和一个 ESP32-S3 核心板（采集/外设端）之间的无线通信（蓝牙、WiFi、ESP-NOW 等），实现数据采集、传输与显示的端到端功能和开发流程掌握。

## 项目开发想法

- 手表显示端（微雪 ESP32-S3 手表）：用于接收核心板发送的数据并在屏幕上展示；也可以作为主控从外设采集并显示数据。
- 核心板（ESP32-S3-WROOM-1-N16R8）：用于连接传感器或外设，采集数据并通过蓝牙、WiFi 或 ESP-NOW 发送给手表；也可以作为外设模块为手表提供传感器数据和扩展接口。
- 支持的通信方式：Bluetooth（BLE）、WiFi（TCP/UDP/HTTP/MQTT）、ESP-NOW。可根据学习目标选择任意一种或多种进行实现与对比。

该项目既可用于演示多设备协作，也适合作为个人学习 ESP32-S3 SDK、Arduino 框架和无线通信协议的练手仓库。

## 开发环境

- **编辑器**：Visual Studio Code
- **构建系统**：PlatformIO
- **开发框架**：Arduino（在 PlatformIO 中使用相应的板子与框架配置）

建议安装插件和工具：

- PlatformIO IDE（VSCode 插件）
- 串口调试终端（VSCode 内置或 PlatformIO Serial Monitor）

## 硬件清单

- 微雪 ESP32-S3 开发手表（带触摸与 AMOLED 屏幕）
  - 产品资料参考：[Waveshare — ESP32-S3 Touch AMOLED 2.06](https://www.waveshare.net/wiki/ESP32-S3-Touch-AMOLED-2.06)
- ESP32-S3-WROOM-1-N16R8 核心板
  - 产品资料参考：[ESP32-S3-WROOM-1-N16R8 Datasheet](https://item.szlcsc.com/datasheet/ESP32-S3-WROOM-1U-N16R8/3522416.html?lcsc_vid=T1ALVFBSFANYVlEHRgdWBgUARlIMXgADR1cKU11TEVAxVlNQR1dcX1xSRlRZVDtW)
- M5Stack Unit CardKB v1.1
  - 用途：作为外设键盘，通过 I2C 接口与 ESP32-S3 通信，用于输入字符或控制命令。
  - 产品资料参考：[M5Stack — Unit CardKB v1.1](https://docs.m5stack.com/en/unit/cardkb)

（可选）其他外设：

- 温湿度传感器
- 加速度计
- 外部电源模块
- 按键
- I2C/SPI 传感器

## 快速开始

1. 在 VSCode 中打开本仓库目录（确保已安装 PlatformIO 插件）
2. 连接 ESP32-S3 开发板至电脑，确保驱动已正确安装
3. 在 VSCode 中使用 PlatformIO 打开串口监视器，波特率设置为 115200
4. 编写或导入 Arduino 程序，选择对应的开发板和串口
5. 上传程序至 ESP32-S3 开发板，观察串口输出信息
6. 断开串口监视器，重启开发板，运行程序

## 参考资料

- [ESP32-S3 官方文档](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/index.html)
- [Arduino 官方文档](https://www.arduino.cc/reference/en/)
- [PlatformIO 文档](https://docs.platformio.org/en/latest/)
- [蓝牙基础知识](https://www.bluetooth.com/bluetooth-resources/bluetooth-101/)
- [WiFi 基础知识](https://www.wi-fi.org/discover-wi-fi/wi-fi-101)
- [ESP-NOW 协议介绍](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/wifi/esp_now.html)

## 参与贡献

欢迎任何形式的贡献，包括但不限于：

- 提交代码
- 提交文档
- 提交翻译
- 提交问题与建议

请通过 Fork 本仓库，提交 Pull Request 参与贡献。

## 许可证

本项目采用 MIT 许可证，详情请参见根目录下的 `LICENSE` 文件。
