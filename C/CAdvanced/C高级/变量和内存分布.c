#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	//标准输入输出
#include<string.h>	//字符串处理函数
#include<stdlib.h>	//标准库函数
/*
数据类型别名：typedef
*/

typedef unsigned int u32;

typedef struct PERSON {

	char name[64];
	u32 age;
}Person;

void TypedefTest() {

	Person person = { "世间美好皆于此",57 };

	printf("%s %u\n", person.name, person.age);
}


/*
void数据类型
*/

void VoidTest(void) {	//void修饰函数参数和函数返回

/*不能定义void类型变量 err*/

	//void val;		

/*void可以指向任意类型数据，称为万能指针*/

	//int
	int a = 10;
	void* p = NULL;
	p = &a;
	printf("(int)%d\n", *(int*)p);

	//char
	char b = 'a';
	p = &b;
	printf("(char)%c\n", *(char*)p);

/*void* 常用于数据类型的封装，可以返回任意类型的数据*/

	//函数：memcpy
	//void* memcpy(void* _Dst, const void* _Src, size_t _Size);

}

/*
sizeof操作符
*/

void Test58(int array[]) {

	printf("Testarr size:%d\n", sizeof array);

}
void SizeofTest(){

//基础用法
	int a = 10;
	printf("len:%d\n", sizeof(a));
	printf("len:%d\n", sizeof(int));
	printf("len:%d\n", sizeof a);

//sizeof结果类型
	unsigned int b = 10;

	if (b - 11 < 0)
		printf("结果小于0\n");
	else
		printf("结果大于0\n");	//unsigned int 运算结果为unsigned int

	int c = 5;
	if (sizeof(c) - 10 < 0)
		printf("结果小于0\n");
	else
		printf("结果大于0\n");	//sizeof返回值类型为unsigned int

	int arr[] = { 10,20,30,40,50 };
	printf("arr size:%d\n", sizeof arr);

	//数组名在某些情况下等价于指针
	int* parr = arr;
	printf("arr[2]:%d\n", parr[2]);
	printf("arr size:%d\n", sizeof parr);

	//数组做函数函数参数，将退化为指针,在函数内部不再返回数组大小
	Test58(arr);
}



/*
修改变量的两种方式
*/
void VariableTest() {

	int a = 10;

	//直接修改
	a = 20;
	printf("直接修改%d\n", a);

	//间接修改
	int* p = &a;
	*p = 100;
	printf("间接修改%d\n", a);
}


/*
内存分区模型-栈区
*/

char* func121() {

	char a[] = "Hello World";	//在栈区存储，乱码

	printf("子函数：%s\n", a);
	return a;
}

void StackAreaTest() {

	char* p = NULL;

	p = func121();
	printf("主函数：%s\n", p);
}



/*
内存分区模型-堆区
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
	func150(&p);		//空指针赋值方法
	printf("%s\n", p);
	free(p);
}




/*
calloc:在内存动态存储区中分配nmemb块长度为size字节的连续区域。
		calloc自动将分配的内存置0。
realloc:重新分配用malloc或者calloc函数在堆中分配内存空间的大小
*/

void CallocReallocTest() {

	int* p = calloc(10, sizeof(int));
	if (p == NULL)
		return;
	for (int i = 0; i < 10; i++)	//赋值
		p[i] = i + 1;

	for (int i = 0; i < 10; i++)	//打印
		printf("calloc Test p[%d]=%d\n", i, p[i]);
	printf("\n\n");

	int* p1 = realloc(p, 15 * sizeof(int));
	if (p1 == NULL)
		return;

	printf("\tp地址:%d\tp1地址%d\n\n", p, p1);
	printf("\n\n");
	for (int i = 0; i < 15; i++)	//打印
		printf("realloc Test I p1[%d]=%d\n", i, p1[i]);
	printf("\n\n");
	for (int i = 10; i < 15; i++)	//赋剩余值
		p1[i] = i + 1;

	for (int i = 0; i < 15; i++)	//打印
		printf("realloc Test II p1[%d]=%d\n", i, p1[i]);
	free(p1);
}


/*
栈的生长方向和内存存放方向
*/

void StackDirectionTest() {

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;

	printf("a = %d\n", &a);
	printf("b = %d\n", &b);
	printf("c = %d\n", &c);
	printf("d = %d\n", &d);

	//a的地址小于b的地址，生长方向向上？？
}

void MemoryDirectionTest() {

	int num = 0xaabbccdd;
	unsigned char* p = &num;

	printf("%x\n", *p);
	printf("%x\n", *(p+1));
	printf("%x\n", *(p+2));
	printf("%x\n", *(p+3));

	//小端模式？
}
void StackMemoryDirection() {

	StackDirectionTest();	//栈的生长方向
	MemoryDirectionTest();	//内存生长方向
}