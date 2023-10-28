#include "dynamicArray.h"
#include "seqQueue.h"




//初始化数组  参数 初始数组容量   返回值 数组指针
struct dynamicArray* init_dynamicArray(int capacity) {

	if (capacity <= 0)
		return NULL;

	//给数组分配指针
	struct dynamicArray* arr = malloc(sizeof(struct dynamicArray));

	if (arr == NULL)
		return NULL;

	//给属性初始化
	arr->pAddr = malloc(sizeof(void*) * capacity);
	//容量初始化
	arr->m_Capacity = capacity;
	//大小初始化
	arr->m_Size = 0;

	return arr;
}



//插入元素
void insert_dynamicArray(struct dynamicArray* arr, void* data, int pos)
{

	if (arr == NULL)
		return;
	if (data == NULL)
		return;

	if (pos<0 || pos>arr->m_Size)
		pos = arr->m_Size;	//无效的位置  尾插

	//判断是否有空间进行插入，如果没有空间了，那么动态扩展
	if (arr->m_Size >= arr->m_Capacity)
	{
		//1、计算申请空间大小
		int newCapacity = arr->m_Capacity * 2;

		//2、创建新空间
		void** newSpace = malloc(sizeof(void*) * newCapacity);

		//3、 将原有数据拷贝到新空间下
		memcpy(newSpace, arr->pAddr, sizeof(void*) * arr->m_Capacity);

		//4、 释放原有空间
		free(arr->pAddr);

		//5、 更新指针的指向
		arr->pAddr = newSpace;

		//6、更新新数组容量
		arr->m_Capacity = newCapacity;
	}


	//插入数据

	for (int i = arr->m_Size - 1; i >= pos; i--)
	{
		//数据后移
		arr->pAddr[i + 1] = arr->pAddr[i];
	}
	//将新数据放入到指定位置中
	arr->pAddr[pos] = data;


	//更新数组大小
	arr->m_Size++;
}



//遍历数组
void foreach_dynamicArray(struct dynamicArray* arr, void(*myPrint)(void*))
{
	if (arr == NULL)
	{
		return;
	}

	if (myPrint == NULL)
	{
		return;
	}

	for (int i = 0; i < arr->m_Size; i++)
	{
		myPrint(arr->pAddr[i]);
	}
}


//删除数组
void removeByPos_dynamicArray(struct dynamicArray* arr, int pos)
{
	if (arr == NULL)
	{
		return;
	}

	//无效位置 就直接return
	if (pos < 0 || pos >arr->m_Size - 1)
	{
		return;
	}

	//移动数据
	for (int i = pos; i < arr->m_Size - 1; i++)
	{
		arr->pAddr[i] = arr->pAddr[i + 1];
	}

	//更新大小
	arr->m_Size--;

}

//按照值 来删除数组中数据
void removeByValue_dynamicArray(struct dynamicArray* arr, void* data, int(*myCompare)(void*, void*))
{
	if (arr == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	for (int i = 0; i < arr->m_Size; i++)
	{
		if (myCompare(arr->pAddr[i], data))
		{
			//如果对比成功了，那么要删除i下标的元素
			removeByPos_dynamicArray(arr, i);
			break;
		}
	}


}

//销毁数组
void destroy_dynamicArray(struct dynamicArray* arr)
{

	if (arr == NULL)
	{
		return;
	}

	if (arr->pAddr != NULL)
	{
		free(arr->pAddr);
		arr->pAddr = NULL;
	}


	free(arr);
	arr = NULL;

}


/*
测试
*/


struct Person
{
	char name[64];
	int age;
};



//void myPrint(void* data, void(*mp)(void*)) {
//
//	mp(data);
//
//}

void printInt(void* data) {

	int* num = data;
	printf("%d\n", *num);
}

void printDouble(void* data) {

	double* num = data;
	printf("%f\n", *num);
}

void printPerson(void* data) {

	struct Person* person = (struct Person*)data;
	printf("姓名：%s 年龄：%d\n", person->name, person->age);
}

int comparaPerson(void* data1, void* data2) {

	struct Person* p1 = data1;
	struct Person* p2 = data2;

	if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age)
		return 1;
	return 0;
}


