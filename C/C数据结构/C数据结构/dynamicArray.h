#define   _CRT_SECURE_NO_WARNINGS
//#pragma once
#ifndef __dynamicArray_h
#define __dynamicArray_h


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*
动态数组
*/


//动态数组结构体
struct dynamicArray {

	//真实在堆区开辟数组的指针
	void** pAddr;

	//数组容量
	int m_Capacity;

	////数组大小
	int m_Size;
};


//初始化数组  参数 初始数组容量   返回值 数组指针
struct dynamicArray* init_dynamicArray(int capacity);

//插入元素
void insert_dynamicArray(struct dynamicArray* arr, void* data, int pos);

//遍历数组
void foreach_dynamicArray(struct dynamicArray* arr, void(*myPrint)(void*));

//删除数组数据，按照位置
void removeByPos_dynamicArray(struct dynamicArray* arr, int pos);

//按照值 来删除数组中数据
void removeByValue_dynamicArray(struct dynamicArray* arr, void* data, int(*myCompare)(void*, void*));

//销毁数组
void destroy_dynamicArray(struct dynamicArray* arr);







/*
测试
*/


//回调函数
void myPrint(void* data, void(*mp)(void*));
void printInt(void* data);
void printDouble(void* data);
void printPerson(void* data);
int comparaPerson(void* data1, void* data2);

void test02();








#endif