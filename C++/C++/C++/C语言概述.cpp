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
	//count是标准的输出流对象，打印字符串
	//endl是刷新缓冲区，并换行
	std::cout << "Hello World!\n";
	cout << "hello world" << endl;
	cout << "st=" << st << endl;
	cout << "::st=" << ::st << endl;	//作用域运算符
	cout << "maker=" << Maker::a << endl;
	cout << "maker::B::b" << Maker::B::b << endl;

	//命名空间取别名
	namespace nameMaker = Maker;
	cout << "nameMaker::a=" << nameMaker::a << endl;
}