#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>	//标准输入输出
#include<string.h>	//字符串处理函数
#include<stdlib.h>	//标准库函数

//指针变量
void PointVariableTest() {

	int* p1 = 0x1234;
	int*** p2 = 0x1111;

	printf("p1 size:%d\n", sizeof(p1));
	printf("p2 size:%d\n", sizeof(p2));

	int a = 10;
	p1 = &a;

	printf("p1 address:%p\n", &p1);
	printf("p1 address:%p\n", p1);
	printf("a address:%p\n", &a);
}


//野指针和空指针

//不允许向NULL和非法地址拷贝内存

void OtherPointTest() {

	char* p = NULL;
	//给p所指内存区域拷贝内容
	//strcpy(p, "1111");	//err 空指针

	char* q = 0x1122;		//野指针,不可读取，不可访问
	//给q所指内存区域拷贝内容
	//strcpy(q, "2222");

	//p = 0x001;
	//printf("%d\n", p);
	//*p = 100;
}



//间接访问操作符

void VisitOperatorTest() {

	int* p = NULL;
	int a = 10;

	p = &a;
	*p = 100;
	int b = *p;

	char* str = "hello world!";	//err 常量区，不可更改
	//*str = 'm';

	printf("a:%d\n", a);
	printf("*p:%d\n", *p);
	printf("b:%d\n", b);
	printf("str:%s\n", str);
}


//指针的步长
typedef struct PERSON {

	char a;		//0~3
	int b;		//4~7
	char buf[64];	//8~71
	int d;		//72~75
}Person;

void PointStepSizeTest() {

	int num = 0xaabbccdd;
	unsigned int* p1 = &num;
	unsigned char* p2 = &num;

	printf("%x\n", *p1);
	printf("%x\n", *p2);	//dd-小段模式

	printf("%x\n", p1);
	printf("%x\n", p1+1);

	printf("%x\n", p2);
	printf("%x\n", p2+1);


	Person p = { 'a',10,"Hello World",1000 };

	//p中d属性偏移量是多少
	printf("d的偏移量为：%d\n", offsetof(Person, d));

	printf("d的值为：%d\n", *(int*)((char*)&p + offsetof(Person, d)));

}

//字符串注意事项,sizeof和strlen测试范围

void StrAttentionTest() {

	//字符串结尾要加\0
	char str1[] = { 'H','e','l','l','o' ,'\0'};
	printf("%s\n", str1);

	char str2[100] = { 'H','e','l','l','o' };
	printf("%s\n", str2);

	char str3[] = "Hello";
	printf("%s\n", str3);
	printf("sizeof of str3:%d\n", sizeof(str3));	//6
	printf("strlen of str3:%d\n", strlen(str3));	//5

	char str4[100] = "Hello";
	printf("sizeof of str4:%d\n", sizeof(str4));	//100
	printf("strlen of str4:%d\n", strlen(str4));	//5

	char str5[] = "hello\0world";
	printf("sizeof of str5:%d\n", sizeof(str5));	//12
	printf("strlen of str5:%d\n", strlen(str5));	//5

	char str6[] = "hello\012world";		//\012 八进制数字 转换为十进制 10 对应ASCII码 换行
	printf("sizeof of str6:%d\n", sizeof(str6));	//12
	printf("strlen of str6:%d\n", strlen(str6));	//11

}

/*
字符串练习
*/

//拷贝方法1
void copy_string01(char* dest, char* source) {

	for (int i = 0; source[i] != '\0'; i++) {
		dest[i] = source[i];
	}

}

//拷贝方法2
void copy_string02(char* dest, char* source) {
	while (*source != '\0' /* *source != 0 */) {
		*dest = *source;
		source++;
		dest++;
	}
}

//拷贝方法3
void copy_string03(char* dest, char* source) {
	//判断*dest是否为0，0则退出循环
	while (*dest++ = *source++) {}
}


