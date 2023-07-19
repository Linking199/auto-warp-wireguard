# 用处
不需要任何额外的依赖项，通过一次简单的双击，即可获得几近无限流量的wireguard配置文件，导入wireguard软件使用，实现vpn自由！

# 使用范围
适用于Windows 10、11系统

# 使用方法
## 使用方法1（自动生成新的warp+ key）
1. 直接双击运行 **“V1_一键生成wireguard配置文件.exe”**
2. 程序运行完之后，会产生wireguard_conf文件夹，里面的.conf文件可以直接导入wireguard使用  
所得到的配置文件是由随机克隆的warp+密钥得到的，因此每个人获得的配置文件都是独特的且一般有20~24Pb的warp流量  

## 使用方法2（由你自己提供warp+ key）
1. 打开命令提示符，cd到“V1_一键生成wireguard配置文件.exe”所在目录  
2. 运行代码：
> V1_一键生成wireguard配置文件.exe [your warp+ key]

例如：
> V1_一键生成wireguard配置文件.exe xxxx-xxxx-xxxxxx-xxx

3. 程序运行完之后，会产生wireguard_conf文件夹，里面的.conf文件可以直接导入wireguard使用
所得到的配置文件是由随机克隆的warp+密钥得到的，因此每个人获得的配置文件都是独特的且一般有20~24Pb的warp流量

# 声明
- lib\clone_key.exe 来源于项目https://github.com/totoroterror/warp-cloner  
- lib\wgcf_2.2.18_windows_amd64.exe 来源于项目https://github.com/ViRb3/wgcf  
- 此项目结合了上述两个项目，以及用于ip优选的脚本和自主编写的c项目，实现了全过程的自动化  
- 事实上，我是觉得看youtube博主们的教程去一步步操作难免枯燥无味且费时费力，所以将各路教程的内容集成并打包成这一项目  
- 在此声明，任何人可以使用此项目，二次开发时需标明来源项目https://github.com/Linking199/auto-warp-wireguard



# Uses
Without any additional dependencies, with a simple double click, you can get wireguard configuration files with nearly unlimited traffic, import wireguard software to use, and achieve vpn freedom!  

# Scope of use
It applies to Windows 10 and Windows 11  

# Usage
##Use Method 1 (automatically generate new warp+ key) 
1. Double-click the wireguard configuration file and run **"V1_一键生成wireguard配置文件.exe"**.
2. After the procedure is done, the wireguard_conf folder is generated. You can import the.conf file to the WireGuard  
The resulting profile is obtained by randomly cloning the warp+ key, so each person gets a unique profile and generally has 20 to 24 petabytes of warp traffic  

## To use Method 2 (warp+ key provided by yourself) 
1. Open the command prompt and go to the directory where v1_One-Click wireguard Configuration file. exe is located  
2. Run code: 
> V1_一键生成wireguard配置文件.exe [your warp+ key]

For example, 
> V1_一键生成wireguard配置文件.exe  xxxx-xxxx-xxxxxx-xxx  

3. After the procedure is done, the wireguard_conf folder is generated. You can import the.conf file to the WireGuard  
The resulting profile is obtained by randomly cloning the warp+ key, so each person gets a unique profile and generally has 20 to 24 petabytes of warp traffic  

# license
- Lib \ clone_key exe is derived from the project at https://github.com/totoroterror/warp-cloner  
- Lib \ wgcf_2. 2.18 _windows_amd64. Exe is derived from the project at https://github.com/ViRb3/wgcf  
- This project combines the above two projects, as well as the script for ip optimization and the self-written c project, to realize the automation of the whole process  
- In fact, I thought it would be tedious and time-consuming to follow the tutorials of youtube bloggers step by step, so I integrated and packaged the content of each tutorial into this project  
- In this statement, anyone can use this project, need to indicate the source when secondary development project at https://github.com/Linking199/auto-warp-wireguard
