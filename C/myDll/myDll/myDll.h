#pragma once

//默认函数声明 外部无法使用
//将这个函数称为内部函数
//int mySubDllTest(int a, int b);


//外部函数 需要特殊声明 __declspec(dllexport)

__declspec(dllexport) int mySubDllTest(int a, int b);


//动态库生成的.lib和静态库的不同，静态库中的.lib会将所有的函数声明、实现都放入其中
//而动态库生成的.lib 只会放 导出函数的声明和变量声明，具体的实现放在.dll