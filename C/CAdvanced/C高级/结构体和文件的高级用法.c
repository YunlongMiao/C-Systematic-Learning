#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

 /*
 �ṹ��Ƕ��һ��ָ��
 */
typedef struct PERSON {

	char* name;
	int age;
}Person;

Person** allocteSpace() {

	Person** temp = malloc(sizeof(Person*) * 3);
	for (int i = 0; i < 3; i++) {

		//��ÿ��Person�����ڴ�
		temp[i] = malloc(sizeof(Person));

		//��ÿ��Person��name�����ڴ�ռ�
		temp[i]->name = malloc(sizeof(char) * 64);

		//��name��ֵ
		sprintf(temp[i]->name, "name_%d", i + 1);

		temp[i]->age = i + 18;
	}

	return temp;
}

void printfPerson(Person** array,int len) {

	for (int i = 0; i < len; i++) {

		printf("%s\n", array[i]->name);
		printf("%d\n", array[i]->age);
	}
}

void freePerson(Person** array, int len) {

	if (array == NULL || len <= 0)
		return;

	for (int i = 0; i < len; i++) {

		if (array[i]->name != NULL) {
			//�ͷ�����
			printf("%s��ʼ�ͷ�\n", array[i]->name);
			free(array[i]->name);
			array[i]->name = NULL;
		}

		if (array[i] != NULL) {

			free(array[i]);
			array[i] = NULL;
		}

		free(array);
		array = NULL;
	}
}
void structNestTest() {

	Person** pArray = NULL;

	//�����ڴ�
	pArray = allocteSpace();
	printfPerson(pArray, 3);
	//freePerson(pArray, 3); //�ڴ��ͷ��쳣
	
}


/*
�ṹ��Ƕ�׶���ָ��
*/

typedef struct TEACHER {

	char* name;
	char** students;
}Teacher;


void allocateSpace(Teacher*** teacherArray) {

	if (teacherArray == NULL)
		return;

	//���������ڴ�
	Teacher** ts = malloc(sizeof(Teacher*) * 3);

	//���ݸ�ֵ
	for (int i = 0; i < 3; i++) {

		ts[i] = malloc(sizeof(Teacher));
		//
		ts[i]->name = malloc(sizeof(char) * 64);

		//��ֵ
		sprintf(ts[i]->name, "teacher_%d", i + 1);
		//ѧ���������ռ�
		ts[i]->students = malloc(sizeof(char*) * 4);
		//ѧ�����鸳ֵ
		for (int j = 0; j < 4; j++) {

			ts[i]->students[j] = malloc(sizeof(char) * 64);
			sprintf(ts[i]->students[j], "%s_name_%d", ts[i]->name, j);
		}
	}
	*teacherArray = ts;
}


void printfteacherArray(Teacher** teacherArray) {

	for (int i = 0; i < 3; i++) 
	{
		printf("%s\n", teacherArray[i]->name);

		for (int j = 0; j < 4; j++)
			printf("    %s\n", teacherArray[i]->students[j]);
	}
		
}

void freeTeacherArray(Teacher** teacherArray) {

	if (teacherArray == NULL)
		return;

	for (int i = 0; i < 3; i++)
	{
		if (teacherArray[i]->name != NULL) {

			free(teacherArray[i]->name);
			teacherArray[i]->name = NULL;
		}

		for (int j = 0; j < 4; j++) {

			if (teacherArray[i]->students[j] != NULL) {

				free(teacherArray[i]->students[j]);
				teacherArray[i]->students[j] = NULL;
			}
		}

		free(teacherArray[i]->students);
		teacherArray[i]->students = NULL;

		free(teacherArray[i]->name);
		teacherArray[i]->name = NULL;

		free(teacherArray);
		teacherArray = NULL;
	}
}

void strcutNestTwoPoint() {

	//��ʦ���鴴��
	Teacher** teacherArray = NULL;

	//�����ڴ�
	allocateSpace(&teacherArray);
	printfteacherArray(teacherArray);
	freeTeacherArray(teacherArray);
	teacherArray = NULL;
}

/*
�ṹ��ƫ����
*/

struct TEACHER182 {

	char a;
	int b;
}TEACHER1822;

typedef struct TEACHER188 {

	char a;
	int b;
	struct TEACHER182 c;
}Test;

void structOffsetTest() {

	Test t1 = { 'a',200 ,'b',500};
	Test* p = &t1;

	int offset1 = offsetof(Test, c);
	int offset2 = offsetof(TEACHER182, b);

	printf("b��ƫ������%d\n", (int)&(p->b) - (int)p);
	printf("b��ƫ������%d\n", offsetof(Test, b));

	//ͨ��ƫ���������ڴ�
	printf("b��ֵΪ��%d\n", *(int*)((char*)p+offsetof(Test,b)));
	printf("b��ֵΪ��%d\n", *(int*)((int*)p + 1));

	printf("����c��b��ֵΪ��%d\n", *(int*)((int*)p + 1));


}