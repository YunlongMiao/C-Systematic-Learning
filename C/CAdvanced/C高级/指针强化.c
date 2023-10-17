#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	//��׼�������
#include<string.h>	//�ַ���������
#include<stdlib.h>	//��׼�⺯��

//ָ�����
void PointVariableTest() {

	int* p1 = 0x1234;
	int*** p2 = 0x1111;

	printf("p1 size:%d\n", sizeof(p1));
	printf("p2 size:%d\n", sizeof(p2));

	int a = 10;
	p1 = &a;

	printf("p1 address:%p\n", &p1);
	printf("p1 address:%p\n", p1);
	printf("a address:%p\n", &a);
}


//Ұָ��Ϳ�ָ��

//��������NULL�ͷǷ���ַ�����ڴ�

void OtherPointTest() {

	char* p = NULL;
	//��p��ָ�ڴ����򿽱�����
	//strcpy(p, "1111");	//err ��ָ��

	char* q = 0x1122;		//Ұָ��,���ɶ�ȡ�����ɷ���
	//��q��ָ�ڴ����򿽱�����
	//strcpy(q, "2222");

	//p = 0x001;
	//printf("%d\n", p);
	//*p = 100;
}



//��ӷ��ʲ�����

void VisitOperatorTest() {

	int* p = NULL;
	int a = 10;

	p = &a;
	*p = 100;
	int b = *p;

	char* str = "hello world!";	//err �����������ɸ���
	//*str = 'm';

	printf("a:%d\n", a);
	printf("*p:%d\n", *p);
	printf("b:%d\n", b);
	printf("str:%s\n", str);
}


//ָ��Ĳ���
typedef struct PERSON {

	char a;		//0~3
	int b;		//4~7
	char buf[64];	//8~71
	int d;		//72~75
}Person;

void PointStepSizeTest() {

	int num = 0xaabbccdd;
	unsigned int* p1 = &num;
	unsigned char* p2 = &num;

	printf("%x\n", *p1);
	printf("%x\n", *p2);	//dd-С��ģʽ

	printf("%x\n", p1);
	printf("%x\n", p1+1);

	printf("%x\n", p2);
	printf("%x\n", p2+1);


	Person p = { 'a',10,"Hello World",1000 };

	//p��d����ƫ�����Ƕ���
	printf("d��ƫ����Ϊ��%d\n", offsetof(Person, d));

	printf("d��ֵΪ��%d\n", *(int*)((char*)&p + offsetof(Person, d)));

}

//�ַ���ע������,sizeof��strlen���Է�Χ

void StrAttentionTest() {

	//�ַ�����βҪ��\0
	char str1[] = { 'H','e','l','l','o' ,'\0'};
	printf("%s\n", str1);

	char str2[100] = { 'H','e','l','l','o' };
	printf("%s\n", str2);

	char str3[] = "Hello";
	printf("%s\n", str3);
	printf("sizeof of str3:%d\n", sizeof(str3));	//6
	printf("strlen of str3:%d\n", strlen(str3));	//5

	char str4[100] = "Hello";
	printf("sizeof of str4:%d\n", sizeof(str4));	//100
	printf("strlen of str4:%d\n", strlen(str4));	//5

	char str5[] = "hello\0world";
	printf("sizeof of str5:%d\n", sizeof(str5));	//12
	printf("strlen of str5:%d\n", strlen(str5));	//5

	char str6[] = "hello\012world";		//\012 �˽������� ת��Ϊʮ���� 10 ��ӦASCII�� ����
	printf("sizeof of str6:%d\n", sizeof(str6));	//12
	printf("strlen of str6:%d\n", strlen(str6));	//11

}

/*
�ַ�����ϰ
*/

//��������1
void copy_string01(char* dest, char* source) {

	for (int i = 0; source[i] != '\0'; i++) {
		dest[i] = source[i];
	}

}

//��������2
void copy_string02(char* dest, char* source) {
	while (*source != '\0' /* *source != 0 */) {
		*dest = *source;
		source++;
		dest++;
	}
}

//��������3
void copy_string03(char* dest, char* source) {
	//�ж�*dest�Ƿ�Ϊ0��0���˳�ѭ��
	while (*dest++ = *source++) {}
}


void reverse_string(char* str) {

	if (str == NULL) {
		return;
	}

	int begin = 0;
	int end = strlen(str) - 1;

	while (begin < end) {

		//���������ַ�Ԫ��
		char temp = str[begin];
		str[begin] = str[end];
		str[end] = temp;

		begin++;
		end--;
	}

}



void StrExercisesTest() {

	//�ַ�����������ʵ��
	char str1[] = "Hello World!";
	char str2[100] = "";
	copy_string01(str2,str1);
	printf("str2-01:%s\n", str2);
	copy_string02(str2, str1);
	printf("str2-02:%s\n", str2);
	copy_string03(str2, str1);
	printf("str2-03:%s\n", str2);

	//�ַ�����תģ��
	char str[] = "abcdefghijklmn";
	reverse_string(str);
	printf("str:%s\n", str);
}