void reverse_string(char* str) {

	if (str == NULL) {
		return;
	}

	int begin = 0;
	int end = strlen(str) - 1;

	while (begin < end) {

		//交换两个字符元素
		char temp = str[begin];
		str[begin] = str[end];
		str[end] = temp;

		begin++;
		end--;
	}

}



void StrExercisesTest() {

	//字符串拷贝功能实现
	char str1[] = "Hello World!";
	char str2[100] = "";
	copy_string01(str2,str1);
	printf("str2-01:%s\n", str2);
	copy_string02(str2, str1);
	printf("str2-02:%s\n", str2);
	copy_string03(str2, str1);
	printf("str2-03:%s\n", str2);

	//字符串反转模型
	char str[] = "abcdefghijklmn";
	reverse_string(str);
	printf("str:%s\n", str);
}

//字符串格式化
void StrFormattingTest() {

	//1. 格式化字符串
	char buf[1024] = { 0 };
	{
		sprintf(buf, "你好,%s,欢迎加入我们!", "John");
		printf("buf:%s\n", buf);

		memset(buf, 0, 1024);
		sprintf(buf, "我今年%d岁了!", 20);
		printf("buf:%s\n", buf);
	}

	//2. 拼接字符串
	{
		memset(buf, 0, 1024);
		char str1[] = "hello";
		char str2[] = "world";
		int len = sprintf(buf, "%s %s", str1, str2);
		printf("buf:%s len:%d\n", buf, len);
	}

	//3. 数字转字符串
	{
		memset(buf, 0, 1024);
		int num = 100;
		sprintf(buf, "%d", num);
		printf("buf:%s\n", buf);

		//设置宽度 右对齐
		memset(buf, 0, 1024);
		sprintf(buf, "%8d", num);
		printf("buf:%s\n", buf);

		//设置宽度 左对齐
		memset(buf, 0, 1024);
		sprintf(buf, "%-8d", num);
		printf("buf:%s\n", buf);

		//转成16进制字符串 小写
		memset(buf, 0, 1024);
		sprintf(buf, "0x%x", num);
		printf("buf:%s\n", buf);

		//转成8进制字符串
		memset(buf, 0, 1024);
		sprintf(buf, "0%o", num);
		printf("buf:%s\n", buf);
	}


	//1. 跳过数据
	
	{
		//跳过前面的数字
		//匹配第一个字符是否是数字，如果是，则跳过
		//如果不是则停止匹配
		memset(buf, 0, 1024);
		sscanf("123456aa65aa", "%*d%s", buf);	//只能匹配位于前面的字符  aa65aa
		printf("跳过数据 buf:%s\n", buf);
	}


	//2. 读取指定宽度数据
	{
		//跳过前面的数字
		memset(buf, 0, 1024);
		sscanf("123456aaaa", "%7s", buf);
		printf("读取指定宽度数据 buf:%s\n", buf);
	}


	//3. 匹配a-z中任意字符
	{
		//跳过前面的数字
		//先匹配第一个字符，判断字符是否是a-z中的字符，如果是匹配
		//如果不是停止匹配
		memset(buf, 0, 1024);
		sscanf("abcdefgAA123456A", "%[a-z]", buf);
		printf("匹配a-z中任意字符 buf:%s\n", buf);
	}

	//4. 匹配aBc中的任何一个
	{
		//跳过前面的数字
		//先匹配第一个字符是否是aBc中的一个，如果是，则匹配，如果不是则停止匹配
		memset(buf, 0, 1024);
		sscanf("abcdefg123456", "%[aBc]", buf);
		printf("匹配aBc中的任何一个 buf:%s\n", buf);
	}

	//5. 匹配非a的任意字符
	{
		memset(buf, 0, 1024);
		sscanf("bcdefag123456", "%[^a]", buf);
		printf("匹配非a的任意字符 buf:%s\n", buf);
	}

	//6. 匹配非a-z中的任意字符
	{
		memset(buf, 0, 1024);
		sscanf("123456ABCDbcdefag", "%[^a-z]", buf);
		printf("匹配非a-z中的任意字符 buf:%s\n", buf);
	}

}