void test01() {


	//初始化动态数组
	struct dynamicArray* arr = init_dynamicArray(5);

	//准备数据
	struct Person p1 = { "刘备", 10 };
	struct Person p2 = { "张飞", 20 };
	struct Person p3 = { "关羽", 30 };
	struct Person p4 = { "赵云", 40 };
	struct Person p5 = { "曹操", 50 };
	struct Person p6 = { "猪脚亮", 50 };

	printf("插入数据前---数组容量：%d\n", arr->m_Capacity);
	printf("插入数据前---数组大小：%d\n", arr->m_Size);

	//插入数据
	insert_dynamicArray(arr, &p1, 0);
	insert_dynamicArray(arr, &p2, 0);
	insert_dynamicArray(arr, &p3, 1);
	insert_dynamicArray(arr, &p4, -1);
	insert_dynamicArray(arr, &p5, 0);
	insert_dynamicArray(arr, &p6, 0);

	//猪，曹，张，关，刘，赵
	foreach_dynamicArray(arr, printPerson);

	printf("插入数据后---数组容量：%d\n", arr->m_Capacity);
	printf("插入数据后---数组大小：%d\n", arr->m_Size);

	//按照位置 删除诸葛想测试
	removeByPos_dynamicArray(arr, 0);
	foreach_dynamicArray(arr, printPerson);

	//按值删除数据，删除刘备
	removeByValue_dynamicArray(arr, &p1, comparaPerson);
	printf("删除刘备后遍历结果：\n");
	foreach_dynamicArray(arr, printPerson);

	//测试销毁
	destroy_dynamicArray(arr);
	arr = NULL;
}























/*
链表
*/

//初始化队列
seqQueue init_SeqQueue()
{
	struct dynamicArray* array = init_dynamicArray(MAX);

	return array;
}
//入队
void push_SeqQueue(seqQueue queue, void* data)
{
	//等价于 尾插
	if (queue == NULL)
	{
		return;
	}
	if (data == NULL)
	{
		return;
	}

	struct dynamicArray* array = queue;

	if (array->m_Size >= MAX)
	{
		return;
	}

	insert_dynamicArray(array, data,array->m_Size);
}
//出队
void pop_SeqQueue(seqQueue queue)
{
	//等价于  头删除
	if (queue == NULL)
	{
		return;
	}

	struct dynamicArray* array = queue;

	if (array->m_Size <= 0)
	{
		return;
	}
	removeByPos_dynamicArray(array, 0);
}
//返回队头元素
void* front_SeqQueue(seqQueue queue)
{
	if (queue == NULL)
	{
		return NULL;
	}

	struct dynamicArray* array = queue;

	return array->pAddr[0];

}

//返回队尾元素
void* back_SeqQueue(seqQueue queue)
{
	if (queue == NULL)
	{
		return NULL;
	}

	struct dynamicArray* array = queue;

	return array->pAddr[array->m_Size - 1];

}

//队列大小
int size_SeqQueue(seqQueue queue)
{
	if (queue == NULL)
	{
		return -1;
	}

	struct dynamicArray* array = queue;

	return array->m_Size;

}

//判断是否为空
int isEmpty_SeqQueue(seqQueue queue)
{
	if (queue == NULL)
	{
		return -1;
	}

	struct dynamicArray* array = queue;
	if (array->m_Size == 0)
	{
		return 1;
	}

	return 0;
}

//销毁队列
void destroy_SeqQueue(seqQueue queue)
{

	if (queue == NULL)
	{
		return;
	}

	destroy_dynamicArray(queue);
	queue = NULL;
}











void test02()
{
	//初始化队列
	seqQueue myQueue = init_SeqQueue();

	//准备数据
	struct Person p1 = { "aaa", 10 };
	struct Person p2 = { "bbb", 20 };
	struct Person p3 = { "ccc", 30 };
	struct Person p4 = { "ddd", 40 };
	struct Person p5 = { "eee", 50 };

	//入队
	push_SeqQueue(myQueue, &p1);
	push_SeqQueue(myQueue, &p2);
	push_SeqQueue(myQueue, &p3);
	push_SeqQueue(myQueue, &p4);
	push_SeqQueue(myQueue, &p5);

	printf("队列大小为：%d\n", size_SeqQueue(myQueue));

	while (isEmpty_SeqQueue(myQueue) == 0)
	{
		//队头元素
		struct Person* pFront = front_SeqQueue(myQueue);
		printf("队头元素姓名：%s 年龄：%d \n", pFront->name, pFront->age);

		//队尾元素
		struct Person* pBack = back_SeqQueue(myQueue);
		printf("队尾元素姓名：%s 年龄：%d \n", pBack->name, pBack->age);

		//出队
		pop_SeqQueue(myQueue);
	}

	printf("队列大小为：%d\n", size_SeqQueue(myQueue));

	//销毁队列
	destroy_SeqQueue(myQueue);
	myQueue = NULL;
}