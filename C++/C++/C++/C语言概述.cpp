#include"main.h"


namespace Maker 
{
	int a = 10;
	namespace B
	{
		int b = 250;
	}
}

int st = 1500;

void myMaker1::printHelloWorld() {

	int st = 120;
	//count�Ǳ�׼����������󣬴�ӡ�ַ���
	//endl��ˢ�»�������������
	std::cout << "Hello World!\n";
	cout << "hello world" << endl;
	cout << "st=" << st << endl;
	cout << "::st=" << ::st << endl;	//�����������
	cout << "maker=" << Maker::a << endl;
	cout << "maker::B::b" << Maker::B::b << endl;

	//�����ռ�ȡ����
	namespace nameMaker = Maker;
	cout << "nameMaker::a=" << nameMaker::a << endl;
}