#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>


//枚举基础

enum ab{SUN,RAIN = 20,SNOW};	//取代宏定义

typedef enum ab allb;
typedef unsigned int u32;

void EnumBasic() {

	printf("%d %d %d\n", SUN, RAIN, SNOW);
}