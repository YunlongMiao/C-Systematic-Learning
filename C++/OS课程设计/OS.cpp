#define   _CRT_SECURE_NO_WARNINGS

/*
 * 该程序使用了位图LRU置换算法
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//宏定义
#define PAGE_TABLE_SIZE 10    //页表大小
#define BITMAP_SIZE    10     //位图大小。块大小为128B，则内存大小：10*128B = 1280B
#define BLOCK_SIZE 128        //块大小为128B

//结构体
struct Page {    //页
    bool flag;                 //标志，是否存入内存
    unsigned short blockNo;    //主存块号
    unsigned short addr;       //外存地址
    bool isMod;                //修改位
};

struct JobWork {    //作业指令
    char operation[5];        //操作名称
    unsigned short PageNo;    //页号
    unsigned short UnitNo;    //单元号
};

struct LRUNode {    //LRU链表节点
    unsigned short PageNo;    //页号
    LRUNode* next;            //指向下一个节点的指针
};

//局部变量
Page PageTable[PAGE_TABLE_SIZE];    //定义页表
bool BitMap[BITMAP_SIZE];           //定义内存位图
JobWork work[20];                   //作业执行的指令序列

int PageTableNum;    //当前页表大小
int workNum;         //当前作业指令集大小

LRUNode* LRUqueue;    //LRU（最近最久未使用算法）队列

//局部函数
void Init();    //初始化，页表，位图等
unsigned short GetAddr(unsigned short curPage, unsigned short UnitNo);    //输入 页号和页内偏移，得到绝对地址
void Insert(unsigned short page);    //将最近使用的页插入到LRU队列中 或 在LRU队列中调整位置，使其始终保持最近最久未使用的页表节点在前面
int FindFreeBlock();            //在内存中查找空闲块
void DropLRUHead();             //丢弃掉LRU队列的第一个结点
void DisplayPageTable();        //打印页表
void DisplayLRUQueue();         //打印LRU队列

//主函数
int main()
{
    int i;
    Init();    //初始化

    printf("初始页表:\n");
    DisplayPageTable();
    printf("\n");
    printf("初始LRU队列:\n");
    DisplayLRUQueue();
    printf("\n");

    for (i = 0; i < workNum; i++) {    //模拟取指令
        printf("-------------------- 第%d条指令：%s -----------------------\n", i + 1, work[i].operation);
        printf("取指令\n");

        unsigned short curPage = work[i].PageNo;    //外存指令页号
        printf("取出页号：%d\n", curPage);

        //判断地址是否非法
        if (curPage<0 || curPage>PageTableNum) {    //页号非法
            printf(" 访问地址非法\n");
            return 0;
        }
        if (work[i].UnitNo < 0 || work[i].UnitNo >= BLOCK_SIZE) {    //页内偏移地址非法
            printf(" 访问地址非法\n");
            return 0;
        }

        //判断该页是否在内存
        while (PageTable[curPage].flag != 1) 
        {//不在内存
            printf(" 该页不在内存\n");
            printf(" 发出缺页中断\n");

            int freeBlock = -1; //空闲块块号
            freeBlock = FindFreeBlock();    //找内存中的空闲块。

            if (freeBlock == -1) {    
                printf(" 没有在内存中找到空闲块，调用LRU页面置换算法\n");

                unsigned short dropPage = LRUqueue->next->PageNo;    //被淘汰的页号
                printf("  获得被淘汰的页号(%d)\n", dropPage);

                if (PageTable[dropPage].isMod == 1) {    //该页修改过
                    printf("   该页修改过，将该页调到磁盘");
                    PageTable[dropPage].isMod = 0;
                }

                printf("  丢弃该页\n");
                PageTable[dropPage].flag = 0;
                DropLRUHead();    //丢弃掉LRU队列的第一个结点
                unsigned short dropBlock = PageTable[dropPage].blockNo;
                PageTable[dropPage].blockNo = -1;

                printf("  调进页(%d)到内存\n", curPage);
                Insert(curPage);        //将调进内存的页加入LRU队列
                PageTable[curPage].flag = 1;
                PageTable[curPage].blockNo = dropBlock;
            }
            else {    //找到空闲块
                //在页表中找到页号对应的页，修改标志位，赋给它内存块号

                printf("  在内存中找到空闲块，赋给给相应的页\n");
                PageTable[curPage].blockNo = freeBlock;
                PageTable[curPage].flag = 1;
                BitMap[freeBlock] = 1;      //将内存位图对应位置 置1
                Insert(curPage);            //将调进内存的页加入LRU队列
            }

        }

        //该页在内存，形成并输出绝对地址
        printf(" 该页在内存中\n");
        unsigned short absAddr = GetAddr(curPage, work[i].UnitNo);//输入页号和页内偏移，得到绝对地址
        Insert(curPage);    //调整内存页排序表(LRU队列)

        if (strcmp(work[i].operation, "存") == 0)    //字符比较
        {
            //如果是存指令
            printf("  是存指令,置该页的修改位为 1\n");
            PageTable[curPage].isMod = 1;
        }

        printf("绝对地址为:0x%04X\n", absAddr);
        printf("\n");
        printf("当前页表:\n");
        DisplayPageTable();
        printf("\n");
        printf("当前LRU队列:\n");
        DisplayLRUQueue();
        printf("-----------------------------------------------------------\n");
        printf("\n");

    }
    return 0;
}

//函数实现

//将最近使用的页插入到LRU队列中 或 在LRU队列中调整位置，使其始终保持最近最久未使用的页表节点在前面
void Insert(unsigned short page)    
{
    //查找链表，如果找到page，将代表该page的节点移到链表最后，说明刚刚使用过该页
    LRUNode* p = LRUqueue;
    while (p->next != NULL) {
        if (p->next->PageNo == page) {
            //找到该节点，将其移动到LRU链表最后
            LRUNode* t = p->next;
            p->next = t->next;      //page所在节点被page->next替换，page移至链表最后
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = t;
            t->next = NULL;
            return;
        }
        p = p->next;
    }
    //如果没有找到page，则创建一个代表该page的节点，加入到LRU链表最后
    if (p->PageNo != page) {
        LRUNode* t = new LRUNode;    //创建节点
        t->PageNo = page;
        t->next = NULL;
        p->next = t;
    }
    //最后一个节点是page的情况不用考虑，因为它本身就在最后，不用移位
    return;
}



//初始化，页表，位图等
void Init()    
{
    memset(PageTable, 0, sizeof(PageTable));    //页表置0
    memset(BitMap, 0, sizeof(BitMap));          //内存位图置0
    PageTableNum = 0;
    workNum = 0;
    LRUqueue = new LRUNode; //创建LRU链表
    LRUqueue->next = NULL;

    //初始化页表
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

    //初始化作业
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

    strcpy(work[3].operation, "存");
    work[3].PageNo = 3;
    work[3].UnitNo = 021;
    workNum++;

    strcpy(work[4].operation, "取");
    work[4].PageNo = 0;
    work[4].UnitNo = 057;
    workNum++;

    strcpy(work[5].operation, "-");
    work[5].PageNo = 6;
    work[5].UnitNo = 040;
    workNum++;

    strcpy(work[6].operation, "移位");
    work[6].PageNo = 4;
    work[6].UnitNo = 053;
    workNum++;

    strcpy(work[7].operation, "+");
    work[7].PageNo = 5;
    work[7].UnitNo = 023;
    workNum++;

    strcpy(work[8].operation, "存");
    work[8].PageNo = 1;
    work[8].UnitNo = 037;
    workNum++;

    strcpy(work[9].operation, "取");
    work[9].PageNo = 2;
    work[9].UnitNo = 076;
    workNum++;

    strcpy(work[10].operation, "+");
    work[10].PageNo = 4;
    work[10].UnitNo = 001;
    workNum++;

    strcpy(work[11].operation, "取");
    work[11].PageNo = 6;
    work[11].UnitNo = 074;
    workNum++;

    //将剩余的内存置为非空，即预先设定内存没有空闲位
    int i;
    for (i = 0; i < BITMAP_SIZE; i++) {
        if (!BitMap[i])
            BitMap[i] = 1;
    }

    return;
}


//输入页号和页内偏移，得到绝对地址
unsigned short GetAddr(unsigned short curPage, unsigned short UnitNo)    
{
    unsigned short absAddr = 0;    //结果

    unsigned short curBlock = PageTable[curPage].blockNo;    //取块号
    absAddr = curBlock * BLOCK_SIZE + UnitNo;

    return absAddr;
}


//在内存中查找空闲块
int FindFreeBlock()
{
    int i;
    for (i = 0; i < BITMAP_SIZE; i++) {
        if (BitMap[i] == 0) {    //找到空闲块，返回块号
            return i;
        }
    }
    return -1;    //没找到
}


//丢弃掉LRU队列的第一个结点
void DropLRUHead()                    
{
    LRUNode* t = LRUqueue->next;
    LRUqueue->next = t->next;
    free(t);
}



//打印页表
void DisplayPageTable()    
{
    int i;
    printf("页号\t标志\t内存块号\t外存地址\t修改值\n");
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



//打印LRU队列
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