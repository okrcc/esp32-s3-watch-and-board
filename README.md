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

## 项目结构
- `src/`：存放主要的源代码文件
  - `core_board/`：核心板（ESP32-S3-WROOM-1-N16R8）相关代码
  - `watch_board/`：微雪 ESP32-S3 手表相关代码
- `lib/`：存放自定义库文件
  - `Major/`：重要功能模块, 全局变量以及单文件头文件
  - `Manager/`：管理器模块, 包括状态管理, 调度器
  - `KBManager/`：键盘管理模块, 负责与 M5Stack Unit CardKB 通信
  - `Check`：检查模块, 包括启动检测以及复检
  - `utils/`：实用工具函数, 如自跳等

## 硬件清单

- 微雪 ESP32-S3 开发手表（带触摸与 AMOLED 屏幕）
  - 产品资料参考：[Waveshare — ESP32-S3 Touch AMOLED 2.06](https://www.waveshare.net/wiki/ESP32-S3-Touch-AMOLED-2.06)
- ESP32-S3-WROOM-1-N16R8 核心板
  - 产品资料参考：[ESP32-S3-WROOM-1-N16R8 Datasheet](https://item.szlcsc.com/datasheet/ESP32-S3-WROOM-1U-N16R8/3522416.html?lcsc_vid=T1ALVFBSFANYVlEHRgdWBgUARlIMXgADR1cKU11TEVAxVlNQR1dcX1xSRlRZVDtW)
- M5Stack Unit CardKB v1.1
  - 用途：作为外设键盘，通过 I2C 接口与 ESP32-S3 通信，用于输入字符或控制命令。
  - 产品资料参考：[M5Stack — Unit CardKB v1.1](https://docs.m5stack.com/en/unit/cardkb)


## 快速开始

1. 在 VSCode 中打开本仓库目录（确保已安装 PlatformIO 插件）
2. 连接 ESP32-S3 开发板至电脑，确保驱动已正确安装
3. 在 VSCode 中使用 PlatformIO 打开串口监视器，波特率设置为 115200
4. 编写或导入 Arduino 程序，选择对应的开发板和串口
5. 上传程序至开发板，观察串口输出信息
6. 断开串口监视器，重启开发板，运行程序

## 参与贡献

欢迎任何形式的贡献，包括但不限于：

- 提交代码
- 提交文档
- 提交翻译
- 提交问题与建议

请通过 Fork 本仓库，提交 Pull Request 参与贡献。
或者向我的[邮箱](3501132@qq.com)发送私信交流。

## 许可证

本项目采用 MIT 许可证，详情请参见根目录下的 `LICENSE` 文件。
