#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <windows.h>

#define ONE_LINE_WARD_MAX 128

#define DIR_TOOL "ip_tool"
#define FILE_TOML "wgcf-account.toml"
#define FILE_CONF "wgcf-profile.conf"
#define TXT_RESULT "result.txt"
#define EXE_GET_KEY_V2 DIR_FOR_EXE "get-key_2.0.exe"
#define EXE_CLONE_KEY DIR_FOR_EXE "clone_key.exe"
#define EXE_WGCF DIR_FOR_EXE "wgcf_2.2.18_windows_amd64.exe"
#define EXE_GEN_CONF DIR_FOR_EXE "gen_conf.exe"
#define BAT_IP_GET "ip_get.bat"
#define EG_KEY "R673wE9z-G910OPC2-0r92Sk4v"
#define DIR_FOR_EXE "lib\\"

#define VARIEBLE_NAME(x) #x



char *Get_result(const char command[]);
void Wgcf_work(char *key);
char *For_clone_key();
char *Joint_str(int count, ...);
void Change_content(const char *file_name,const char *feature,const char *new_cont);
void For_RESULT_SVC(const char *film_name);
void remove_directory(const char *path);
void move_conf_files();