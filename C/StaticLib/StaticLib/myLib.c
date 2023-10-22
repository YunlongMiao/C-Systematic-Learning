#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "myLib.h"

int myStaticLibTest(int a, int b) {

	printf("My Statci Lib Test! Add(a,b)\n");

	return a + b;
}