#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "linklist.h"


/*
�������
*/

//��ʼ������
struct LinkNode* init_LinkList() {

	
	struct LinkNode* pHeader = malloc(sizeof(struct LinkNode));
	if (pHeader == NULL)
		return NULL;

	//ͷ�ڵ㲻ά��������
	pHeader->num = -1;
	pHeader->next = NULL;


	//����β�ڵ�ָ�� �û���¼��ǰ����β���ڵ�λ�ã�������β��
	struct LinkNode* pTail = pHeader;
	int val = -1;

	while (1) {

		printf("�������ݣ�-1����\n");
		scanf("%d", &val);

		if (val == -1)
			break;

		//�����½ڵ�
		struct LinkNode* newNode = malloc(sizeof(struct LinkNode));
		newNode->num = val;
		newNode->next = NULL;

		//���½��ָ��
		pTail->next = newNode;
		pTail = newNode;
	}

	//����ͷ�ڵ�
	return pHeader;
}


//��������
void foreach_LinkList(struct LinkNode* pHeader) {

	if (pHeader == NULL)
		return;

	//��ǰ�ڵ� ָ���һ������ʵ���ݽڵ�
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL)
	{
		printf("%d\n", pCurrent->num);
		pCurrent = pCurrent->next;
	}
	printf("\n\n");

}


//�ڵ����
void insert_LinkList(struct LinkNode* pHeader,int addNum,int newNum) {

	if (pHeader == NULL)
		return;

	struct LinkNode* pPrev = pHeader;
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL) {

		if (pCurrent->num == addNum)
			break;

		//����ָ������ƶ�
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}

	//�����½ڵ�
	struct LinkNode* newNode = malloc(sizeof(struct LinkNode));
	newNode->num = newNum;
	newNode->next = NULL;

	//����ָ��ָ��
	newNode->next = pCurrent;
	pPrev->next = newNode;
}


//�ڵ�ɾ��
void delect_LinkList(struct LinkNode* pHeader,int delVal) {

	if (pHeader == NULL)
		return;

	//������ʱ�ڵ�
	struct LinkNode* pPrev = pHeader;
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL) {

		if (pCurrent->num == delVal)
			break;

		//����ָ������ƶ�
		pPrev = pCurrent;
		pCurrent = pCurrent->next;
	}
	if (pCurrent == NULL)
		return;

	//����ָ��ָ��
	pPrev->next = pCurrent->next;

	//ɾ���ڵ�
	free(pCurrent);
	pCurrent = NULL;
}



//�������
void clear_LinkList(struct LinkNode* pHeader) {

	if (pHeader == NULL)
		return;

	//������ʱ�ڵ�
	struct LinkNode* pCurrent = pHeader->next;

	while (pCurrent != NULL) {

		//��¼��һ���ڵ�λ��
		struct LinkNode* nextList = pCurrent->next;
		//�ͷŽڵ�
		free(pCurrent);
		pCurrent = nextList;
	}
	//ͷ�ڵ��ÿ�
	pHeader->next = NULL;
}

//��������
void destroy_LinkList(struct LinkNode* pHeader) {

	if (pHeader == NULL)
		return;

	//�������
	clear_LinkList(pHeader);

	free(pHeader);
	pHeader = NULL;
}

void linkListTest() {

	//�����ʼ��
	printf("�����ʼ��\n");
	struct LinkNode* pHeader = init_LinkList();

	//��������
	printf("��������\n");
	foreach_LinkList(pHeader);

	//����ڵ����
	printf("����ڵ����\n");
	insert_LinkList(pHeader, 30, 200);
	insert_LinkList(pHeader, 50, 250);
	foreach_LinkList(pHeader);

	//ɾ���ڵ����
	printf("ɾ���ڵ����\n");
	delect_LinkList(pHeader, 30);
	foreach_LinkList(pHeader);

	//�������
	printf("�������\n");
	clear_LinkList(pHeader);

	//��������
	printf("��������\n");
	destroy_LinkList(pHeader);

}




/*
����ָ�룺����VSÿ�γ�������ַ��ͬ��������
*/

