#define   _CRT_SECURE_NO_WARNINGS
//#pragma once
#ifndef __dynamicArray_h
#define __dynamicArray_h


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*
��̬����
*/


//��̬����ṹ��
struct dynamicArray {

	//��ʵ�ڶ������������ָ��
	void** pAddr;

	//��������
	int m_Capacity;

	////�����С
	int m_Size;
};


//��ʼ������  ���� ��ʼ��������   ����ֵ ����ָ��
struct dynamicArray* init_dynamicArray(int capacity);

//����Ԫ��
void insert_dynamicArray(struct dynamicArray* arr, void* data, int pos);

//��������
void foreach_dynamicArray(struct dynamicArray* arr, void(*myPrint)(void*));

//ɾ���������ݣ�����λ��
void removeByPos_dynamicArray(struct dynamicArray* arr, int pos);

//����ֵ ��ɾ������������
void removeByValue_dynamicArray(struct dynamicArray* arr, void* data, int(*myCompare)(void*, void*));

//��������
void destroy_dynamicArray(struct dynamicArray* arr);







/*
����
*/


//�ص�����
void myPrint(void* data, void(*mp)(void*));
void printInt(void* data);
void printDouble(void* data);
void printPerson(void* data);
int comparaPerson(void* data1, void* data2);

void test02();








#endif