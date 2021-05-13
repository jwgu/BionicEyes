# BionicEyes
BinoSense系列产品SDK, 支持的使用模式及使用方法如下.
1. 远程连接使用模式
   1) 将仿生眼设备连接至网络，启动相应设备程序(对于III代默认自启动),以ubuntu 18.04举例：
      1. III代
         + `cd SDK_Path/bin`
         + `./evo_be_Device_1804`
         + `./evo_be_Device_Service_1804`(另一个终端)
      2. IV&V代
         + `cd SDK_Path/bin`
         + `./evo_be_Device_5_1804`
         + `./evo_be_Device_Service_1804`(另一个终端)
   2) 将终端计算平台连接同一网络，直接运行SDK相应功能程序或者链接SDK相应库启动相应程序（需事先配置相关运行环境，如下文描述）
      
2. 直连模式(目前仅V5版本支持)
    1) 将仿生眼设备连接自有设备，直接运行SDK相应功能程序或者链接SDK相应库启动相应程序（需事先配置相关运行环境，如下文描述）
    2) 直连模式仍然支持外部计算平台通过网络连接自有设备，如果需要同时开启上述远程连接使用模式，需在仿生眼直连自有设备中启动`./evo_be_Device_Service_1804`

---
## 仿生眼远程连接模式内部 & 直连设备环境配置
1) 安装若干依赖库
   `sudo apt-get install build-essential git libgtk2.0-dev libhdf5-dev pkg-config libavcodec-dev libdc1394-22-dev libavformat-dev libswscale-dev libtbb-dev liblapacke-dev libvtk6-dev libatlas-base-dev`
2) `sudo mkdir /usr/Evo_BionicEyes`
3) `sudo chmod 777 /usr/Evo_BionicEyes/`
4) 将设备配置文件拷贝至/usr/Evo_BionicEyes路径下
5) `cd ~/workspace`
6) `git clone https://github.com/BinoSense/BionicEyes`
7) 下载dependencies文件夹至BionicEyes目录下
8) `cd ~/workspace/BionicEyes`
9) 如果拥有核心代码模块权限，可clone相应模块置于src路径下
10) `mkdir build`
11) `cd build`
12) `cmake ..`
13) `make -j8`
14) 所有设备可执行文件位于`~/workspace/BionicEyes/bin/`下


## 仿生眼远端首次使用SDK安装步骤
### 一、若干准备工作：
1) 安装若干依赖库
   `sudo apt-get install build-essential git libgtk2.0-dev libhdf5-dev pkg-config libavcodec-dev libdc1394-22-dev libavformat-dev libswscale-dev libtbb-dev liblapacke-dev libvtk6-dev libatlas-base-dev`
2) `sudo mkdir /usr/Evo_BionicEyes`
3) `sudo chmod 777 /usr/Evo_BionicEyes/`
4) 如果后续需要使用SDK中图像处理相关模块功能,可能需要自行安装配置安装CUDA 11.1

### 二、开始：
1) 进入你的workspace文件路径下,`cd ~/workspace`
2) `git clone https://github.com/BinoSense/BionicEyes`
3) 下载dependencies文件夹(http://binosense.ilooktech.com/downloads/BinoSense_SDK_DEP.zip, 里面有dependencies和resource两个文件）至BionicEyes目录下
4) `cd ~/workspace/BionicEyes`
5)  如果拥有核心代码模块权限，可clone相应模块置于src路径下
6) `mkdir build`
7) `cd build`
8) `cmake ..`
9) 如果需要重新编译源码，则`make -j8`
10) 所有设备可执行文件位于`~/workspace/BionicEyes/bin/`下

### 三、更新：
1) 进入你的仿生眼工程路径下,`cd ~/workspace/BionicEyes`
2) 使用git更新BionicEyes工程,`git pull`
3) 如果有核心源码权限，可更新相应核心源码工程
4) `cd build`
5) `cmake -DBE_LIB_UPDATE=ON -DBE_INCLUDE_UPDATE=ON -DBE_DEP_UPDATE=ON ..`
6) `make -j8`
6) 可执行文件位于`~/workspace/BionicEyes/bin/`下

---
## 注意!!!
在仿生眼内部设备首次装载工程正式使用前：
###对于第III代仿生眼
1) 需要安装basler相机驱动, https://www.baslerweb.com/fp-1589378344/media/downloads/software/pylon_software/pylon_6.1.1.19861-deb0_amd64.deb
2) `sudo /opt/pylon/share/pylon/setup-usb.sh`
3) `sudo gedit /etc/security/limits.conf`
4) 在文件末尾添加“*    hard    nofile    4096”
5) `cat /sys/module/usbcore/parameters/usbfs_memory_mb`
    确认返回值是不是1000，如果不是可能导致采集图像出现卡顿等异常,请依次执行以下步骤：
1) `sudo /etc/default/grub`
2) 修改GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"
   改成：GRUB_CMDLINE_LINUX_DEFAULT="quiet splash usbcore.usbfs_memory_mb=1000"
3) `sudo update-grub`

###对于第IV & V代仿生眼
需要查看https://github.com/TheImagingSource/tiscamera
根据说明安装相应相机驱动并完成设置才可使用仿生眼