void func(int a,char b) {

	printf("%d.%c:����ָ�����\n",a,b);
}
void func2(int a, char b) {

	printf("%d.%c:����ָ����ԣ�ͦ�����\n", a, b);
}

void funcPoint() {

	int addr = func;	//���ɴ�ӡ
	int* p = (int*)addr;

	func(215,'q');

	//����ָ��ָ������ַ
	void (*pFunc218)(int,char) = (void (*)(int,char))p;
	pFunc218(219,'w');

	//��һ�ֶ��巽ʽ���ȶ��庯�����ͣ���ͨ�����Ͷ��庯��ָ�����
	typedef void(FUNC_TYPE222)(int, char);//����һ���������ͣ�����ֵvoid �β��б�int,char��
	FUNC_TYPE222* pFunc223 = func;
	pFunc223(224, 'e');

	//�ڶ��ֶ��巽ʽ���ȶ��庯��ָ������� ����ͨ�����Ͷ��庯��ָ�����
	typedef void(*FUNC_TYPE227)(int, char);
	FUNC_TYPE227 pFunc228 = func;
	pFunc223(229, 'r');

	//�����ֶ��巽ʽ��ֱ�Ӷ��庯��ָ�����
	//void(__cdecl *)(int,char)  == void func(int a, char b)
	void(*p233)(int, char) = func;
	p233(234, 't');

	//�����ֶ��巽ʽ������ָ�����鶨�巽ʽ
	void(*func_array[2])(int, char);
	func_array[0] = func;
	func_array[1] = func2;

	func_array[0](246, 'y');
	func_array[1](247, 'u');


}




/*
�ص�����-����
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
	printf("������%s ���䣺%d\n", num->name,num->age);
}


void callBackTypeTest() {

	int a = 10;
	myPrint(&a, printInt);

	struct Person person = { "�γ�����",51 };
	myPrint(&person, printPerson);
}


/*
�ص�����-����
*/

void printAllArray(void* arr,int eleSize, int len,void(*myArrayPrint)(void*)) {

	//��������׵�ַ
	char* p = arr;
	for (int i = 0; i < len; i++) {
		//���ÿ������Ԫ���׵�ַ
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
	printf("������%s ���䣺%d\n", num->name, num->age);

}

void callBackArrayTest() {

	int arr[] = { 1,2,3,4,5,6 };
	int eleSize = sizeof(int);
	int len = sizeof(arr) / sizeof(arr[0]);
	printAllArray(arr, eleSize, len, printArrayInt);

	struct Person personArray[] = {
		{"սʤ",56},
		{"������",645},
		{"���Ϸ���",61}
	};
	eleSize = sizeof(struct Person);
	len = sizeof(personArray) / sizeof(personArray[0]);
	printAllArray(personArray, eleSize, len, printArrayMyPerson);
}



/*
�ص�����-��������
*/

int findArrayEle(void* arr, int eleSize, int len, void* data,int(*myCompare)(void*,void*)) {

	//��������׵�ַ
	char* p = arr;
	for (int i = 0; i < len; i++) {
		//���ÿ������Ԫ���׵�ַ
		char* pAddr = p + eleSize * i;

		//if���û��������� == �����б������ݣ�
		//if (data == pAddr)	err����ʹ�õ�ֱַ�ӽ��бȽ�
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
		printf("����arr\t�ҵ�Ԫ��\n");
	else
		printf("����arr\tû���ҵ�Ԫ��\n");
	tem = -1;



	struct Person personArray[] = {
		{"սʤ",56},
		{"������",645},
		{"���Ϸ���",61}
	};
	struct Person p = { "���Ϸ���",61 };
	eleSize = sizeof(struct Person);
	len = sizeof(personArray) / sizeof(personArray[0]);
	tem = findArrayEle(personArray, eleSize, len, &p, comparaPerson);
	if (tem)
		printf("����personArray\t�ҵ�Ԫ��\n");
	else
		printf("����personArray\tû���ҵ�Ԫ��\n");
	tem = -1;
}
