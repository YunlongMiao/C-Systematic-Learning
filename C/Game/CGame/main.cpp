#define   _CRT_SECURE_NO_WARNINGS

#include "main.h"

/*
��ʱ�޷�������ESC��������
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
	printf("��Ϸ����������ʱ:%ds\n", End - Start);
	printf("������:%d��\n", strlen(str2));
	printf("���Ŀ��Ϊ��%s\n", str1);
	printf("�������Ϊ��%s\n", str2);
}