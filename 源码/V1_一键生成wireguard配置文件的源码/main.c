#include "header.h"

int main(int argc, char **argv) {//�����ⲿ������Ϊwarp+����Կ
	char *key;

	puts("Initialize...\n");
	if (argc == 1)
	//	while ((key = Get_result(EXE_GET_KEY_V2" 1")) == NULL);
		while ((key=For_clone_key()) == NULL);	
	else
		key = argv[1];

	Wgcf_work(key);

	free(key);

	system("cd ip_tool&&ip_get.bat 1 >nul");
	system("move ip_tool\\result.csv . >nul");
	For_RESULT_SVC("result.csv");//���result.txt
	system("type nul | "EXE_GEN_CONF" >nul");
	struct stat dir_stat;
    if (stat("warp_conf", &dir_stat) == 0 && S_ISDIR(dir_stat.st_mode)) {
        // ���ڣ���ɾ�����е� "warp_conf" �ļ��м�������
        remove_directory("warp_conf");
    }
	system("mkdir warp_conf"">nul");
	system("move "FILE_TOML" warp_conf"">nul");
	system("move "FILE_CONF" warp_conf"">nul");
	system("move "TXT_RESULT" warp_conf"">nul");
	move_conf_files();
	puts("done!");
	return 0;
}