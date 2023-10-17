#define   _CRT_SECURE_NO_WARNINGS	//c4996
#include<stdio.h>	//标准输入输出
#include<string.h>	//字符串处理函数
#include<stdlib.h>	//标准库函数
#include"main.h"



int main() {

//变量和内存分布
 
	////数据类型别名：typedef
	//TypedefTest();

	////void数据类型
	//VoidTest();

	////sizeof操作符
	//SizeofTest();

	////修改变量的两种方式
	//VariableTest();

	////内存分区模型-栈区
	//StackAreaTest();

	////内存分区模型-堆区
	//HeapAreaTest();

	////calloc和realloc函数
	//CallocReallocTest();

	////栈的生长方向和内存存放方向
	//StackMemoryDirection();


//指针强化

	////指针变量
	//PointVariableTest();

	////野指针和空指针
	//OtherPointTest();

	////间接访问操作符
	//VisitOperatorTest();

	////指针的步长
	//PointStepSizeTest();

	////字符串注意事项
	//StrAttentionTest();

	////字符串练习
	//StrExercisesTest();

	////字符串格式化
	//StrFormattingTest();

	////分割姓名
	//StrFormattingTest_T();

	////字符串强化-子串查找
	//StrStrengthenFindTest();

	////一级指针易错点
	//FirstOrderPointerTest();

	////二级指针的输出特性
	//SecondOrderPointerOutputTest();

	////二级指针的输入特性
	//SecondOrderPointerInputTest();

	////二级指针做函数参数的输出特性
	//SecondOrderPointerParameterOutputTest();

	//二级指针练习 - 文件读写---着重理解
	SecondOrderPointerFileRWTest(); 

	system("pause");
	return EXIT_SUCCESS;
}
