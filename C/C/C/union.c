#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

//�����壺�����������һ���ַ�ռ䣬��ͬʱֻ��һ������������


//����
union Myunion1 {

	char a9;
	short b10;
	int c11;
};


void UnionBasic() {

	union Myunion1 tem17;

	tem17.a9 = 0x01;	//1���ֽڣ�2^4=16
	//tem17.b10 = 0x0102;
	tem17.c11 = 0x01020304;
	tem17.b10 = 0x0102;

	printf("%x\n", tem17.b10);
}


//�ж�ϵͳ���С��

union Myunion2 {

	short num34;
	char buf[2];
};

void UnionJudge() {

	union Myunion2 tem40;
	tem40.num34 = 0x0102;
	if (tem40.buf[0] == 0x01)
		printf("���");
	else
		printf("С��");
}