//分割姓名
void StrFormattingTest_T() {
	//分割姓名
	char str1[] = "416wge#MiaoYunLong@outlook.com";
	char str2[1024] = "";
	sscanf(str1, "%*[^#]#%[^@]", str2);
	printf("%s\n", str2);
}


//字符串强化-子串查找
void StrStrengthenFindTest() {

	char* str = "sgwfaufcgbquifbhquagxcaufhbwuf";
	char* goal = "bqu";
	int temp = -1;

	//自己写的
	{
		for (int i = 0; i < strlen(str) - 2; i++)
		{
			if (str[i] == goal[0])
			{
				for (int f = 1; f < strlen(goal); f++)
				{
					if (str[i + f] != goal[f])
						break;
					temp = i;
				}
			}
		}
		printf("%d\n", temp);
	}

	//视频内容
	{
		int x = 0;
		temp = -1;
		while (*str != '\0') 
		{


			if (*str != *goal) 
			{
				x++;
				str++;
				continue;
			}

			//创建临时指针
			char* temstr = str;
			char* temgoal = goal;

			while (*temgoal != '\0') 
			{
				
				temstr++;
				temgoal++;

				if (*temstr != *temgoal)//匹配失败情况
					break;
			}

			str++;

			if (*temgoal == '\0')
			{
				temp = x;
				x = -1;
				printf("%d\n", temp);
				break;
			}
		}
		if(x != -1)
			printf("%d\n", temp);
	}
}


/*
一级指针易错点
*/
//指针移动后不可free
void FirstOrderPointerTest() {

	char* p = (char*)malloc(sizeof(char) * 64);
	char* pp = p;
	for (int i = 0; i < 10; i++)
	{
		*pp = i + 97;
		printf("%c\n", *pp);
		pp++;
	}

	free(p);

	p = NULL;

}


/*
二级指针的输出特性
*/

void SecondOrderPointerOutputTest() {

	//在堆区开辟内存
	int** pArray = malloc(sizeof(int*) * 5);

	//在栈上开辟数据
	int a1 = 100;
	int a2 = 200;
	int a3 = 300;
	int a4 = 400;
	int a5 = 500;

	//堆区数组维护 栈上数据的地址，建立联系
	pArray[0] = &a1;
	pArray[1] = &a2;
	pArray[2] = &a3;
	pArray[3] = &a4;
	pArray[4] = &a5;

	int** Array = pArray;	//传入后，*数组名退化为**指针
	
	printf("%d\n", sizeof((Array)) / sizeof(int*));
	printf("%d\n", strlen((*Array)));

	for (int i = 0; i < 5; i++)
		printf("%d\n", *Array[i]);

	//释放堆区空间
	if (pArray != NULL)
	{
		free(pArray);
		pArray = NULL;
	}

}



/*
二级指针的输入特性
*/
void SecondOrderPointerInputTest() {

	//在栈上开辟内存
	int* pArray[5];
	for (int i = 0; i < 5; i++) {

		pArray[i] = malloc(4);//栈上每个数据 维护 栈区开辟的内存
		*(pArray[i]) = i + 100;
	}
	int** Array = pArray;

	printf("%d\n", sizeof(pArray) / sizeof(int*));	//5 pArray 数组
	printf("%d\n", sizeof(Array) / sizeof(int*));	//1 Array	二级指针
	printf("%d\n", strlen((*Array)));				//1

	for (int i = 0; i < 5; i++)
		printf("%d\n", *Array[i]);

	//堆区数据释放
	for (int i = 0; i < 5; i++)
	{
		if (pArray[i] != NULL)
			free(pArray[i]);
		pArray[i] = NULL;
	}

}


