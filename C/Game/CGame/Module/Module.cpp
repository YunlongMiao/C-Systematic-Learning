#define   _CRT_SECURE_NO_WARNINGS

#include "main.h"

void GetStr(char *str) {

	srand((uint)time(NULL));	//�������
	int i = 0;

	for (i = 0; i < MAX - 1; i++)	//���50��Ӣ����ĸ
		str[i] = rand() % 26 + 'a';

	str[MAX - 1] = '\0';	//������־λ
	/**(str + MAX - 1) = '\0';*/
}


long long int GetTime() {

	return time(NULL);
}

void StrJudge(char* str1, char* str2) {

	char ch = '\n',ch2;
	int temp = 0;

	printf("%s\n", str1);	//��ӡĿ���ַ���
	puts(str2);				//��ӡ�������ַ�

	temp = strlen(str2);
	/*printf("Str = %d\n", temp);*/

	while (ch == '\n') {
		ch = getchar();
		/*scanf("%c", &ch);*/
		while ((ch2 = getchar()) != '\n');	//��ջ�����

	}
	/*printf("%c\n", ch);*/
	if (ch == '\033')
		
		printf("ESC");
		/*exit(0);*/
	else if (ch == str1[temp])
		str2[temp] = ch;
	else
		str2[temp] = '_';
	
}
