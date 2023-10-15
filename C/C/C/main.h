#pragma once	//��ֹͷ�ļ��ظ�

#ifndef MAIN_H
#define MAIN_H

//�ṹ����ϰ����
void Struct();	

//�ڴ沿��
void AddrNum();
void Memoryset();
void Memorycpy();
void Memorycmp();

void MemoryMalloc();
void MemoryAddrTest();
void MemoryHeapTest();
void MemoryPollutionTest();

//�ṹ�岿��
void StructBasic();
void StructArray();//�ṹ������
void StructMultiple();	//�ṹ���׽ṹ��
void StructAssignment();	//�ṹ�帳ֵ
void StructPoint();//�ṹ��ָ��
void StructMultiplePoint();//�ṹ����ָ��
void StructArrayParameter();//�ṹ����Ϊ�����β�

//�����岿��
void UnionBasic();//����
void UnionJudge();//�ж�ϵͳ���С��

//ö�ٲ���
void EnumBasic(); //ö�ٻ���

//�ļ�����
void FileFopenWrite();//fopen:��һ���ļ���д
void FileFopenRead();//��������Ϊ���ı�
void FileFopenRead1();//������������
void PrintfTest();//fprintf��fscanf:�ַ���ʽ������
void ScanfTest();//fscanf��sscanf
void FwriteFile();//fwrite:д�ļ�
void FreadFile();//fread:���ļ�
void FseekFile();//fseek:�ƶ����
#endif