//�ַ�����ʽ��
void StrFormattingTest() {

	//1. ��ʽ���ַ���
	char buf[1024] = { 0 };
	{
		sprintf(buf, "���,%s,��ӭ��������!", "John");
		printf("buf:%s\n", buf);

		memset(buf, 0, 1024);
		sprintf(buf, "�ҽ���%d����!", 20);
		printf("buf:%s\n", buf);
	}

	//2. ƴ���ַ���
	{
		memset(buf, 0, 1024);
		char str1[] = "hello";
		char str2[] = "world";
		int len = sprintf(buf, "%s %s", str1, str2);
		printf("buf:%s len:%d\n", buf, len);
	}

	//3. ����ת�ַ���
	{
		memset(buf, 0, 1024);
		int num = 100;
		sprintf(buf, "%d", num);
		printf("buf:%s\n", buf);

		//���ÿ�� �Ҷ���
		memset(buf, 0, 1024);
		sprintf(buf, "%8d", num);
		printf("buf:%s\n", buf);

		//���ÿ�� �����
		memset(buf, 0, 1024);
		sprintf(buf, "%-8d", num);
		printf("buf:%s\n", buf);

		//ת��16�����ַ��� Сд
		memset(buf, 0, 1024);
		sprintf(buf, "0x%x", num);
		printf("buf:%s\n", buf);

		//ת��8�����ַ���
		memset(buf, 0, 1024);
		sprintf(buf, "0%o", num);
		printf("buf:%s\n", buf);
	}


	//1. ��������
	
	{
		//����ǰ�������
		//ƥ���һ���ַ��Ƿ������֣�����ǣ�������
		//���������ֹͣƥ��
		memset(buf, 0, 1024);
		sscanf("123456aa65aa", "%*d%s", buf);	//ֻ��ƥ��λ��ǰ����ַ�  aa65aa
		printf("�������� buf:%s\n", buf);
	}


	//2. ��ȡָ���������
	{
		//����ǰ�������
		memset(buf, 0, 1024);
		sscanf("123456aaaa", "%7s", buf);
		printf("��ȡָ��������� buf:%s\n", buf);
	}


	//3. ƥ��a-z�������ַ�
	{
		//����ǰ�������
		//��ƥ���һ���ַ����ж��ַ��Ƿ���a-z�е��ַ��������ƥ��
		//�������ֹͣƥ��
		memset(buf, 0, 1024);
		sscanf("abcdefgAA123456A", "%[a-z]", buf);
		printf("ƥ��a-z�������ַ� buf:%s\n", buf);
	}

	//4. ƥ��aBc�е��κ�һ��
	{
		//����ǰ�������
		//��ƥ���һ���ַ��Ƿ���aBc�е�һ��������ǣ���ƥ�䣬���������ֹͣƥ��
		memset(buf, 0, 1024);
		sscanf("abcdefg123456", "%[aBc]", buf);
		printf("ƥ��aBc�е��κ�һ�� buf:%s\n", buf);
	}

	//5. ƥ���a�������ַ�
	{
		memset(buf, 0, 1024);
		sscanf("bcdefag123456", "%[^a]", buf);
		printf("ƥ���a�������ַ� buf:%s\n", buf);
	}

	//6. ƥ���a-z�е������ַ�
	{
		memset(buf, 0, 1024);
		sscanf("123456ABCDbcdefag", "%[^a-z]", buf);
		printf("ƥ���a-z�е������ַ� buf:%s\n", buf);
	}

}

//�ָ�����
void StrFormattingTest_T() {
	//�ָ�����
	char str1[] = "416wge#MiaoYunLong@outlook.com";
	char str2[1024] = "";
	sscanf(str1, "%*[^#]#%[^@]", str2);
	printf("%s\n", str2);
}


//�ַ���ǿ��-�Ӵ�����
void StrStrengthenFindTest() {

	char* str = "sgwfaufcgbquifbhquagxcaufhbwuf";
	char* goal = "bqu";
	int temp = -1;

	//�Լ�д��
	{
		for (int i = 0; i < strlen(str) - 2; i++)
		{
			if (str[i] == goal[0])
			{
				for (int f = 1; f < strlen(goal); f++)
				{
					if (str[i + f] != goal[f])
						break;
					temp = i;
				}
			}
		}
		printf("%d\n", temp);
	}

	//��Ƶ����
	{
		int x = 0;
		temp = -1;
		while (*str != '\0') 
		{


			if (*str != *goal) 
			{
				x++;
				str++;
				continue;
			}

			//������ʱָ��
			char* temstr = str;
			char* temgoal = goal;

			while (*temgoal != '\0') 
			{
				
				temstr++;
				temgoal++;

				if (*temstr != *temgoal)//ƥ��ʧ�����
					break;
			}

			str++;

			if (*temgoal == '\0')
			{
				temp = x;
				x = -1;
				printf("%d\n", temp);
				break;
			}
		}
		if(x != -1)
			printf("%d\n", temp);
	}
}


