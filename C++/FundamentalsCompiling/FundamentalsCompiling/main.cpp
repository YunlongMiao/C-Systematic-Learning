#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define NULL 0
#define MAX_KEY_NUM  9		
#define MAX_BORDER_NUM  6
#define MAX_ARITH_NUM  4
#define MAX_RELATION_NUM 7 
#define MAX_CONSTS_NUM  20
#define MAX_ID_NUM  20


FILE* fp;
char cbuffer;

//1
const char* key[MAX_KEY_NUM] = { "if","else","int","for","while","do","return","break","cintunue" };
//2
const char* border[MAX_BORDER_NUM] = { ",",";","{","}","(",")" };
//3
const char* arithmetic[MAX_ARITH_NUM] = { "+","-","*","/" };
//4
const char* relation[MAX_RELATION_NUM] = { "=","==","!=",">",">=","<","<=" };
//5
char* consts[MAX_CONSTS_NUM];
//6
char* id[MAX_ID_NUM];

//char KEY[MAX_KEY_NUM] = { "if","else","int","for","while","do","return","break","cintunue" };
//char BORDER[MAX_BORDER_NUM] = { ",",";","{","}","(",")" };
//char ARITHMETIC[MAX_ARITH_NUM] = { "+","-","*","/" };
//char RELATION[MAX_RELATION_NUM] = { "=","==","!=",">",">=","<","<=" };
//char CONST[MAX_CONSTS_NUM];
//char ID[MAX_ID_NUM];
//
//char* key = KEY;
//char* border = BORDER;
//char* arithmetic = ARITHMETIC;
//char* relation = RELATION;
//char* consts = CONST;
//char* id = ID;


int constnum = 0, idnum = 0;


/*
作用：搜索对应字符
输入：searchchar：需要比较的字符串	wordtype：目标字符串种类识别码
输出：需要比较的字符串(searchchar)在对应字符串中的位置
例：search(s,1)	s="if"
*/
int search(char searchchar[], int wordtype) {
	int i = 0;
	switch (wordtype) {
	case 1:
		for (i = 0; i < MAX_KEY_NUM; i++) {
			if (strcmp(key[i], searchchar) == 0)
				return(i + 1);
		}
	case 2:
	{
		for (i = 0; i < MAX_BORDER_NUM; i++) {
			if (strcmp(border[i], searchchar) == 0)
				return(i + 1);
		}
		return(0);
	}
	case 3:
	{
		for (i = 0; i < MAX_ARITH_NUM; i++) {
			if (strcmp(arithmetic[i], searchchar) == 0) {
				return(i + 1);
			}
		}
		return(0);
	}

	case 4:
	{
		for (i = 0; i < MAX_RELATION_NUM; i++) {
			if (strcmp(relation[i], searchchar) == 0) {
				return(i + 1);
			}
		}
		return(0);
	}
	case 5:
	{
		for (i = 0; i < constnum; i++) {
			if (constnum > 0)
				if (strcmp(consts[i], searchchar) == 0) {
					return(i + 1);
				}
		}
		consts[i] = (char*)malloc(sizeof(searchchar));
		memcpy(consts[i], searchchar,sizeof(searchchar));
		constnum++;
		return(i + 1);
	}
	case 6:
	{
		for (i = 0; i < idnum; i++) {
			if (strcmp(id[i], searchchar) == 0) {
				return(i + 1);
			}
		}
		id[i] = (char*)malloc(sizeof(searchchar));
		memcpy(id[i], searchchar,sizeof(searchchar));
		idnum++;
		return(i + 1);
	}
	}
}


//isalpha()用来判断一个字符是否为字母
//isdigit() 用来检测一个字符是否是十进制数字0-9

/*
作用：搜索字母	1、6

输入：buffer:字符串
输出：buffer:字符串 打印文件读取的字符串(searchchar)在对应字符串中的位置
例：alphaprocess(ch)	ch="if"
*/
char alphaprocess(char buffer) {
	int atype;
	int i = -1;
	char alphatp[20];
	while ((isalpha(buffer)) || (isdigit(buffer))) {	//字母或数字型字符进入，将连续的符合条件的字符放入alphatp
		alphatp[++i] = buffer;
		buffer = fgetc(fp);
	}
	alphatp[i + 1] = '\0';

	if (atype = search(alphatp, 1))
		printf("%s   (1,%d)\n", alphatp, atype);
	else {
		atype = search(alphatp, 6);
		printf("%s    (6,%d)\n", alphatp, atype);
	}
	return(buffer);
}


