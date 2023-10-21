#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "linklist.h"


/*
链表操作
*/

//初始化链表
struct LinkNode* init_LinkList() {

	
	struct LinkNode* pHeader = malloc(sizeof(struct LinkNode));
	if (pHeader == NULL)
		return NULL;

	//头节点不维护数据域
	pHeader->num = -1;
	pHeader->next = NULL;


	//创建尾节点指针 用户记录当前链表尾部节点位置，方便做尾插
	struct LinkNode* pTail = pHeader;
	int val = -1;

	while (1) {

		printf("插入数据，-1结束\n");
		scanf("%d", &val);

		if (val == -1)
			break;

		//创建新节点
		struct LinkNode* newNode = malloc(sizeof(struct LinkNode));
		newNode->num = val;
		newNode->next = NULL;

		//更新结点指向
		pTail->next = newNode;
		pTail = newNode;
	}

	//返回头节点
	return pHeader;
}


//遍历链表
void foreach_LinkList(struct LinkNode* pHeader) {

	if (pHeader == NULL)
		return;

	//当前节点 指向第一个有真实数据节点
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL)
	{
		printf("%d\n", pCurrent->num);
		pCurrent = pCurrent->next;
	}
	printf("\n\n");

}


//节点插入
void insert_LinkList(struct LinkNode* pHeader,int addNum,int newNum) {

	if (pHeader == NULL)
		return;

	struct LinkNode* pPrev = pHeader;
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL) {

		if (pCurrent->num == addNum)
			break;

		//辅助指针向后移动
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}

	//创建新节点
	struct LinkNode* newNode = malloc(sizeof(struct LinkNode));
	newNode->num = newNum;
	newNode->next = NULL;

	//更改指针指向
	newNode->next = pCurrent;
	pPrev->next = newNode;
}


//节点删除
void delect_LinkList(struct LinkNode* pHeader,int delVal) {

	if (pHeader == NULL)
		return;

	//创建临时节点
	struct LinkNode* pPrev = pHeader;
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL) {

		if (pCurrent->num == delVal)
			break;

		//辅助指针向后移动
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}
	if (pCurrent == NULL)
		return;

	//更改指针指向
	pPrev->next = pCurrent->next;

	//删除节点
	free(pCurrent);
	pCurrent = NULL;
}



//清空链表
void clear_LinkList(struct LinkNode* pHeader) {

	if (pHeader == NULL)
		return;

	//创建临时节点
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL) {

		//记录下一个节点位置
		struct LinkNode* nextList = pCurrent->next;
		//释放节点
		free(pCurrent);
		pCurrent = nextList;
	}
	//头节点置空
	pHeader->next = NULL;
}

//销毁链表
void destroy_LinkList(struct LinkNode* pHeader) {

	if (pHeader == NULL)
		return;

	//清空链表
	clear_LinkList(pHeader);

	free(pHeader);
	pHeader = NULL;
}

void linkListTest() {

	//链表初始化
	printf("链表初始化\n");
	struct LinkNode* pHeader = init_LinkList();

	//遍历链表
	printf("遍历链表\n");
	foreach_LinkList(pHeader);

	//插入节点测试
	printf("插入节点测试\n");
	insert_LinkList(pHeader, 30, 200);
	insert_LinkList(pHeader, 50, 250);
	foreach_LinkList(pHeader);

	//删除节点测试
	printf("删除节点测试\n");
	delect_LinkList(pHeader, 30);
	foreach_LinkList(pHeader);

	//清空链表
	printf("清空链表\n");
	clear_LinkList(pHeader);

	//销毁链表
	printf("销毁链表\n");
	destroy_LinkList(pHeader);

}




/*
函数指针：由于VS每次程序分配地址不同，不可用
*/

void func(int a,char b) {

	printf("%d.%c:函数指针测试\n",a,b);
}
void func2(int a, char b) {

	printf("%d.%c:函数指针测试，挺抽象的\n", a, b);
}

