
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//��λ�ַ����飬һά�ַ������飺���·�����ļ���
char** paths, ** names;
//���·������
short len = 0;
//�ļ�λ��(���·��)
char nameFile[] = "names.txt", pathFile[] = "paths.txt";

//���ַ�1~9��a~z, A~Zת��Ϊ1~36
int changeCh(char ch) {
	if (ch >= 48 && ch <= 57)
		return ch - 48;
	else if (ch >= 65 && ch <= 90)
		return ch - 55;
	else if (ch >= 97 && ch <= 122)
		return ch - 87;
	return -1;
}

//��ָ���ļ���ȡ·�����ļ���
int ReadFile() {
	//�ļ�ָ��
	FILE* nameFp, * pathFp;
	//��ʱ����ַ���,ѭ������
	char tempStr[1024];
	int i = 0;

	nameFp = fopen(nameFile, "r");
	pathFp = fopen(pathFile, "r");
	//����򲻿���˵���ǵ�һ�����У�����������
	if (nameFp == NULL) {
		return 0;
	}
	if (pathFp == NULL) {
		return 0;
	}

	//�ļ����ڣ���ȡ�ļ�����Ϣ����ȥ�����з���ÿ��ȡһ����len(���鳤��)��1
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
	//��Ϊ����ļ������һ�����з�����len--������ѭ��������Ȼ���ȡ·����Ϣ����ȥ�����з�
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

//��names��paths�е���Ϣд��ָ���ļ�
int WriteFile() {
	//�ļ�ָ��
	FILE* nameFp, * pathFp;
	//ѭ������
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
	//�м����
	int i;
	char tempName[1024], tempPath[1024];
	//��ʾ��Ϣ�������ʼ·������
	printf("\t��ӭʹ�ÿ������\n");
	printf("�������������ֺ�·������python�ļ��� D)\\acPython\n");
	printf("��������Ҫ�������������������ó���35����");
	scanf("%d", &len);

	for (i = 0; i < len; i++) {
		printf("��%d�� ���ֺ�·����", i + 1);
		//�Ե���һ���س���
		getchar();
		scanf("%s %s", tempName, tempPath);
		names[i] = (char*)malloc(sizeof(char) * (strlen(tempName) + 1));
		strcpy(names[i], tempName);
		paths[i] = (char*)malloc(sizeof(char) * (strlen(tempPath) + 1));
		strcpy(paths[i], tempPath);
	}
	WriteFile();
	printf("д��ɹ�����������˳����ٴδ򿪾Ϳ���ʹ����\n");
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
	printf("x���޸�\n");
	printf("y���½�һ��·��\n");
	printf("z��quit\n");
	return 1;
}

int updatePaths() {
	char ch, num;
	char nameStr[1024], pathStr[1024];
	printf("��1: 1 ���� D:\\acPython\n");
	printf("��2: a ���� D:\\acPython\n");
	printf("�����룺");
	scanf("%c%s%s", &ch, nameStr, pathStr);
	num = changeCh(ch) - 1;
	free(names[num]);
	free(paths[num]);
	names[num] = (char*)malloc(sizeof(char) * (strlen(nameStr) + 1));
	paths[num] = (char*)malloc(sizeof(char) * (strlen(pathStr) + 1));
	strcpy(names[num], nameStr);
	strcpy(paths[num], pathStr);
	printf("������...\n");
	WriteFile();
	printf("���³ɹ���\n");
	printTitle();

	return 1;
}


int addPaths() {
	char ch, num;
	char nameStr[1024], pathStr[1024];
	FILE* nameFp, * pathFp;
	printf("��1: ���� D:\\acPython\n");
	printf("�����룺");
	scanf("%s%s", nameStr, pathStr);
	names[len] = (char*)malloc(sizeof(char) * (strlen(nameStr) + 1));
	paths[len] = (char*)malloc(sizeof(char) * (strlen(pathStr) + 1));
	strcpy(names[len], nameStr);
	strcpy(paths[len], pathStr);
	printf("������...\n");
	
	nameFp = fopen(nameFile, "a");
	pathFp = fopen(pathFile, "a");
	fprintf(nameFp, "%s\n", names[len]);
	fprintf(pathFp, "%s\n", paths[len]);
	len++;
	fclose(nameFp);
	fclose(pathFp);
	printf("���³ɹ���\n");
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
			printf("ѡ����Ч��������ѡ��\n");
			if (ao == 2) {
				system("explorer D:\\aa�ҵ��ļ�\\123");
				exit(0);
			}
			else {
				ao++;
			}
		}
		else {
			printf("ѡ����Ч��������ѡ��\n");
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
