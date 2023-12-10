#define   _CRT_SECURE_NO_WARNINGS

/*
 * �ó���ʹ����λͼLRU�û��㷨
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//�궨��
#define PAGE_TABLE_SIZE 10    //ҳ���С
#define BITMAP_SIZE    10     //λͼ��С�����СΪ128B�����ڴ��С��10*128B = 1280B
#define BLOCK_SIZE 128        //���СΪ128B

//�ṹ��
struct Page {    //ҳ
    bool flag;                 //��־���Ƿ�����ڴ�
    unsigned short blockNo;    //������
    unsigned short addr;       //����ַ
    bool isMod;                //�޸�λ
};

struct JobWork {    //��ҵָ��
    char operation[5];        //��������
    unsigned short PageNo;    //ҳ��
    unsigned short UnitNo;    //��Ԫ��
};

struct LRUNode {    //LRU����ڵ�
    unsigned short PageNo;    //ҳ��
    LRUNode* next;            //ָ����һ���ڵ��ָ��
};

//�ֲ�����
Page PageTable[PAGE_TABLE_SIZE];    //����ҳ��
bool BitMap[BITMAP_SIZE];           //�����ڴ�λͼ
JobWork work[20];                   //��ҵִ�е�ָ������

int PageTableNum;    //��ǰҳ���С
int workNum;         //��ǰ��ҵָ���С

LRUNode* LRUqueue;    //LRU��������δʹ���㷨������

//�ֲ�����
void Init();    //��ʼ����ҳ��λͼ��
unsigned short GetAddr(unsigned short curPage, unsigned short UnitNo);    //���� ҳ�ź�ҳ��ƫ�ƣ��õ����Ե�ַ
void Insert(unsigned short page);    //�����ʹ�õ�ҳ���뵽LRU������ �� ��LRU�����е���λ�ã�ʹ��ʼ�ձ���������δʹ�õ�ҳ��ڵ���ǰ��
int FindFreeBlock();            //���ڴ��в��ҿ��п�
void DropLRUHead();             //������LRU���еĵ�һ�����
void DisplayPageTable();        //��ӡҳ��
void DisplayLRUQueue();         //��ӡLRU����

//������
int main()
{
    int i;
    Init();    //��ʼ��

    printf("��ʼҳ��:\n");
    DisplayPageTable();
    printf("\n");
    printf("��ʼLRU����:\n");
    DisplayLRUQueue();
    printf("\n");

    for (i = 0; i < workNum; i++) {    //ģ��ȡָ��
        printf("-------------------- ��%d��ָ�%s -----------------------\n", i + 1, work[i].operation);
        printf("ȡָ��\n");

        unsigned short curPage = work[i].PageNo;    //���ָ��ҳ��
        printf("ȡ��ҳ�ţ�%d\n", curPage);

        //�жϵ�ַ�Ƿ�Ƿ�
        if (curPage<0 || curPage>PageTableNum) {    //ҳ�ŷǷ�
            printf(" ���ʵ�ַ�Ƿ�\n");
            return 0;
        }
        if (work[i].UnitNo < 0 || work[i].UnitNo >= BLOCK_SIZE) {    //ҳ��ƫ�Ƶ�ַ�Ƿ�
            printf(" ���ʵ�ַ�Ƿ�\n");
            return 0;
        }

        //�жϸ�ҳ�Ƿ����ڴ�
        while (PageTable[curPage].flag != 1) 
        {//�����ڴ�
            printf(" ��ҳ�����ڴ�\n");
            printf(" ����ȱҳ�ж�\n");

            int freeBlock = -1; //���п���
            freeBlock = FindFreeBlock();    //���ڴ��еĿ��п顣

            if (freeBlock == -1) {    
                printf(" û�����ڴ����ҵ����п飬����LRUҳ���û��㷨\n");

                unsigned short dropPage = LRUqueue->next->PageNo;    //����̭��ҳ��
                printf("  ��ñ���̭��ҳ��(%d)\n", dropPage);

                if (PageTable[dropPage].isMod == 1) {    //��ҳ�޸Ĺ�
                    printf("   ��ҳ�޸Ĺ�������ҳ��������");
                    PageTable[dropPage].isMod = 0;
                }

                printf("  ������ҳ\n");
                PageTable[dropPage].flag = 0;
                DropLRUHead();    //������LRU���еĵ�һ�����
                unsigned short dropBlock = PageTable[dropPage].blockNo;
                PageTable[dropPage].blockNo = -1;

                printf("  ����ҳ(%d)���ڴ�\n", curPage);
                Insert(curPage);        //�������ڴ��ҳ����LRU����
                PageTable[curPage].flag = 1;
                PageTable[curPage].blockNo = dropBlock;
            }
            else {    //�ҵ����п�
                //��ҳ�����ҵ�ҳ�Ŷ�Ӧ��ҳ���޸ı�־λ���������ڴ���

                printf("  ���ڴ����ҵ����п飬��������Ӧ��ҳ\n");
                PageTable[curPage].blockNo = freeBlock;
                PageTable[curPage].flag = 1;
                BitMap[freeBlock] = 1;      //���ڴ�λͼ��Ӧλ�� ��1
                Insert(curPage);            //�������ڴ��ҳ����LRU����
            }

        }

        //��ҳ���ڴ棬�γɲ�������Ե�ַ
        printf(" ��ҳ���ڴ���\n");
        unsigned short absAddr = GetAddr(curPage, work[i].UnitNo);//����ҳ�ź�ҳ��ƫ�ƣ��õ����Ե�ַ
        Insert(curPage);    //�����ڴ�ҳ�����(LRU����)

        if (strcmp(work[i].operation, "��") == 0)    //�ַ��Ƚ�
        {
            //����Ǵ�ָ��
            printf("  �Ǵ�ָ��,�ø�ҳ���޸�λΪ 1\n");
            PageTable[curPage].isMod = 1;
        }

        printf("���Ե�ַΪ:0x%04X\n", absAddr);
        printf("\n");
        printf("��ǰҳ��:\n");
        DisplayPageTable();
        printf("\n");
        printf("��ǰLRU����:\n");
        DisplayLRUQueue();
        printf("-----------------------------------------------------------\n");
        printf("\n");

    }
    return 0;
}

//����ʵ��

//�����ʹ�õ�ҳ���뵽LRU������ �� ��LRU�����е���λ�ã�ʹ��ʼ�ձ���������δʹ�õ�ҳ��ڵ���ǰ��
void Insert(unsigned short page)    
{
    //������������ҵ�page���������page�Ľڵ��Ƶ��������˵���ո�ʹ�ù���ҳ
    LRUNode* p = LRUqueue;
    while (p->next != NULL) {
        if (p->next->PageNo == page) {
            //�ҵ��ýڵ㣬�����ƶ���LRU�������
            LRUNode* t = p->next;
            p->next = t->next;      //page���ڽڵ㱻page->next�滻��page�����������
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = t;
            t->next = NULL;
            return;
        }
        p = p->next;
    }
    //���û���ҵ�page���򴴽�һ�������page�Ľڵ㣬���뵽LRU�������
    if (p->PageNo != page) {
        LRUNode* t = new LRUNode;    //�����ڵ�
        t->PageNo = page;
        t->next = NULL;
        p->next = t;
    }
    //���һ���ڵ���page��������ÿ��ǣ���Ϊ�����������󣬲�����λ
    return;
}



//��ʼ����ҳ��λͼ��
void Init()    
{
    memset(PageTable, 0, sizeof(PageTable));    //ҳ����0
    memset(BitMap, 0, sizeof(BitMap));          //�ڴ�λͼ��0
    PageTableNum = 0;
    workNum = 0;
    LRUqueue = new LRUNode; //����LRU����
    LRUqueue->next = NULL;

    //��ʼ��ҳ��
    PageTable[0].flag = 1;
    PageTable[0].blockNo = 5;
    PageTable[0].addr = 0x0011;
    PageTable[0].isMod = 1;
    Insert(0);
    PageTableNum++;

    PageTable[1].flag = 1;
    PageTable[1].blockNo = 8;
    PageTable[1].addr = 0x0012;
    PageTable[1].isMod = 1;
    Insert(1);
    PageTableNum++;

    PageTable[2].flag = 1;
    PageTable[2].blockNo = 9;
    PageTable[2].addr = 0x0013;
    PageTable[2].isMod = 0;
    Insert(2);
    PageTableNum++;

    PageTable[3].flag = 1;
    PageTable[3].blockNo = 1;
    PageTable[3].addr = 0x0021;
    PageTable[3].isMod = 0;
    Insert(3);
    PageTableNum++;

    PageTable[4].flag = 0;
    PageTable[4].blockNo = -1;
    PageTable[4].addr = 0x0022;
    PageTable[4].isMod = 0;
    PageTableNum++;

    PageTable[5].flag = 0;
    PageTable[5].blockNo = -1;
    PageTable[5].addr = 0x0023;
    PageTable[5].isMod = 0;
    PageTableNum++;

    PageTable[6].flag = 0;
    PageTable[6].blockNo = -1;
    PageTable[6].addr = 0x0121;
    PageTable[6].isMod = 0;
    PageTableNum++;

    //��ʼ����ҵ
    strcpy(work[0].operation, "+");
    work[0].PageNo = 0;
    work[0].UnitNo = 070;
    workNum++;

    strcpy(work[1].operation, "+");
    work[1].PageNo = 1;
    work[1].UnitNo = 050;
    workNum++;

    strcpy(work[2].operation, "*");
    work[2].PageNo = 2;
    work[2].UnitNo = 015;
    workNum++;

    strcpy(work[3].operation, "��");
    work[3].PageNo = 3;
    work[3].UnitNo = 021;
    workNum++;

    strcpy(work[4].operation, "ȡ");
    work[4].PageNo = 0;
    work[4].UnitNo = 057;
    workNum++;

    strcpy(work[5].operation, "-");
    work[5].PageNo = 6;
    work[5].UnitNo = 040;
    workNum++;

    strcpy(work[6].operation, "��λ");
    work[6].PageNo = 4;
    work[6].UnitNo = 053;
    workNum++;

    strcpy(work[7].operation, "+");
    work[7].PageNo = 5;
    work[7].UnitNo = 023;
    workNum++;

    strcpy(work[8].operation, "��");
    work[8].PageNo = 1;
    work[8].UnitNo = 037;
    workNum++;

    strcpy(work[9].operation, "ȡ");
    work[9].PageNo = 2;
    work[9].UnitNo = 076;
    workNum++;

    strcpy(work[10].operation, "+");
    work[10].PageNo = 4;
    work[10].UnitNo = 001;
    workNum++;

    strcpy(work[11].operation, "ȡ");
    work[11].PageNo = 6;
    work[11].UnitNo = 074;
    workNum++;

    //��ʣ����ڴ���Ϊ�ǿգ���Ԥ���趨�ڴ�û�п���λ
    int i;
    for (i = 0; i < BITMAP_SIZE; i++) {
        if (!BitMap[i])
            BitMap[i] = 1;
    }

    return;
}


//����ҳ�ź�ҳ��ƫ�ƣ��õ����Ե�ַ
unsigned short GetAddr(unsigned short curPage, unsigned short UnitNo)    
{
    unsigned short absAddr = 0;    //���

    unsigned short curBlock = PageTable[curPage].blockNo;    //ȡ���
    absAddr = curBlock * BLOCK_SIZE + UnitNo;

    return absAddr;
}


//���ڴ��в��ҿ��п�
int FindFreeBlock()
{
    int i;
    for (i = 0; i < BITMAP_SIZE; i++) {
        if (BitMap[i] == 0) {    //�ҵ����п飬���ؿ��
            return i;
        }
    }
    return -1;    //û�ҵ�
}


//������LRU���еĵ�һ�����
void DropLRUHead()                    
{
    LRUNode* t = LRUqueue->next;
    LRUqueue->next = t->next;
    free(t);
}



//��ӡҳ��
void DisplayPageTable()    
{
    int i;
    printf("ҳ��\t��־\t�ڴ���\t����ַ\t�޸�ֵ\n");
    for (i = 0; i < PageTableNum; i++) {
        printf("%d\t", i);
        printf("%d\t", PageTable[i].flag);
        if (PageTable[i].blockNo == 65535) {
            printf("-\t\t");
        }
        else {
            printf("%d\t\t", PageTable[i].blockNo);
        }
        printf("0x%03x\t\t", PageTable[i].addr);
        printf("%d\n", PageTable[i].isMod);
    }
    return;
}



//��ӡLRU����
void DisplayLRUQueue()       
{
    LRUNode* q = LRUqueue->next;
    while (q != NULL) {
        if (q->next == NULL)
            printf("%d\n", q->PageNo);
        else
            printf("%d->", q->PageNo);
        q = q->next;
    }
}