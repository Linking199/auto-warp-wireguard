#include "header.h"

char *Get_result(const char command[]) {//返回的字符串末尾有个'\n'
	FILE *pipe = popen(command, "r");//特供给get-key_2.0.exe的用于获得key的函数
	if (!pipe) {
		printf("Failed to run \"%s\"\n", command);
		exit(1);
	}

	char *key = (char *)malloc(sizeof(char) * ONE_LINE_WARD_MAX);
	if (fgets(key, ONE_LINE_WARD_MAX, pipe) != NULL) {
		pclose(pipe);
		for (int i = 0; key[i] != '\0'; i++)
			if (key[i] == '\n')
				key[i] = '\0';
		return key;
	}
}

void Wgcf_work(char *key) {
	char *command_reg = Joint_str(2, EXE_WGCF, " register");
	char *command_upd = Joint_str(2, EXE_WGCF, " update");
	char *command_gen = Joint_str(2, EXE_WGCF, " generate");
	char feature1[ONE_LINE_WARD_MAX] = "license_key";
	char feature2[ONE_LINE_WARD_MAX] = "Endpoint";
	char *temp;

	temp = Joint_str(4, feature1, " = \'", key, "'\n");
	system(command_reg);
	free(command_reg);

//	system("pause");

	Change_content(FILE_TOML, feature1, temp);
	free(temp);

	system(command_upd);
	free(command_upd);

	system(command_gen);
	free(command_gen);

	temp = Joint_str(2, feature2, " = ");
	Change_content(FILE_CONF, feature2, temp);
}

char *Joint_str(int count, ...) {
	int count_len = 0;
	char *new_str = NULL;
	va_list args;
	va_start(args, count);

	for (int i = 0; i < count; ++i) {
		char *str = va_arg(args, char *);
		count_len += strlen(str);
	}
	va_end(args);//完成计算字符串总长

	new_str = malloc(sizeof(char) * (count_len + 1));
	*new_str = '\0'; /*重点！一个刚被分配内存的指针并不是字符串*/

	va_start(args, count);
	for (int i = 0; i < count; ++i) {
		char *str = va_arg(args, char *);
		strcat(new_str, str);
	}
	va_end(args);//完成字符串拼接

	return new_str;
}

void Change_content(const char *file_name, const char *feature, const char *new_cont) {
	char temp_file[] = "temp.txt";
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("%s open,failed", file_name);
		getchar();
	}
	FILE *temp_fp = fopen(temp_file, "w+");
	if (fp == NULL) {
		printf("%s open,failed", temp_file);
		getchar();
	}

	char read_cont[ONE_LINE_WARD_MAX];
	int found = 0;

	while ((fgets(read_cont, ONE_LINE_WARD_MAX, fp)) != NULL) {
		if (strstr(read_cont, feature)) {
			found = 1;
			fputs(new_cont, temp_fp);
		} else {
			fputs(read_cont, temp_fp);
		}
	}
	fclose(fp);
	fclose(temp_fp);

	if (found) {
		remove(file_name);
		rename(temp_file, file_name);
	} else {
		remove(temp_file);
		printf("%s changed failed, (enter) to exit", file_name);
		getchar();
		exit(1);
	}
}

void For_RESULT_SVC(const char *film_name) {
	FILE *fp = fopen(film_name, "r");
	if (fp == NULL) {
		printf("%s open failed\n", film_name);
		system("pause");
		exit(1);
	}
	char temp_file[] = TXT_RESULT;
	FILE *temp_fp = fopen(temp_file, "w+");
	if (temp_fp == NULL) {
		printf("%s open failed\n", temp_file);
		system("pause");
		exit(1);
	}

	char read_cont[ONE_LINE_WARD_MAX],backup[ONE_LINE_WARD_MAX], *token_1, *token_2;
	const char delim[] = ",";
	while (fgets(read_cont, ONE_LINE_WARD_MAX, fp)) {
		strcpy(backup,read_cont);
		token_1 = strtok(read_cont, delim);
		token_2 = strtok(NULL, delim);
		if (!strcmp(token_2, "0.00%")) {
//			fputs(token_1, temp_fp);
			fputs(backup, temp_fp);//受限于gen_conf.exe，需要保留丢包率等信息
//			fputc('\n', temp_fp);
		}
	}
	fclose(fp);
	fclose(temp_fp);

	remove(film_name);
}

