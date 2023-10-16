#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	//��׼�������
#include<string.h>	//�ַ���������
#include<stdlib.h>	//��׼�⺯��
/*
�������ͱ�����typedef
*/

typedef unsigned int u32;

typedef struct PERSON {

	char name[64];
	u32 age;
}Person;

void TypedefTest() {

	Person person = { "�������ý��ڴ�",57 };

	printf("%s %u\n", person.name, person.age);
}


/*
void��������
*/

void VoidTest(void) {	//void���κ��������ͺ�������

/*���ܶ���void���ͱ��� err*/

	//void val;		

/*void����ָ�������������ݣ���Ϊ����ָ��*/

	//int
	int a = 10;
	void* p = NULL;
	p = &a;
	printf("(int)%d\n", *(int*)p);

	//char
	char b = 'a';
	p = &b;
	printf("(char)%c\n", *(char*)p);

/*void* �������������͵ķ�װ�����Է����������͵�����*/

	//������memcpy
	//void* memcpy(void* _Dst, const void* _Src, size_t _Size);

}

/*
sizeof������
*/

void Test58(int array[]) {

	printf("Testarr size:%d\n", sizeof array);

}
void SizeofTest(){

//�����÷�
	int a = 10;
	printf("len:%d\n", sizeof(a));
	printf("len:%d\n", sizeof(int));
	printf("len:%d\n", sizeof a);

//sizeof�������
	unsigned int b = 10;

	if (b - 11 < 0)
		printf("���С��0\n");
	else
		printf("�������0\n");	//unsigned int ������Ϊunsigned int

	int c = 5;
	if (sizeof(c) - 10 < 0)
		printf("���С��0\n");
	else
		printf("�������0\n");	//sizeof����ֵ����Ϊunsigned int

	int arr[] = { 10,20,30,40,50 };
	printf("arr size:%d\n", sizeof arr);

	//��������ĳЩ����µȼ���ָ��
	int* parr = arr;
	printf("arr[2]:%d\n", parr[2]);
	printf("arr size:%d\n", sizeof parr);

	//�����������������������˻�Ϊָ��,�ں����ڲ����ٷ��������С
	Test58(arr);
}



/*
�޸ı��������ַ�ʽ
*/
void VariableTest() {

	int a = 10;

	//ֱ���޸�
	a = 20;
	printf("ֱ���޸�%d\n", a);

	//����޸�
	int* p = &a;
	*p = 100;
	printf("����޸�%d\n", a);
}


/*
�ڴ����ģ��-ջ��
*/

char* func121() {

	char a[] = "Hello World";	//��ջ���洢������

	printf("�Ӻ�����%s\n", a);
	return a;
}

void StackAreaTest() {

	char* p = NULL;

	p = func121();
	printf("��������%s\n", p);
}



/*
�ڴ����ģ��-����
*/
char* func142() {

	char* str = malloc(100);
	strcpy(str, "Don't hello world!");
	printf("%s\n", str);
	return str;
}

void func150(char** str) {

	*str = malloc(100);
	strcpy(*str, "Don't hello world!!");
	printf("%s\n", *str);
}


void HeapAreaTest() {

	char* p = NULL;
	p = func142();
	printf("%s\n", p);
	free(p);

	p = NULL;
	func150(&p);		//��ָ�븳ֵ����
	printf("%s\n", p);
	free(p);
}




/*
calloc:���ڴ涯̬�洢���з���nmemb�鳤��Ϊsize�ֽڵ���������
		calloc�Զ���������ڴ���0��
realloc:���·�����malloc����calloc�����ڶ��з����ڴ�ռ�Ĵ�С
*/

void CallocReallocTest() {

	//calloc���ٵĿռ��Զ���ֵ0
	int* p = calloc(10, sizeof(int));
	if (p == NULL)
		return;
	for (int i = 0; i < 10; i++)	//��ֵ
		p[i] = i + 1;

	for (int i = 0; i < 10; i++)	//��ӡ
		printf("calloc Test p[%d]=%d\n", i, p[i]);
	printf("\n\n");


	//������ٵĿռ��ԭ���󣬺����Ŀռ䲻�����
	int* p1 = realloc(p, 15 * sizeof(int));
	if (p1 == NULL)
		return;

	printf("\tp��ַ:%d\tp1��ַ%d\n\n", p, p1);
	printf("\n\n");
	for (int i = 0; i < 15; i++)	//��ӡ
		printf("realloc Test I p1[%d]=%d\n", i, p1[i]);
	printf("\n\n");
	for (int i = 10; i < 15; i++)	//��ʣ��ֵ
		p1[i] = i + 1;

	for (int i = 0; i < 15; i++)	//��ӡ
		printf("realloc Test II p1[%d]=%d\n", i, p1[i]);
	free(p1);
}


/*
ջ������������ڴ��ŷ���
*/

void StackDirectionTest() {

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;

	int num[3] = { 1,2,3 };

	printf("a = %x\n", &a);
	printf("b = %x\n", &b);
	printf("c = %x\n", &c);
	printf("d = %x\n", &d);

	printf("num[0] = %x\n", &num[0]);
	printf("num[1] = %x\n", &num[1]);
	printf("num[2] = %x\n", &num[2]);

	//a�ĵ�ַ����b�ĵ�ַ��������������
	/*
	* �������ԣ���Windowsƽ̨vs���棬����ѡ��32λ��64λ�����ͬ��
	* 32λջ����������64λ��������
	*/
}

void MemoryDirectionTest() {

	int num = 0xaabbccdd;
	unsigned char* p = &num;

	printf("%x\n", *p);
	printf("%x\n", *(p+1));
	printf("%x\n", *(p+2));
	printf("%x\n", *(p+3));

	//С��ģʽ

/*
С�ˣ���ָ���ݵĸ��ֽڱ������ڴ�ĸߵ�ַ�У������ݵĵ��ֽڱ������ڴ�ĵ͵�ַ�У����ִ洢ģʽ����ַ�ĸߵͺ�����λȨ��Ч�ؽ���������ߵ�ַ����Ȩֵ�ߣ��͵�ַ����Ȩֵ�͡���Intel  x86�ṹ����ʹ��С��ģʽ��

��ˣ���ָ���ݵĸ��ֽڱ������ڴ�ĵ͵�ַ�У������ݵĵ��ֽڱ������ڴ�ĸߵ�ַ�У������Ĵ洢ģʽ�е�������ڰ����ݵ����ַ���˳������ַ��С������ӣ������ݴӸ�λ����λ�ţ�������ǵ��Ķ�ϰ��һ�¡���IBM  power PC�ṹ����ʹ�õĴ��ģʽ��

����Ҫ֪�������Ǵ�˻���С�ˣ�cpu�ڶ�ȡ�ʹ洢���ݵ�ʱ��һ�����Ǵ��ڴ�ĵ͵�ַ������ߵ�ַ��ȡ��д�롣
*/
}
void StackMemoryDirection() {

	StackDirectionTest();	//ջ����������
	MemoryDirectionTest();	//�ڴ���������
}