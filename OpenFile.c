
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//二位字符数组，一维字符串数组：存放路径，文件名
char** paths, ** names;
//存放路径个数
short len = 0;
//文件位置(相对路径)
char nameFile[] = "names.txt", pathFile[] = "paths.txt";

//将字符1~9，a~z, A~Z转化为1~36
int changeCh(char ch) {
	if (ch >= 48 && ch <= 57)
		return ch - 48;
	else if (ch >= 65 && ch <= 90)
		return ch - 55;
	else if (ch >= 97 && ch <= 122)
		return ch - 87;
	return -1;
}

//从指定文件获取路径和文件名
int ReadFile() {
	//文件指针
	FILE* nameFp, * pathFp;
	//临时存放字符串,循环变量
	char tempStr[1024];
	int i = 0;

	nameFp = fopen(nameFile, "r");
	pathFp = fopen(pathFile, "r");
	//如果打不开，说明是第一次运行，返回主函数
	if (nameFp == NULL) {
		return 0;
	}
	if (pathFp == NULL) {
		return 0;
	}

	//文件存在，读取文件名信息，并去掉换行符，每读取一个，len(数组长度)加1
	while (!feof(nameFp)) {
		fgets(tempStr, 1024, nameFp);
		if (tempStr[strlen(tempStr)-1] != '\n') {
			break;
		}
		tempStr[strlen(tempStr) - 1] = '\0';
		names[i] = (char*)malloc(sizeof(char) * (strlen(tempStr) + 1));
		strcpy(names[i++], tempStr);
		len++;
	}
	//因为最后文件最后是一个换行符所以len--，重置循环变量，然后读取路径信息，并去掉换行符
	len--;
	i = 0;
	while (!feof(pathFp)) {
		fgets(tempStr, 1024, pathFp);
		if (tempStr[strlen(tempStr)-1] != '\n') {
			break;
		}
		tempStr[strlen(tempStr) - 1] = '\0';
		paths[i] = (char*)malloc(sizeof(char) * (strlen(tempStr) + 1));
		strcpy(paths[i++], tempStr);
	}

	fclose(nameFp);
	fclose(pathFp);
	return 1;
}

//将names，paths中的信息写入指定文件
int WriteFile() {
	//文件指针
	FILE* nameFp, * pathFp;
	//循环变量
	int i = 0;

	nameFp = fopen(nameFile, "w");
	pathFp = fopen(pathFile, "w");
	for (i = 0; i < len; i++) {
		fprintf(nameFp, "%s\n", names[i]);
	}
	for (i = 0; i < len; i++) {
		fprintf(pathFp, "%s\n", paths[i]);
	}

	fclose(nameFp);
	fclose(pathFp);
	return 1;
}

int FirstExe() {
	//中间变量
	int i;
	char tempName[1024], tempPath[1024];
	//提示信息，输入初始路径数量
	printf("\t欢迎使用快捷命令\n");
	printf("输入样例（名字和路径）：python文件夹 D)\\acPython\n");
	printf("请输入需要创建的命令条数（不得超过35）：");
	scanf("%d", &len);

	for (i = 0; i < len; i++) {
		printf("第%d条 名字和路径：", i + 1);
		//吃掉上一个回车符
		getchar();
		scanf("%s %s", tempName, tempPath);
		names[i] = (char*)malloc(sizeof(char) * (strlen(tempName) + 1));
		strcpy(names[i], tempName);
		paths[i] = (char*)malloc(sizeof(char) * (strlen(tempPath) + 1));
		strcpy(paths[i], tempPath);
	}
	WriteFile();
	printf("写入成功，按任意键退出，再次打开就可以使用了\n");
}

int printTitle() {
	int i = 0;
	system("cls");
	for (i = 0; i < len; i++) {
		if (i < 9) {
			printf("%d, %s\n", i + 1, names[i]);
		}
		else {
			printf("%c, %s\n", i + 88, names[i]);
		}
	}
	printf("x、修改\n");
	printf("y、新建一条路径\n");
	printf("z、quit\n");
	return 1;
}

int updatePaths() {
	char ch, num;
	char nameStr[1024], pathStr[1024];
	printf("例1: 1 名字 D:\\acPython\n");
	printf("例2: a 名字 D:\\acPython\n");
	printf("请输入：");
	scanf("%c%s%s", &ch, nameStr, pathStr);
	num = changeCh(ch) - 1;
	free(names[num]);
	free(paths[num]);
	names[num] = (char*)malloc(sizeof(char) * (strlen(nameStr) + 1));
	paths[num] = (char*)malloc(sizeof(char) * (strlen(pathStr) + 1));
	strcpy(names[num], nameStr);
	strcpy(paths[num], pathStr);
	printf("更新中...\n");
	WriteFile();
	printf("更新成功！\n");
	printTitle();

	return 1;
}


int addPaths() {
	char ch, num;
	char nameStr[1024], pathStr[1024];
	FILE* nameFp, * pathFp;
	printf("例1: 名字 D:\\acPython\n");
	printf("请输入：");
	scanf("%s%s", nameStr, pathStr);
	names[len] = (char*)malloc(sizeof(char) * (strlen(nameStr) + 1));
	paths[len] = (char*)malloc(sizeof(char) * (strlen(pathStr) + 1));
	strcpy(names[len], nameStr);
	strcpy(paths[len], pathStr);
	printf("更新中...\n");
	
	nameFp = fopen(nameFile, "a");
	pathFp = fopen(pathFile, "a");
	fprintf(nameFp, "%s\n", names[len]);
	fprintf(pathFp, "%s\n", paths[len]);
	len++;
	fclose(nameFp);
	fclose(pathFp);
	printf("更新成功！\n");
	printTitle();

	return 1;
}

int exeCmd() {
	char tempStr[1024] = "explorer ";
	int ao = 0, num = 0;
	char ch;
	while (1) {
		ch = getch();
		num = changeCh(ch);

		if (num > 0 && num <= len) {
			strcat(tempStr, paths[num - 1]);
			system(tempStr);
			exit(0);
		}
		else if (num == 33) {
			updatePaths(-1, names, paths);
			exeCmd();
		}
		else if (num == 34) {
			addPaths(names, paths);
			exeCmd();
		}
		else if (num == 35)
			exit(0);
		else if (num == 0) {
			printf("选择无效，请重新选择：\n");
			if (ao == 2) {
				system("explorer D:\\aa我的文件\\123");
				exit(0);
			}
			else {
				ao++;
			}
		}
		else {
			printf("选择无效，请重新选择：\n");
		}
	}
}

int main() {
	names = (char**)malloc(sizeof(char*) * 50);
	paths = (char**)malloc(sizeof(char*) * 50);

	//system("color 09");
	if (ReadFile() == 0) {
		FirstExe();
	}
	else {
		printTitle();
		exeCmd();
	}

	return 0;
}
