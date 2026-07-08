# esp32p4


## 安装步骤

### 安装vscode+ESP-IDF插件+离线安装包
esp-idf安装的是v5.4.4

### 克隆仓库

```
git clone https://github.com/waveshareteam/ESP32-P4-Platform.git
```

### 快速校验是否成功

```
cd ESP32-P4-Platform/examples/esp-idf/00_board_check  

cd D:\esp32\esp32p4\ESP32-P4-Platform\examples\esp-idf\00_board_check
idf.py set-target esp32p4  
idf.py build  
idf.py -p PORT flash monitor
```

ESP-IDF 示例运行前必须先构建并烧录。`idf.py build` 会生成可烧录固件；`idf.py -p PORT flash monitor` 会烧录固件并打开串口监视器。若修改了 `menuconfig` 或源码，需要重新构建后再烧录。

不同示例可能需要先配置引脚、Wi-Fi 凭据、Ethernet PHY、显示屏、摄像头或示例参数。运行这类示例前，请结合示例 README、板卡原理图和实际连接情况，在构建前执行：

```
idf.py menuconfig
```

