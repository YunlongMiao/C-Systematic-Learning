#pragma once

//Ĭ�Ϻ������� �ⲿ�޷�ʹ��
//�����������Ϊ�ڲ�����
//int mySubDllTest(int a, int b);


//�ⲿ���� ��Ҫ�������� __declspec(dllexport)

__declspec(dllexport) int mySubDllTest(int a, int b);


//��̬�����ɵ�.lib�;�̬��Ĳ�ͬ����̬���е�.lib�Ὣ���еĺ���������ʵ�ֶ���������
//����̬�����ɵ�.lib ֻ��� ���������������ͱ��������������ʵ�ַ���.dll