/*
作用：搜索数字	5
输入：buffer:字符串
输出：buffer:字符串 打印文件读取的字符串(searchchar)在对应字符串中的位置
例：digitprocess(ch)	ch="if"
*/
char digitprocess(char buffer) {
	int i = -1;
	char digittp[20];
	int dtype;
	while ((isdigit(buffer))) {	//获得非数字字符
		digittp[++i] = buffer;
		buffer = fgetc(fp);
	}
	digittp[i + 1] = '\0';
	dtype = search(digittp, 5);
	printf("%s    (5,%d)\n", digittp, dtype);
	return(buffer);
}


/*
作用：搜索非字母数字类型	2、3、4

输入：buffer:字符串
输出：buffer:字符串 打印文件读取的字符串(searchchar)在对应字符串中的位置
例：otherprocess(ch)	ch="=="
*/
char otherprocess(char buffer) {
	int i = -1;
	char othertp[20];
	int otype, otypetp;
	othertp[0] = buffer;
	othertp[1] = '\0';
	if (othertp[0] == '\0') {
		buffer = fgetc(fp);
		othertp[1] = buffer;
		if (othertp[1] == '/' || othertp[1] == '*') {
			int i = 1;
			if (othertp[1] == '*') {
				while (othertp[i - 1] != '*' || othertp[i] != '/') {
					buffer = fgetc(fp);
					othertp[++i] = buffer;
				}
				othertp[i + 1] = '\0';
				printf("(%s,注释)\n", othertp);
				buffer = fgetc(fp);
				goto out;
			}
			else {
				while (othertp[i] != '\n') {
					buffer = fgetc(fp);
					othertp[++i] = buffer;
				}
				othertp[i] = '\0';
				printf("(%s,注释)\n", othertp);
				buffer = fgetc(fp);
				goto out;
			}
		}
		else {
			buffer = othertp[1];
			othertp[1] = '\0';
			if (otype = search(othertp, 3))
				printf("%s    (3,%d)\n", othertp, otype - 1);
			goto out;
		}
	}
	if (otype = search(othertp, 3)) {
		printf("%s   (3,%d)\n", othertp, otype);
		buffer = fgetc(fp);
		goto out;
	}

	if (othertp[0] == '=' || othertp[0] == '!' || othertp[0] == '<' || othertp[0] == '>') {
		buffer = fgetc(fp);
		othertp[1] = buffer;
		if (othertp[1] == '=') {
			othertp[2] = '\0';
			if (otypetp = search(othertp, 4)) {
				printf("%s   (4,%d)\n", othertp, otypetp);
				buffer = fgetc(fp);
				goto out;
			}
		}
		else {
			buffer + othertp[1];
			othertp[1] = '\0';
			if (otypetp = search(othertp, 4)) {
				printf("%s   (4,%d)\n", othertp, otypetp);
				goto out;
			}
		}
	}


	if (otype = search(othertp, 2)) {
		printf("%s    (2,%d)\n", othertp, otype);
		buffer = fgetc(fp);
		goto out;
	}
	if ((buffer != '\n') && (buffer != ' '))
		printf("%c error,not a word\n", buffer);
	buffer = fgetc(fp);
out: return(buffer);
}


int main() {
	int i;
	for (i = 0; i <= 20; i++) {		//id和consts清空数值
		id[i] = NULL;
		consts[i] = NULL;
	}
	if ((fp = fopen("example.c", "r")) == NULL)	//打开要分析的文件
		printf("error");
	else {
		cbuffer = fgetc(fp);
		while (cbuffer != EOF) {				//循环读取，直至读完
			if (cbuffer == ' ' || cbuffer == '\n' || cbuffer == '\t')
				cbuffer = fgetc(fp);
			else  if (isalpha(cbuffer))		//判断字母
				cbuffer = alphaprocess(cbuffer);
			else if (isdigit(cbuffer))		//判断数字
				cbuffer = digitprocess(cbuffer);
			else 							//非字母数字
				cbuffer = otherprocess(cbuffer);
		}
		printf("over\n");
		getchar();
	}
}
