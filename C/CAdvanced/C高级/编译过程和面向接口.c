#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
预处理指令
*/

/*
1.头文件包含
"自定义"		<系统头文件>

2.宏定义
宏常量 不重视作用域
没有数据类型
可以利用 undef卸载宏
宏函数 用于频繁短小函数 封装为宏函数
声明时候 主要保证运算完整性

3.条件编译

4.特殊宏

*/

//3.条件编译

#define First 1
#define DEBUG

#ifdef DEBUG

#if First

void func34() {
	printf("#if  func34\n");
}

#else

void func38() {
	printf("#else  func38\n");
}

#endif


#else


void func50() {
	printf("func50\n");
}


#endif // DEBUG




//特殊宏

void specialMacro1(char* p) {

	if (p == NULL)
	{
		printf("文件:%s的%d行出错！\n", __FILE__, __LINE__);
		printf("日期：%s\n", __DATE__);
		printf("时间：%s\n", __TIME__);

		return;
	}
}

void specialMacroTest() {

	specialMacro1(NULL);

}