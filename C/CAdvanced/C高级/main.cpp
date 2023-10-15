#define   _CRT_SECURE_NO_WARNINGS	//c4996
#include<stdio.h>	//标准输入输出
#include<string.h>	//字符串处理函数
#include<stdlib.h>	//标准库函数


int* test01() {

	int* p = (int*)malloc(sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
		p[i] = 100 + i;

	if (p == NULL)
		return 0;
	return p;
}
int main() {

	for (int i = 0; i < 5; i++)
		printf("%d\n", test01()[i]);
	free(test01());

	system("pause");
	return EXIT_SUCCESS;
}
