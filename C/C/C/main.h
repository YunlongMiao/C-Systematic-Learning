#pragma once	//防止头文件重复

#ifndef MAIN_H
#define MAIN_H

//结构体练习部分
void Struct();	

//内存部分
void AddrNum();
void Memoryset();
void Memorycpy();
void Memorycmp();

void MemoryMalloc();
void MemoryAddrTest();
void MemoryHeapTest();
void MemoryPollutionTest();

//结构体部分
void StructBasic();
void StructArray();//结构体数组
void StructMultiple();	//结构体套结构体
void StructAssignment();	//结构体赋值
void StructPoint();//结构体指针
void StructMultiplePoint();//结构体套指针
void StructArrayParameter();//结构体作为函数形参

//共用体部分
void UnionBasic();//基础
void UnionJudge();//判断系统大端小端

//枚举部分
void EnumBasic(); //枚举基础

//文件操作
void FileFopenWrite();//fopen:打开一个文件，写
void FileFopenRead();//读，内容为纯文本
void FileFopenRead1();//读，内容任意
void PrintfTest();//fprintf、fscanf:字符格式化函数
void ScanfTest();//fscanf、sscanf
void FwriteFile();//fwrite:写文件
void FreadFile();//fread:读文件
void FseekFile();//fseek:移动光标
#endif