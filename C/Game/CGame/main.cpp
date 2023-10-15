#define   _CRT_SECURE_NO_WARNINGS

#include "main.h"

/*
暂时无法解决检测ESC输入问题
*/

int main() {

	char str1[MAX];
	char str2[MAX] = "";
	long long int Start = 0, End = 0;
	Start = GetTime();
	GetStr(str1);

	while (1) {

		StrJudge(str1, str2);
		system("cls");
		if (strlen(str2) == 50)
			break;
	}
	

	End = GetTime();
	printf("游戏结束，共用时:%ds\n", End - Start);
	printf("共输入:%d字\n", strlen(str2));
	printf("你的目标为：%s\n", str1);
	printf("你的输入为：%s\n", str2);
}