#include "dynamicArray.h"
#include "seqQueue.h"




//��ʼ������  ���� ��ʼ��������   ����ֵ ����ָ��
struct dynamicArray* init_dynamicArray(int capacity) {

	if (capacity <= 0)
		return NULL;

	//���������ָ��
	struct dynamicArray* arr = malloc(sizeof(struct dynamicArray));

	if (arr == NULL)
		return NULL;

	//�����Գ�ʼ��
	arr->pAddr = malloc(sizeof(void*) * capacity);
	//������ʼ��
	arr->m_Capacity = capacity;
	//��С��ʼ��
	arr->m_Size = 0;

	return arr;
}



//����Ԫ��
void insert_dynamicArray(struct dynamicArray* arr, void* data, int pos)
{

	if (arr == NULL)
		return;
	if (data == NULL)
		return;

	if (pos<0 || pos>arr->m_Size)
		pos = arr->m_Size;	//��Ч��λ��  β��

	//�ж��Ƿ��пռ���в��룬���û�пռ��ˣ���ô��̬��չ
	if (arr->m_Size >= arr->m_Capacity)
	{
		//1����������ռ��С
		int newCapacity = arr->m_Capacity * 2;

		//2�������¿ռ�
		void** newSpace = malloc(sizeof(void*) * newCapacity);

		//3�� ��ԭ�����ݿ������¿ռ���
		memcpy(newSpace, arr->pAddr, sizeof(void*) * arr->m_Capacity);

		//4�� �ͷ�ԭ�пռ�
		free(arr->pAddr);

		//5�� ����ָ���ָ��
		arr->pAddr = newSpace;

		//6����������������
		arr->m_Capacity = newCapacity;
	}


	//��������

	for (int i = arr->m_Size - 1; i >= pos; i--)
	{
		//���ݺ���
		arr->pAddr[i + 1] = arr->pAddr[i];
	}
	//�������ݷ��뵽ָ��λ����
	arr->pAddr[pos] = data;


	//���������С
	arr->m_Size++;
}



//��������
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


//ɾ������
void removeByPos_dynamicArray(struct dynamicArray* arr, int pos)
{
	if (arr == NULL)
	{
		return;
	}

	//��Чλ�� ��ֱ��return
	if (pos < 0 || pos >arr->m_Size - 1)
	{
		return;
	}

	//�ƶ�����
	for (int i = pos; i < arr->m_Size - 1; i++)
	{
		arr->pAddr[i] = arr->pAddr[i + 1];
	}

	//���´�С
	arr->m_Size--;

}

//����ֵ ��ɾ������������
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
			//����Աȳɹ��ˣ���ôҪɾ��i�±��Ԫ��
			removeByPos_dynamicArray(arr, i);
			break;
		}
	}


}

//��������
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
����
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
	printf("������%s ���䣺%d\n", person->name, person->age);
}

int comparaPerson(void* data1, void* data2) {

	struct Person* p1 = data1;
	struct Person* p2 = data2;

	if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age)
		return 1;
	return 0;
}


void test01() {


	//��ʼ����̬����
	struct dynamicArray* arr = init_dynamicArray(5);

	//׼������
	struct Person p1 = { "����", 10 };
	struct Person p2 = { "�ŷ�", 20 };
	struct Person p3 = { "����", 30 };
	struct Person p4 = { "����", 40 };
	struct Person p5 = { "�ܲ�", 50 };
	struct Person p6 = { "�����", 50 };

	printf("��������ǰ---����������%d\n", arr->m_Capacity);
	printf("��������ǰ---�����С��%d\n", arr->m_Size);

	//��������
	insert_dynamicArray(arr, &p1, 0);
	insert_dynamicArray(arr, &p2, 0);
	insert_dynamicArray(arr, &p3, 1);
	insert_dynamicArray(arr, &p4, -1);
	insert_dynamicArray(arr, &p5, 0);
	insert_dynamicArray(arr, &p6, 0);

	//���ܣ��ţ��أ�������
	foreach_dynamicArray(arr, printPerson);

	printf("�������ݺ�---����������%d\n", arr->m_Capacity);
	printf("�������ݺ�---�����С��%d\n", arr->m_Size);

	//����λ�� ɾ����������
	removeByPos_dynamicArray(arr, 0);
	foreach_dynamicArray(arr, printPerson);

	//��ֵɾ�����ݣ�ɾ������
	removeByValue_dynamicArray(arr, &p1, comparaPerson);
	printf("ɾ����������������\n");
	foreach_dynamicArray(arr, printPerson);

	//��������
	destroy_dynamicArray(arr);
	arr = NULL;
}























/*
����
*/

//��ʼ������
seqQueue init_SeqQueue()
{
	struct dynamicArray* array = init_dynamicArray(MAX);

	return array;
}
//���
void push_SeqQueue(seqQueue queue, void* data)
{
	//�ȼ��� β��
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
//����
void pop_SeqQueue(seqQueue queue)
{
	//�ȼ���  ͷɾ��
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
//���ض�ͷԪ��
void* front_SeqQueue(seqQueue queue)
{
	if (queue == NULL)
	{
		return NULL;
	}

	struct dynamicArray* array = queue;

	return array->pAddr[0];

}

//���ض�βԪ��
void* back_SeqQueue(seqQueue queue)
{
	if (queue == NULL)
	{
		return NULL;
	}

	struct dynamicArray* array = queue;

	return array->pAddr[array->m_Size - 1];

}

//���д�С
int size_SeqQueue(seqQueue queue)
{
	if (queue == NULL)
	{
		return -1;
	}

	struct dynamicArray* array = queue;

	return array->m_Size;

}

//�ж��Ƿ�Ϊ��
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

//���ٶ���
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
	//��ʼ������
	seqQueue myQueue = init_SeqQueue();

	//׼������
	struct Person p1 = { "aaa", 10 };
	struct Person p2 = { "bbb", 20 };
	struct Person p3 = { "ccc", 30 };
	struct Person p4 = { "ddd", 40 };
	struct Person p5 = { "eee", 50 };

	//���
	push_SeqQueue(myQueue, &p1);
	push_SeqQueue(myQueue, &p2);
	push_SeqQueue(myQueue, &p3);
	push_SeqQueue(myQueue, &p4);
	push_SeqQueue(myQueue, &p5);

	printf("���д�СΪ��%d\n", size_SeqQueue(myQueue));

	while (isEmpty_SeqQueue(myQueue) == 0)
	{
		//��ͷԪ��
		struct Person* pFront = front_SeqQueue(myQueue);
		printf("��ͷԪ��������%s ���䣺%d \n", pFront->name, pFront->age);

		//��βԪ��
		struct Person* pBack = back_SeqQueue(myQueue);
		printf("��βԪ��������%s ���䣺%d \n", pBack->name, pBack->age);

		//����
		pop_SeqQueue(myQueue);
	}

	printf("���д�СΪ��%d\n", size_SeqQueue(myQueue));

	//���ٶ���
	destroy_SeqQueue(myQueue);
	myQueue = NULL;
}