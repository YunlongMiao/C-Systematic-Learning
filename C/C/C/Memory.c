#define   _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int e;
static int f;
int g = 10;
static int h = 10;

//各种变量存储位置
void AddrNum()
{
	int a;
	int b = 10;
	static int c;
	static int d = 10;
	char* i = "test";
	char* k = NULL;

	printf("&a\t %p\t //局部未初始化变量\n", &a);
	printf("&b\t %p\t //局部初始化变量\n", &b);

	printf("&c\t %p\t //静态局部未初始化变量\n", &c);
	printf("&d\t %p\t //静态局部初始化变量\n", &d);

	printf("&e\t %p\t //全局未初始化变量\n", &e);
	printf("&f\t %p\t //全局静态未初始化变量\n", &f);

	printf("&g\t %p\t //全局初始化变量\n", &g);
	printf("&h\t %p\t //全局静态初始化变量\n", &h);

	printf("i\t %p\t //只读数据(文字常量区)\n", i);

	k = (char*)malloc(10);
	printf("k\t %p\t //动态分配的内存\n", k);

	return 0;
}


//内存设置
void Memoryset() {

	int a = 10;
	char buf[10] = "";

	strcpy(buf, "hello");
	printf("%s\n", buf);

	memset(&a, 0, sizeof(a));
	printf("%d\n", a);

	memset(buf, 0, sizeof(buf));
	printf("%s\n", buf);

	memset(buf, 'a', sizeof(buf)-1);
	printf("%s\n", buf);

	memset(buf, '0', sizeof(buf) - 9);
	printf("%s\n", buf);
}

//内存拷贝 memcpy
void Memorycpy() {

	int i = 0;
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int b[10] = { 0 };

	char str1[128] = "";
	char str2[128] = "abc\0def\0dadfa";


	printf("memcpy：");
	memcpy(b, a, sizeof(int) * 5);
	for (i=0; i<sizeof(b)/sizeof(b[0]); i++)
		printf("%d ",b[i]);
	printf("\n");


	printf("memcpy： ");
	memcpy(str1, str2, sizeof(char) * 10);
	for (i = 0; i < 10; i++)
		printf("%d ", str1[i]);
	printf("\n");

	 
	//与memcpy相比，strncpy遇0折断
	printf("strncpy：");
	strncpy(str1, str2, sizeof(char) * 10);
	for (i = 0; i < 10; i++)
		printf("%d ", str1[i]);
	printf("\n");
}


//memmov


//内存比较 memcmp
void Memorycmp() {

	char num1[] = { 1,3,3,4,5,6,7 };
	char num2[] = { 1,2,3,4,5,6,7 };

	char str1[] = "asdf\0qwer";
	char str2[] = "asdf\0zwer";

	printf("%d\n", memcmp(num1, num2, sizeof(char) * 7));

	printf("%d\n", memcmp(str1, str2, sizeof(str1)));

	//与memcmp相比，strncmp遇0折断
	printf("%d\n", strncmp(str1, str2, sizeof(str1)));
}


//内存申请释放 malloc free
void MemoryMalloc() {

	int i; 

	//申请一个数组，数组有10个元素，int类型
	int *p = (int*)malloc(sizeof(int)*10);
	memset(p, 0, 10);
	*p = 1000;
	*(p + 5) = 50;
	for (i = 0; i < 10; i++)
		printf("%d ", *(p+i));
	free(p);
	printf("\n");

	char* q = malloc(1024);
	memset(q, 0, 1024);
	strncpy(q, "helloworld");
	printf("%s\n", q);
	free(q);
}

//MemoryAddrTest
#if 1
//返回变量地址
int *MemoryAddr() {

	//int p = 10;			//局部变量在函数运行结束后释放空间，解决方法：static变量
	static int p = 10;		//静态变量可以一直存在，直至程序结束
	p *= 10;
	return &p;
}
void MemoryAddrTest() {

	int* p = MemoryAddr();
	printf("%d\n", *p);
	*p = 1000;              //err: p所指的空间已经释放
	printf("%d\n", *p);
}

#endif


//MemoryHeapTest
#if 1	
//堆区地址
int *MemoryHeap1(int num) {

	num += 100;
	return &num;
}

int* MemoryHeap2(int *num) {

	*num += 102;
	return num;
}

char* MemoryHeap3() {

	char* q = malloc(100);
	return q;
}

void MemoryHeapTest() {

	int num = 10;

//MemoryHeap1:
 
	//int *p = MemoryHeap1(num);      //err: 不可以返回形参地址
	//*p = 1000;
	//printf("%d\n", *p);

//MemoryHeap2:

	//int* p = MemoryHeap2(&num);    //可以，函数实际操作的是num的地址
	//*p = 1000;
	//printf("%d\n", *p);


//MemoryHeap3:

	char* p = MemoryHeap3();    //malloc申请的堆区不会释放，可以传递

	/*但是这句话有问题，字符串地址传递的过程中会把字符串首地址传递给p,
	 这使得p的地址不再指向malloc申请的地址，出现错误*/
	//*p = "hello";		//err	
	strcpy(p, "hello");	//正确做法
	printf("%s\n", p);	//字符串，不需要*p,直接传递首地址
	free(p);

}

#endif



//内存污染
char* MemoryPollution(char *q) {

	q = malloc(1024);
	return q;
}

void MemoryPollution1(char** K) {

	*K = malloc(1024);	//*K是  *p = NULL 的地址
}

void MemoryPollutionTest() {

	char* p = NULL;

	//err:通过函数的值传递，不能改变实参的值，
	
	//MemoryPollution(p);

	//p = MemoryPollution(p);	//正确方法：p接受malloc申请的地址
	//strcpy(p, "hello");
	//printf("%s\n", p);


	//传实参的地址，可以在调用的时候改变实参的值

	MemoryPollution1(&p);	//另一种方式，二级指针
	strcpy(p, "hello");
	printf("%s\n", p);

}