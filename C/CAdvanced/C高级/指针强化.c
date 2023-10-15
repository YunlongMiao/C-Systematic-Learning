#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	//标准输入输出
#include<string.h>	//字符串处理函数
#include<stdlib.h>	//标准库函数

//指针变量

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


//野指针和空指针

//不允许向NULL和非法地址拷贝内存

void OtherPointTest() {

	char* p = NULL;
	//给p所指内存区域拷贝内容
	//strcpy(p, "1111");	//err 空指针

	char* q = 0x1122;		//野指针,不可读取，不可访问
	//给q所指内存区域拷贝内容
	//strcpy(q, "2222");

	//p = 0x001;
	//printf("%d\n", p);
	//*p = 100;
}



//间接访问操作符

void VisitOperatorTest() {

	int* p = NULL;
	int a = 10;

	p = &a;
	*p = 100;
	int b = *p;

	char* str = "hello world!";	//err 常量区，不可更改
	//*str = 'm';

	printf("a:%d\n", a);
	printf("*p:%d\n", *p);
	printf("b:%d\n", b);
	printf("str:%s\n", str);
}


//指针的步长
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
	printf("%x\n", *p2);	//dd-小段模式

	printf("%x\n", p1);
	printf("%x\n", p1+1);

	printf("%x\n", p2);
	printf("%x\n", p2+1);


	Person p = { 'a',10,"Hello World",1000 };

	//p中d属性偏移量是多少
	printf("d的偏移量为：%d\n", offsetof(Person, d));

	printf("d的值为：%d\n", *(int*)((char*)&p + offsetof(Person, d)));



}