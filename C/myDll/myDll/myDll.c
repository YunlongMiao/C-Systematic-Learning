#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


__declspec(dllexport) int mySubDllTest(int a, int b) {

	printf("�ҵĶ�̬�����! Add(a,b)\n");

	return a + b;
}