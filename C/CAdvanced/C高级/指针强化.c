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