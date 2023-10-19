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

	int offset1 = offsetof(Test, c);	//c在Test中的偏移量
	int offset2 = offsetof(struct TEACHER182, b);	//b在TEACHER182中的偏移量

	printf("b的偏移量：%d\n", (int)&(p->b) - (int)p);
	printf("b的偏移量：%d\n", offsetof(Test, b));

	//通过偏移量访问内存
	printf("b的值为：%d\n", *(int*)((char*)p+offsetof(Test,b)));
	printf("b的值为：%d\n", *(int*)((int*)p + 1));


	printf("属性c中b的值为：%d\n", *(int*)((char*)&t1 + offset1 + offset2));
	printf("属性c中b的值为：%d\n", ((struct TEACHER182*)((char*)&t1+offset1))->b);

}

/*
内存对齐
内存对齐原则：
第一个属性开始 从0开始计算偏移量
第二个属性开始 该属性的大小 与对齐模数比 取小的值的整数倍
当所有的值都计算完毕后，整体做二次偏移，
将上面计算的结果，扩充到这个结构体中最大数据类型 与对齐模数比 取小的值 的整数倍
*/

//#pragma pack (show)	//查看对齐模数的值 默认8
//#pragma pack (1)	//对齐模数 可以改为 2的n次方

typedef struct _STUDENT {

	int a;		//0~3		0~3
	char b;		//4~7		4
	double c;	//8~15		5~12
	float d;	//16~19		13~16
}Student;


typedef struct _STUDENT2 {

	char a;		//0~7		0
	Student b;	//8~31		1~16  ？
	double c;	//32~39		17~25 ？
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
文件读写
*/


//1、字符的读写回顾 fgetc(), fputc()
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

//2、按行进行读写
void fileWriteFputs() {

	FILE* fp = openFile("filetest2.txt", "w");
	char* buf[] = { 
		"锄禾日当午\n",
		"汗滴禾下土\n",
		"谁知盘中餐\n",
		"粒粒皆辛苦\n"
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

//3、按块进行读写
struct Hero
{
	char name[64];
	int age;
};

void fileWriteFwrite() {

	FILE* fp = openFile("filetest3.txt", "wb");

	struct Hero heros[] = 
	{
		{ "孙悟空", 999 },
		{ "亚瑟", 20 },
		{ "曹操", 80 },
		{ "鲁班", 5 },
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
		printf("姓名：  %s   年龄：  %d\n", temp[i].name, temp[i].age);

	fclose(fp);
	fp = NULL;
}


//4、格式化读写回顾
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
	//写文件
	FILE* f_wirte = fopen("filetest5.txt","wb");
	if (f_wirte == NULL)
	{
		return;
	}

	struct Hero heros[] =
	{
		{ "孙悟空", 999 },
		{ "亚瑟", 20 },
		{ "曹操", 80 },
		{ "鲁班", 5 },
	};

	for (int i = 0; i < 4; i++)
	{
		//参数1 数据地址   参数2  块大小   参数3  块个数   参数4  文件指针
		fwrite(&heros[i], sizeof(struct Hero), 1, f_wirte);
	}

	fclose(f_wirte);


	//读文件
	FILE* f_read = fopen("filetest5.txt", "rb");
	if (f_read == NULL)
	{
		//error 宏
		//printf("文件加载失败\n");
		perror("文件加载失败"); //用户提示信息 + 系统提示信息

		return;
	}
	struct Hero tempHero;
	//移动光标
	// 参数1  文件指针   参数2 偏移大小    参数3  起始位置   
	// SEEK_SET 从开始  SEEK_END 从结尾   SEEK_CUR 从当前位置
	//fseek(f_read, sizeof(struct Hero) * 2, SEEK_SET);

	fseek(f_read, -(long)sizeof(struct Hero) * 2, SEEK_END);

	rewind(f_read); //将文件光标置首

	fread(&tempHero, sizeof(struct Hero), 1, f_read);

	printf(" 姓名： %s , 年龄： %d\n", tempHero.name, tempHero.age);


	fclose(f_read);
}



void fileWRTest() {

	//1、字符的读写回顾 fgetc(), fputc()
	fileWriteFputc();
	fileReadFgetc();

	//2、按行进行读写
	fileWriteFputs();
	fileReadFgets();

	//3、按块进行读写
	fileWriteFwrite();
	fileReadFread();

	//4、格式化读写回顾
	fileWriteFprintf();
	fileReadFscanf();

	//光标移动
	test05();
}