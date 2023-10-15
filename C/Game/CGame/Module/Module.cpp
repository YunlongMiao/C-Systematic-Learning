#define   _CRT_SECURE_NO_WARNINGS

#include "main.h"

void GetStr(char *str) {

	srand((uint)time(NULL));	//随机种子
	int i = 0;

	for (i = 0; i < MAX - 1; i++)	//获得50个英文字母
		str[i] = rand() % 26 + 'a';

	str[MAX - 1] = '\0';	//结束标志位
	/**(str + MAX - 1) = '\0';*/
}


long long int GetTime() {

	return time(NULL);
}

void StrJudge(char* str1, char* str2) {

	char ch = '\n',ch2;
	int temp = 0;

	printf("%s\n", str1);	//打印目标字符串
	puts(str2);				//打印已输入字符

	temp = strlen(str2);
	/*printf("Str = %d\n", temp);*/

	while (ch == '\n') {
		ch = getchar();
		/*scanf("%c", &ch);*/
		while ((ch2 = getchar()) != '\n');	//清空缓冲区

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