/*
һ��ָ���״��
*/
//ָ���ƶ��󲻿�free
void FirstOrderPointerTest() {

	char* p = (char*)malloc(sizeof(char) * 64);
	char* pp = p;
	for (int i = 0; i < 10; i++)
	{
		*pp = i + 97;
		printf("%c\n", *pp);
		pp++;
	}

	free(p);

	p = NULL;

}


/*
����ָ����������
*/

void SecondOrderPointerOutputTest() {

	//�ڶ��������ڴ�
	int** pArray = malloc(sizeof(int*) * 5);

	//��ջ�Ͽ�������
	int a1 = 100;
	int a2 = 200;
	int a3 = 300;
	int a4 = 400;
	int a5 = 500;

	//��������ά�� ջ�����ݵĵ�ַ��������ϵ
	pArray[0] = &a1;
	pArray[1] = &a2;
	pArray[2] = &a3;
	pArray[3] = &a4;
	pArray[4] = &a5;

	int** Array = pArray;	//�����*�������˻�Ϊ**ָ��
	
	printf("%d\n", sizeof((Array)) / sizeof(int*));
	printf("%d\n", strlen((*Array)));

	for (int i = 0; i < 5; i++)
		printf("%d\n", *Array[i]);

	//�ͷŶ����ռ�
	if (pArray != NULL)
	{
		free(pArray);
		pArray = NULL;
	}

}



/*
����ָ�����������
*/
void SecondOrderPointerInputTest() {

	//��ջ�Ͽ����ڴ�
	int* pArray[5];
	for (int i = 0; i < 5; i++) {

		pArray[i] = malloc(4);//ջ��ÿ������ ά�� ջ�����ٵ��ڴ�
		*(pArray[i]) = i + 100;
	}
	int** Array = pArray;

	printf("%d\n", sizeof(pArray) / sizeof(int*));	//5 pArray ����
	printf("%d\n", sizeof(Array) / sizeof(int*));	//1 Array	����ָ��
	printf("%d\n", strlen((*Array)));				//1

	for (int i = 0; i < 5; i++)
		printf("%d\n", *Array[i]);

	//���������ͷ�
	for (int i = 0; i < 5; i++)
	{
		if (pArray[i] != NULL)
			free(pArray[i]);
		pArray[i] = NULL;
	}

}


/*
����ָ���������������������
*/
void AllocateSpace(int** pp) {

	int* pArray = malloc(sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
		pArray[i] = i + 100;

	*pp = pArray;
}
void SecondOrderPointerParameterOutputTest() {

	int* p = NULL;
	AllocateSpace(&p);

	for (int i = 0; i < 10; i++)
		printf("%d\n", p[i]);

	int** arr = &p;
	for (int i = 0; i < 10; i++)
		printf("%d\n", (*arr)[i]);

	//�ͷŶ�������
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}


/*
����ָ����ϰ-�ļ���д
*/

int getFileLines(FILE* fp) {

	if (fp == NULL)
		return -1;

	char buf[1024];
	int lines = 0;

	while (fgets(buf, 1024, fp) != NULL)
	{
		lines++;
		//printf("%s\n", buf);
	}

	//���������
	fseek(fp, 0, SEEK_SET);

	return lines;
}

void readFileData(FILE* FILE, char** pArray,int len) {

	if (FILE == NULL || pArray == NULL || len <= 0)
		return;

	char buf[1024] = { 0 };
	int index = 0;

	while (fgets(buf, 1024, FILE) != NULL) {

		//���㿪��ÿ���ַ����Ĵ�С
		int currentLen = strlen(buf) + 1;
		//�ַ�������ַ���Ϊ \0
		buf[strlen(buf) - 1] = '\0';

		//���ٶ����ռ�
		char* currentP = malloc(sizeof(char) * currentLen);

		//���ļ��ж�ȡ�����ݣ��ŵ����ٵĿռ���
		strcpy(currentP, buf);

		//�����ٿռ������ ����������
		pArray[index++] = currentP;

		//���buf
		memset(buf, 0, 1024);
	}
}

void SecondOrderPointerFileRWTest() {

	//���ļ�
	FILE* fp = fopen("./filetest.txt", "r");
	if (fp == NULL)
		printf("open file fail");

	//��ȡ�ļ���Ч����
	int len = getFileLines(fp);
	printf("%d\n", len);
	char** pArray = malloc(sizeof(char*) * len);

	//���ļ��е����ݷŵ�pArray��������
	readFileData(fp,pArray,len);

	//��ӡ����
	for (int i = 0; i < len; i++)
		printf("%s\n", pArray[i]);

	//�ر��ļ�
	fclose(fp);
	fp = NULL;
	//�ͷŶ���
	for(int i=0;i<len;i++)
		if (pArray[i] != NULL)
		{
			printf("%s���ͷ�\n", pArray[i]);
			free(pArray[i]);
			pArray[i] = NULL;
		}

	free(pArray);
	pArray = NULL;

}

