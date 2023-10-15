#define   _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <time.h>
#include <vcruntime_string.h>
#include<windows.h>


FILE* FileOpen(const char *Command) {

	FILE* fp = fopen(PATHFILE, Command);

	if (fp == NULL) {

		perror("File");
		return 0;
	}

	return fp;
}

//a+b=\n
void GetData(){

	char stu[128] = "";
	char bstu[] = { '*','+','-','/'};
	char a, b,c;
	FILE* fp = FileOpen("w");

	srand(time(NULL));

	printf("开始生成随机四则运算...\n");
	Sleep(1500);

	for (int i = 0; i < 10; i++)
	{

		a = rand() % 100 + 1;
		b = rand() % 4;
		c = rand() % 100 + 1;
		sprintf(stu, "%s%d%c%d=\n", stu, a, bstu[b], c);
	}

	printf("四则运算已生成：\n%s",stu);
	Sleep(500);
	if (fputs(stu, fp) == 0)
		printf("写入文件成功\n\n\n");
	fclose(fp);
}


void CalculateData(char* stunumx) {


	char stu[128]  = "";
	
	char* p = NULL;
	int a, c,sum;
	char b;
	FILE* fp = FileOpen("r");

	while(1)
	{
		a = 0, b = 0, c = 0,sum = 0;
		p = fgets(stu, sizeof(stu), fp);
		if (p == NULL)
			break;

		sscanf(stu,"%d%c%d=",&a,&b,&c);

		switch (b)
		{
			case'+':
				sum = a + c;
				break;
			case'-':
				sum = a - c;
				break;
			case'*':
				sum = a * c;
				break;
			case'/':
				sum = a / c;
				break;
			default:
				break;
		}

		sprintf(stunumx, "%s%d%c%d=%d\n", stunumx, a, b, c, sum);
	}
	Sleep(1500);
	printf("计算完成：\n%s", stunumx);
	fclose(fp);
}


void WriteFile(char* stu) {


	FILE* fp = FileOpen("w");

	if(fputs(stu, fp)==0)
		printf("写入文件成功\n");

	fclose(fp);
}