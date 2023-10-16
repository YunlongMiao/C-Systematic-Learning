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
		temp = 0;
		while (*str != '\0') {


			if (*str != *goal) {

				str++;
				temp++;
				continue;
			}

			//创建临时指针
			char* temstr = str;
			char* temgoal = goal;

			while (*temgoal != '\0') {

				temstr++;
				temgoal++;
				if (*temstr != *temgoal)
					break;
			}
			if (*temgoal == '\0')
			{
				printf("%d\n", temp);
				break;
			}
		}
	}
}