void funcPoint() {

	int addr = func;	//不可打印
	int* p = (int*)addr;

	func(215,'q');

	//函数指针指向函数地址
	void (*pFunc218)(int,char) = (void (*)(int,char))p;
	pFunc218(219,'w');

	//第一种定义方式：先定义函数类型，再通过类型定义函数指针变量
	typedef void(FUNC_TYPE222)(int, char);//定义一个函数类型，返回值void 形参列表（int,char）
	FUNC_TYPE222* pFunc223 = func;
	pFunc223(224, 'e');

	//第二种定义方式：先定义函数指针的类型 ，再通过类型定义函数指针变量
	typedef void(*FUNC_TYPE227)(int, char);
	FUNC_TYPE227 pFunc228 = func;
	pFunc223(229, 'r');

	//第三种定义方式：直接定义函数指针变量
	//void(__cdecl *)(int,char)  == void func(int a, char b)
	void(*p233)(int, char) = func;
	p233(234, 't');

	//第四种定义方式：函数指针数组定义方式
	void(*func_array[2])(int, char);
	func_array[0] = func;
	func_array[1] = func2;

	func_array[0](246, 'y');
	func_array[1](247, 'u');


}




/*
回调函数-类型
*/

void myPrint(void* data, void(*mp)(void*)) {

	mp(data);
}

struct Person {

	char name[64];
	int age;
};

void printInt(void* data) {

	int* num = data;
	printf("%d\n", *num);
}

void printDouble(void* data) {

	double* num = data;
	printf("%f\n", *num);
}

void printPerson(void* data) {

	struct Person* num = data;
	printf("姓名：%s 年龄：%d\n", num->name,num->age);
}


void callBackTypeTest() {

	int a = 10;
	myPrint(&a, printInt);

	struct Person person = { "形成万幸",51 };
	myPrint(&person, printPerson);
}


/*
回调函数-数组
*/

void printAllArray(void* arr,int eleSize, int len,void(*myArrayPrint)(void*)) {

	//获得数组首地址
	char* p = arr;
	for (int i = 0; i < len; i++) {
		//获得每个数组元素首地址
		char* pAddr = p + eleSize * i;

		myArrayPrint(pAddr);
	}
}

void printArrayInt(void* data) {

	int* num = data;
	printf("%d\n", *num);
}

void printArrayMyPerson(void* data) {

	struct Person* num = data;
	printf("姓名：%s 年龄：%d\n", num->name, num->age);

}

void callBackArrayTest() {

	int arr[] = { 1,2,3,4,5,6 };
	int eleSize = sizeof(int);
	int len = sizeof(arr) / sizeof(arr[0]);
	printAllArray(arr, eleSize, len, printArrayInt);

	struct Person personArray[] = {
		{"战胜",56},
		{"塞尔达",645},
		{"艾迪芬奇",61}
	};
	eleSize = sizeof(struct Person);
	len = sizeof(personArray) / sizeof(personArray[0]);
	printAllArray(personArray, eleSize, len, printArrayMyPerson);
}



/*
回调函数-查找数组
*/

int findArrayEle(void* arr, int eleSize, int len, void* data,int(*myCompare)(void*,void*)) {

	//获得数组首地址
	char* p = arr;
	for (int i = 0; i < len; i++) {
		//获得每个数组元素首地址
		char* pAddr = p + eleSize * i;

		//if（用户传入数据 == 数组中遍历数据）
		//if (data == pAddr)	err不可使用地址直接进行比较
		if(myCompare(data, pAddr))
			return 1;
	}
	return 0;
}

int comparaPerson(void* data1,void* data2) {

	struct Person* p1 = data1;
	struct Person* p2 = data2;

	if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age)
		return 1;
	return 0;
}

int comparaInt(void* data1, void* data2) {

	int* num1 = data1;
	int* num2 = data2;

	if (*num1 == *num2)
		return 1;
	return 0;
}



void callBackFindArrayTest() {

	int arr[] = { 1,2,3,4,5,6 };
	int eleSize = sizeof(int);
	int len = sizeof(arr) / sizeof(arr[0]);
	int a = 2;
	int tem = -1;
	tem = findArrayEle(arr, eleSize, len, &a, comparaInt);
	if (tem)
		printf("数组arr\t找到元素\n");
	else
		printf("数组arr\t没有找到元素\n");
	tem = -1;



	struct Person personArray[] = {
		{"战胜",56},
		{"塞尔达",645},
		{"艾迪芬奇",61}
	};
	struct Person p = { "艾迪芬奇",61 };
	eleSize = sizeof(struct Person);
	len = sizeof(personArray) / sizeof(personArray[0]);
	tem = findArrayEle(personArray, eleSize, len, &p, comparaPerson);
	if (tem)
		printf("数组personArray\t找到元素\n");
	else
		printf("数组personArray\t没有找到元素\n");
	tem = -1;
}
