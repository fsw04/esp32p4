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


## 创建工程

先选择esp-idf版本
![[Pasted image 20260710183850.png]]

点击adcanced,点击新项目向导

![[Pasted image 20260710183923.png]]

点击examples

点击esp32p4（这里是将上面仓库克隆后将esp32p4/ESP32-P4-Platform/examples/esp-idf复制到安装esp-idf的example案例下，例如\v5.4.4\esp-idf\examples，然后重命名esp-idf为esp32p4）

点击想要的案例(这里我选择03)

![[Pasted image 20260710184115.png]]

修改路径（代码保存的路径，我保存在esp32p4\code里面）

芯片选择esp32p4

Choose ESP-IDF Board 选择第一个  (ESP32-P4 chip (via builtin USB-JTAG))

端口我接的是COM23(需要预先安装驱动CH340，在设备管理器->端口查看，插拔usb观察端口变化，突然改变的就是连接芯片的端口)

![[Pasted image 20260710184019.png]]
![[Pasted image 20260710185245.png]]

## 打开工程

### 编译工程

1.可以通过esp-idf的命令栏点击构建
2.或者点击底下的图标
3.或者终端输入构建指令

```
cd ESP32-P4-Platform/examples/esp-idf/00_board_check 
idf.py set-target esp32p4  
idf.py build 
```

（构建，烧录，监控是一次性将三个步骤同时启动）

![[Pasted image 20260710185528.png]]
![[Pasted image 20260710185721.png]]

![[Pasted image 20260710190255.png]]
### 烧录工程

![[Pasted image 20260710190333.png]]

![[Pasted image 20260710190401.png]]

### 监控工程

![[Pasted image 20260710190448.png]]

**crtl+]** 退出，如果不退出，改端口不能再次烧录，不能另开监控


## 注意事项

### 1.如果编译不通过
可能是sdkconfig的问题，将其他sdkconfig删除只保留sdkconfig.defaults，重新编译生成sdkconfig

编译不通过原因可能是保留了之前的sdkconfig的配置导致的，只保留sdkconfig.defaults是保留默认的配置