/*
二级指针做函数参数的输出特性
*/
void AllocateSpace(int** pp) {

	int* pArray = malloc(sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
		pArray[i] = i + 100;

	*pp = pArray;
}
void SecondOrderPointerParameterOutputTest() {

	int* p = NULL;
	AllocateSpace(&p);

	for (int i = 0; i < 10; i++)
		printf("%d\n", p[i]);

	int** arr = &p;
	for (int i = 0; i < 10; i++)
		printf("%d\n", (*arr)[i]);

	//释放堆区数据
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}


/*
二级指针练习-文件读写
*/

int getFileLines(FILE* fp) {

	if (fp == NULL)
		return -1;

	char buf[1024];
	int lines = 0;

	while (fgets(buf, 1024, fp) != NULL)
	{
		lines++;
		//printf("%s\n", buf);
	}

	//将光标置首
	fseek(fp, 0, SEEK_SET);

	return lines;
}

void readFileData(FILE* FILE, char** pArray,int len) {

	if (FILE == NULL || pArray == NULL || len <= 0)
		return;

	char buf[1024] = { 0 };
	int index = 0;

	while (fgets(buf, 1024, FILE) != NULL) {

		//计算开辟每个字符串的大小
		int currentLen = strlen(buf) + 1;
		//字符串最后字符改为 \0
		buf[strlen(buf) - 1] = '\0';

		//开辟堆区空间
		char* currentP = malloc(sizeof(char) * currentLen);

		//将文件中读取的内容，放到开辟的空间中
		strcpy(currentP, buf);

		//将开辟空间的数据 放入数组中
		pArray[index++] = currentP;

		//清空buf
		memset(buf, 0, 1024);
	}
}

void SecondOrderPointerFileRWTest() {

	//打开文件
	FILE* fp = fopen("./filetest.txt", "r");
	if (fp == NULL)
		printf("open file fail");

	//获取文件有效行数
	int len = getFileLines(fp);
	printf("%d\n", len);
	char** pArray = malloc(sizeof(char*) * len);

	//将文件中的数据放到pArray的数组中
	readFileData(fp,pArray,len);

	//打印数组
	for (int i = 0; i < len; i++)
		printf("%s\n", pArray[i]);

	//关闭文件
	fclose(fp);
	fp = NULL;
	//释放堆区
	for(int i=0;i<len;i++)
		if (pArray[i] != NULL)
		{
			printf("%s被释放\n", pArray[i]);
			free(pArray[i]);
			pArray[i] = NULL;
		}

	free(pArray);
	pArray = NULL;

}


/*
位运算
*/
void bitOperationTest() {

	//按位取反
	int num = 2;
	printf("%d\n", ~num);	//-3
	// 0...10
	// 1...01	原码
	// 1...10+1 111 补码

	//按位与
	if (num & 1)
		printf("奇数\n");
	else
		printf("偶数\n");

	//按位异或
	int num626 = 5;
	int num627 = 9;
	printf("num626 = %d\nnum627 = %d\n\n", num626, num627);
	//	0101  5		1
	//	1001  9		2
	//  1100  12	3

	num626 = num626 ^ num627;
	num627 = num626 ^ num627;
	num626 = num626 ^ num627;
	printf("num626 = %d\nnum627 = %d\n\n", num626, num627);

	num626 = num626 + num627;
	num627 = num626 - num627;
	num626 = num626 - num627;
	printf("num626 = %d\nnum627 = %d\n\n", num626, num627);

}


/*
一维数组名称
*/
void oneDimensionalArrayTest() {

	//一维数组的名，不是指向第一个元素的指针
	int arr[5] = { 1,2,3,4,5 };
	printf("sizeof arr = %d\n", sizeof(arr));

	//对数组名，取地址
	printf("&arr \t%d\n", &arr);
	printf("&arr+1 \t%d\n", &arr + 1);

	/*
	第一种：对数组名称 sizeof
	第二种：对数组名称取地址 步长为整个数组长度
	除这两种情况，一维数组名 指向数组第一个元素的指针
	*/

	int* p = arr;
	//数组名是指针常量
	//int* const p	指针常量,指针指向不能修改
	//const int* p	常量指针，指针指向的值不能修改

	//数组访问的时候，下标可以为负数
	p = p + 3;
	printf("%d\n", p[0]);
	printf("%d\n", p[-1]);	//给人看
	printf("%d\n", *(p - 1));	//给机器看
}


/*
数组指针的定义
*/

void arrayPointTest() {

	int num[5] = { 1,2,3,4,5 };

	//第一种
	typedef int(ARRAY_TYPE)[5];	//ARRAY_TYPE是一个有5个int类型的数组类型
	ARRAY_TYPE* arrP = &num;
	for (int i = 0; i < 5; i++)
		printf("%d\n", (*arrP)[i]);
	printf("\n\n");

	//第二种
	typedef int(*ARRAY_TYPE1)[5];
	ARRAY_TYPE1 arrPY = &num;
	for (int i = 0; i < 5; i++)
		printf("%d\n", (*arrP)[i]);
	printf("\n\n");


	//第三种
	int(*p)[5] = &num;
	for (int i = 0; i < 5; i++)
		printf("%d\n", (*p)[i]);
	printf("\n\n");
}


/*
二维数组数组名
*/

//void disPlay713(int pArr[][3], int len1, int len2)
//void disPlay713(int pArr[3][3], int len1, int len2)
void disPlay713(int(*pArr)[3], int len1, int len2) 
{

	for(int i=0;i<len1;i++)
		for (int j = 0; j < len2; j++)
		{
			printf("%d", *(*(pArr + i) + j));
			printf("%d\n", pArr[i][j]);
		}
}

void twoDimensionalArrayTest() {

	int arr1[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9}
	};
	int arr2[3][3] = { 1,2,3,4,5,6,7,8,9 };

	int arr3[][3] = { 1,2,3,4,5,6,7,8,9 };

	int(*p)[3] = arr1;	//一般情况下，指向第一行数组

	//通过p指针 访问6
	printf("%d\n", *(*p + 5));
	printf("%d\n", *(*(p + 1) + 2));
	printf("%d\n", p[1][2]);

	disPlay713(arr1, 3, 3);

	printf("%d\n", sizeof(arr1));
	printf("%d\n", &arr1);
	printf("%d\n", &arr1 + 1);

	int(*p1)[3][3] = &arr1;
}

