#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
Ԥ����ָ��
*/

/*
1.ͷ�ļ�����
"�Զ���"		<ϵͳͷ�ļ�>

2.�궨��
�곣�� ������������
û����������
�������� undefж�غ�
�꺯�� ����Ƶ����С���� ��װΪ�꺯��
����ʱ�� ��Ҫ��֤����������

3.��������

4.�����

*/

//3.��������

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




//�����

void specialMacro1(char* p) {

	if (p == NULL)
	{
		printf("�ļ�:%s��%d�г���\n", __FILE__, __LINE__);
		printf("���ڣ�%s\n", __DATE__);
		printf("ʱ�䣺%s\n", __TIME__);

		return;
	}
}

void specialMacroTest() {

	specialMacro1(NULL);

}