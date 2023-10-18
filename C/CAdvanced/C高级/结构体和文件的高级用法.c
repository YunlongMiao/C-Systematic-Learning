#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

 /*
 结构体嵌套一级指针
 */
typedef struct PERSON {

	char* name;
	int age;
}Person;

Person** allocteSpace() {

	Person** temp = malloc(sizeof(Person*) * 3);
	for (int i = 0; i < 3; i++) {

		//给每个Person分配内存
		temp[i] = malloc(sizeof(Person));

		//给每个Person的name分配内存空间
		temp[i]->name = malloc(sizeof(char) * 64);

		//给name赋值
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
			//释放人名
			printf("%s开始释放\n", array[i]->name);
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

	//分配内存
	pArray = allocteSpace();
	printfPerson(pArray, 3);
	//freePerson(pArray, 3); //内存释放异常
	
}


/*
结构体嵌套二级指针
*/

typedef struct TEACHER {

	char* name;
	char** students;
}Teacher;


void allocateSpace(Teacher*** teacherArray) {

	if (teacherArray == NULL)
		return;

	//堆区分配内存
	Teacher** ts = malloc(sizeof(Teacher*) * 3);

	//数据赋值
	for (int i = 0; i < 3; i++) {

		ts[i] = malloc(sizeof(Teacher));
		//
		ts[i]->name = malloc(sizeof(char) * 64);

		//赋值
		sprintf(ts[i]->name, "teacher_%d", i + 1);
		//学生数组分配空间
		ts[i]->students = malloc(sizeof(char*) * 4);
		//学生数组赋值
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

	//老师数组创建
	Teacher** teacherArray = NULL;

	//分配内存
	allocateSpace(&teacherArray);
	printfteacherArray(teacherArray);
	freeTeacherArray(teacherArray);
	teacherArray = NULL;
}

/*
结构体偏移量
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

	printf("b的偏移量：%d\n", (int)&(p->b) - (int)p);
	printf("b的偏移量：%d\n", offsetof(Test, b));

	//通过偏移量访问内存
	printf("b的值为：%d\n", *(int*)((char*)p+offsetof(Test,b)));
	printf("b的值为：%d\n", *(int*)((int*)p + 1));

	printf("属性c中b的值为：%d\n", *(int*)((int*)p + 1));


}