/*
选择排序
*/
void selectionSort1(int* arr, int len) {

	for (int i = 0; i < len; i++)
	{
		int min = i;
		for(int j=i+1; j<len; j++)
			if (arr[min] > arr[j])
			{
				arr[min] = arr[min] + arr[j];
				arr[j] = arr[min] - arr[j];
				arr[min] = arr[min] - arr[j];
			}
	}
}

void selectionSort2(char* arr[], int len) {

	for (int i = 0; i < len; i++)
	{
		int max = i;
		for (int j = i + 1; j < len; j++)
			if (strcmp(arr[max], arr[j]) == -1)
				max = j;

		if(i!=max) 
		{
			char* temp = arr[max];
			arr[max] = arr[i];
			arr[i] = temp;
		}
	}
}


void selectionSortTest() {

	int pArr[] = {1,2,10,4,5,50,7,8,9};
	char* Arr[] = { "aaa","bbb","ccc","ddd","eee" };
	int len = sizeof(pArr) / sizeof(pArr[0]);

	selectionSort1(pArr, len);
	for (int i = 0; i < len; i++)
		printf("%d\n", pArr[i]);

	len = sizeof(Arr) / sizeof(Arr[0]);
	selectionSort2(Arr, len);
	for (int i = 0; i < len; i++)
		printf("%s\n", Arr[i]);

}