char *For_clone_key(){//特供给clone_key.exe的用于获得key的函数
	const char OUT_txt[]="output.txt";
	FILE *env=fopen(".env","w+");
	fputs("BASE_KEYS="EG_KEY"\n",env);
	fputs("THREADS_COUNT=1\n",env);
	fputs("DEVICE_MODELS=\"Desktop\"\n",env);
	fputs("# PROXY_FILE=\n",env);
	fputs("DELAY=25\n",env);
	fprintf(env,"OUTPUT_FILE=%s\n",OUT_txt);
	fputs("OUTPUT_FORMAT={key}",env);
	fclose(env);
	system(EXE_CLONE_KEY" >nul");
	
	char *key = (char *)malloc(sizeof(char) * ONE_LINE_WARD_MAX);
	FILE *out=fopen(OUT_txt,"r");
	fgets(key,ONE_LINE_WARD_MAX,out);
	for(int i=0;key[i]!='\0';i++)	if(key[i]=='\n') key[i]='\0';
	fclose(out);
	remove(".env");
	remove(OUT_txt);
	
	return key;
}

void packup_conf(){
  // 创建新文件夹 wireguard_conf
    if (mkdir("wireguard_conf") != 0) {
        printf("Failed to create directory.\n");
        return 1;
    }

    // 打开当前目录
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Failed to open directory.\n");
        return 1;
    }

    struct _finddata_t file_info;
    intptr_t handle = _findfirst("*", &file_info);
    if (handle == -1) {
        printf("Failed to find first file.\n");
        return 1;
    }

    do {
        if (file_info.attrib & _A_ARCH) { // 只处理普通文件
            // 获取文件名
            char *filename = file_info.name;
            // 获取文件名后缀
            char *extension = strrchr(filename, '.');
            if (extension != NULL && strcmp(extension, ".conf") == 0) { // 判断后缀名为.conf的文件
                // 构建目标文件路径
                char dest_path[100];
                snprintf(dest_path, sizeof(dest_path), "wireguard_conf/%s", filename);
                // 移动文件
                if (rename(filename, dest_path) != 0) {
                    printf("Failed to move file: %s\n", filename);
                }
            }
        }
    } while (_findnext(handle, &file_info) == 0);

    _findclose(handle);
    closedir(dir);
}

void remove_directory(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filepath[100];
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

        struct stat file_stat;
        if (stat(filepath, &file_stat) == 0) {
            if (S_ISDIR(file_stat.st_mode)) {
                remove_directory(filepath); // 递归删除子文件夹
            } else {
                remove(filepath); // 删除文件
            }
        }
    }

    closedir(dir);
    rmdir(path); // 删除当前文件夹
}

void move_conf_files() {
    // 检查 "wireguard_conf" 文件夹是否存在
    struct stat dir_stat;
    if (stat("wireguard_conf", &dir_stat) == 0 && S_ISDIR(dir_stat.st_mode)) {
        // 存在，则删除现有的 "wireguard_conf" 文件夹及其内容
        remove_directory("wireguard_conf");
    }

    // 创建新文件夹 wireguard_conf
    if (mkdir("wireguard_conf") != 0) {
        printf("Failed to create directory.\n");
        return;
    }

    // 打开当前目录
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Failed to open directory.\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char filepath[100];
        snprintf(filepath, sizeof(filepath), "./%s", entry->d_name);

        DWORD attributes = GetFileAttributes(filepath);
        if (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // 获取文件名后缀
            char *extension = strrchr(entry->d_name, '.');
            if (extension != NULL && strcmp(extension, ".conf") == 0) { // 判断后缀名为.conf的文件
                // 构建目标文件路径
                char dest_path[100];
                snprintf(dest_path, sizeof(dest_path), "wireguard_conf/%s", entry->d_name);
                // 移动文件
                if (rename(entry->d_name, dest_path) != 0) {
                    printf("Failed to move file: %s\n", entry->d_name);
                }
            }
        }
    }

    closedir(dir);
}