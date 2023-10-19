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

	int offset1 = offsetof(Test, c);	//c��Test�е�ƫ����
	int offset2 = offsetof(struct TEACHER182, b);	//b��TEACHER182�е�ƫ����

	printf("b��ƫ������%d\n", (int)&(p->b) - (int)p);
	printf("b��ƫ������%d\n", offsetof(Test, b));

	//ͨ��ƫ���������ڴ�
	printf("b��ֵΪ��%d\n", *(int*)((char*)p+offsetof(Test,b)));
	printf("b��ֵΪ��%d\n", *(int*)((int*)p + 1));


	printf("����c��b��ֵΪ��%d\n", *(int*)((char*)&t1 + offset1 + offset2));
	printf("����c��b��ֵΪ��%d\n", ((struct TEACHER182*)((char*)&t1+offset1))->b);

}

/*
�ڴ����
�ڴ����ԭ��
��һ�����Կ�ʼ ��0��ʼ����ƫ����
�ڶ������Կ�ʼ �����ԵĴ�С �����ģ���� ȡС��ֵ��������
�����е�ֵ��������Ϻ�����������ƫ�ƣ�
���������Ľ�������䵽����ṹ��������������� �����ģ���� ȡС��ֵ ��������
*/

//#pragma pack (show)	//�鿴����ģ����ֵ Ĭ��8
//#pragma pack (1)	//����ģ�� ���Ը�Ϊ 2��n�η�

typedef struct _STUDENT {

	int a;		//0~3		0~3
	char b;		//4~7		4
	double c;	//8~15		5~12
	float d;	//16~19		13~16
}Student;


typedef struct _STUDENT2 {

	char a;		//0~7		0
	Student b;	//8~31		1~16  ��
	double c;	//32~39		17~25 ��
}Student2;

void memoryAligningTest() {

	printf("student sizeof = %d\n",sizeof(Student));
	printf("student2 sizeof = %d\n", sizeof(Student2));
}



FILE* openFile(char p[],char s[]) {

	FILE* fp = fopen(p, s);

	if (fp == NULL) {
		printf("open file fail\n");
		return;
	}
	return fp;
}
/*
�ļ���д
*/


//1���ַ��Ķ�д�ع� fgetc(), fputc()
void fileWriteFputc() {

	FILE* fp = openFile("filetest1.txt","w");
	char buf[] = "hello world!";

	for (int i = 0; i < strlen(buf); i++)
		fputc(buf[i], fp);

	fclose(fp);
	fp = NULL;
}
void fileReadFgetc() {

	FILE* fp = openFile("filetest1.txt", "r");
	char buf ;

	while ((buf = fgetc(fp)) != EOF)
		printf("%c", buf);
	printf("\n");

	fclose(fp);
	fp = NULL;
}

//2�����н��ж�д
void fileWriteFputs() {

	FILE* fp = openFile("filetest2.txt", "w");
	char* buf[] = { 
		"�����յ���\n",
		"���κ�����\n",
		"˭֪���в�\n",
		"����������\n"
	};

	for (int i = 0; i < 4; i++)
		fputs(buf[i], fp);

	fclose(fp);
	fp = NULL;
}
void fileReadFgets() {

	FILE* fp = openFile("filetest2.txt", "r");
	char temp[1024] = { 0 };
	while (!feof(fp))
	{
		memset(temp, 0, 1024);

		fgets(temp, 1024, fp);
		printf("%s", temp);
	}

	fclose(fp);
	fp = NULL;
}

//3��������ж�д
struct Hero
{
	char name[64];
	int age;
};

void fileWriteFwrite() {

	FILE* fp = openFile("filetest3.txt", "wb");

	struct Hero heros[] = 
	{
		{ "�����", 999 },
		{ "��ɪ", 20 },
		{ "�ܲ�", 80 },
		{ "³��", 5 },
	};

	for (int i = 0; i < 4; i++)
		fwrite(&heros[i], sizeof(struct Hero), 1, fp);

	fclose(fp);
	fp = NULL;
}
void fileReadFread() {

	FILE* fp = openFile("filetest3.txt", "rb");
	struct Hero temp[4];

	fread(&temp, sizeof(struct Hero), 4, fp);
	for (int i = 0; i < 4; i++)
		printf("������  %s   ���䣺  %d\n", temp[i].name, temp[i].age);

	fclose(fp);
	fp = NULL;
}


//4����ʽ����д�ع�
void fileWriteFprintf() {

	FILE* fp = openFile("filetest4.txt", "w");

	fprintf(fp, "hello world!! %s", "abcd");

	fclose(fp);
	fp = NULL;
}
void fileReadFscanf() {

	FILE* fp = openFile("filetest4.txt", "r");

	char temp[1024] = { 0 };

	while (!feof(fp)) {

		fscanf(fp, "%s", temp);
		printf("%s\n", temp);
	}

	fclose(fp);
	fp = NULL;
}



void test05()
{
	//д�ļ�
	FILE* f_wirte = fopen("filetest5.txt","wb");
	if (f_wirte == NULL)
	{
		return;
	}

	struct Hero heros[] =
	{
		{ "�����", 999 },
		{ "��ɪ", 20 },
		{ "�ܲ�", 80 },
		{ "³��", 5 },
	};

	for (int i = 0; i < 4; i++)
	{
		//����1 ���ݵ�ַ   ����2  ���С   ����3  �����   ����4  �ļ�ָ��
		fwrite(&heros[i], sizeof(struct Hero), 1, f_wirte);
	}

	fclose(f_wirte);


	//���ļ�
	FILE* f_read = fopen("filetest5.txt", "rb");
	if (f_read == NULL)
	{
		//error ��
		//printf("�ļ�����ʧ��\n");
		perror("�ļ�����ʧ��"); //�û���ʾ��Ϣ + ϵͳ��ʾ��Ϣ

		return;
	}
	struct Hero tempHero;
	//�ƶ����
	// ����1  �ļ�ָ��   ����2 ƫ�ƴ�С    ����3  ��ʼλ��   
	// SEEK_SET �ӿ�ʼ  SEEK_END �ӽ�β   SEEK_CUR �ӵ�ǰλ��
	//fseek(f_read, sizeof(struct Hero) * 2, SEEK_SET);

	fseek(f_read, -(long)sizeof(struct Hero) * 2, SEEK_END);

	rewind(f_read); //���ļ��������

	fread(&tempHero, sizeof(struct Hero), 1, f_read);

	printf(" ������ %s , ���䣺 %d\n", tempHero.name, tempHero.age);


	fclose(f_read);
}



void fileWRTest() {

	//1���ַ��Ķ�д�ع� fgetc(), fputc()
	fileWriteFputc();
	fileReadFgetc();

	//2�����н��ж�д
	fileWriteFputs();
	fileReadFgets();

	//3��������ж�д
	fileWriteFwrite();
	fileReadFread();

	//4����ʽ����д�ع�
	fileWriteFprintf();
	fileReadFscanf();

	//����ƶ�
	test05();
}