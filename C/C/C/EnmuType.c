#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>


//ö�ٻ���

enum ab{SUN,RAIN = 20,SNOW};	//ȡ���궨��

typedef enum ab allb;
typedef unsigned int u32;

void EnumBasic() {

	printf("%d %d %d\n", SUN, RAIN, SNOW);
}