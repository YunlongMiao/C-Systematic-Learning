﻿#define   _CRT_SECURE_NO_WARNINGS	//c4996
#include<stdio.h>	//标准输入输出
#include<string.h>	//字符串处理函数
#include<stdlib.h>	//标准库函数
#include "main.h"

#pragma comment(lib,"./myDll.lib")	//链接动态库，可以不导入
#pragma comment(lib,"./StaticLib.lib")

#include "myLib.h"
#include "myDll.h"


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

	////二级指针练习 - 文件读写---着重理解
	//SecondOrderPointerFileRWTest(); 

	////位运算
	//bitOperationTest();

	////一维数组名称
	//oneDimensionalArrayTest();

	////数组指针的定义
	//arrayPointTest();

	////二维数组数组名
	//twoDimensionalArrayTest();

	////选择排序
	//selectionSortTest();



//结构体和文件的高级用法
 
	////结构体嵌套一级指针
	//structNestTest();

	////结构体嵌套二级指针
	//strcutNestTwoPoint();

	////结构体偏移量
	//structOffsetTest();

	////内存对齐
	//memoryAligningTest();

	////文件读写
	//fileWRTest();


//链表和回调函数


	////链表操作
	//linkListTest();

	////函数指针
	//funcPoint();

	////回调函数-类型
	//callBackTypeTest();

	////回调函数-数组
	//callBackArrayTest();

	////回调函数-查找数组
	//callBackFindArrayTest();



//编译过程和面向接口

	////4.特殊宏
	//specialMacroTest();

	//静态库测试
	printf("%d\n", myStaticLibTest(60, 20));

	//动态库测试
	printf("%d\n", mySubDllTest(60, 30));

	system("pause");
	return EXIT_SUCCESS;
}
