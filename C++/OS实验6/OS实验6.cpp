#define   _CRT_SECURE_NO_WARNINGS
#define   _CRT_NONSTDC_NO_DEPRECATE

/*
* 在将显示改为数组输出显示修改的过程中失败，1个多小时没盖好
*/


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


#define MAX_LINE 100		//位示图最大行
#define MAX_COLUMN 100		//位示图最大列
using namespace std;	

int map[MAX_LINE][MAX_COLUMN];	//位示图

typedef struct file		//文件数据结构
{
	char	fileName[30];   /* 文件名字 */
	int	length;         	/* 文件长度 */
	int	start;          	/* 文件存储时 的初始位置 */
}file;



file	File[60];
int	line, column;           /* 行  列 */
int	fileTotalNum = 0;       /* 总文件数 */


void showWST() {
	printf("当前位示图为%dX%d", line, column);
	printf("\033[44;37;5m 当前位示图为↓ \033[0m\n");
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < line; j++)
		{
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}
}

/*
 * *函数名：mapInit()
 * *描述： 对位示图进行初始化
 * *参数： 无
 * *返回值： 无
 **/
void  mapInit()
{
	int i, j;
	printf("位示图初始化\n");
	printf("请输入行和列：");
	scanf("%d%d", &line, &column);

	while (line > MAX_LINE || column > MAX_COLUMN) {
		if (line > MAX_LINE) {
			printf("\033[41;37;5m 最大支持100行! \033[0m\n");
		}
		if (column > MAX_COLUMN) {
			printf("\033[41;37;5m 最大支持100列! \033[0m\n");
		}
		printf("请重新输入行和列：");
		scanf("%d%d", &line, &column);
	}

	//位示图初值赋0
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			map[i][j] = 0;
		}
	}

	printf("初始化完成");
	system("cls");

	showWST();

}



/*
 * *函数名：allocation(int fileNum)
 * *描述： 分配空间给文件，采用连续分配方式
 * *参数： fileNum  第几个文件
 * *返回值： 无
 **/
void  allocation(int fileNum)
{
	int	length = File[fileNum].length;		//记录文件长度
	int	b[MAX_LINE * MAX_COLUMN];	//记录空闲块所处位示图的位置
	int	i, j;
	int	x = 0;	//记录连续空闲块的数量
	if (length == 0) {
		
		printf("\033[41;37;5m 空文件，重新输入 \033[0m\n");
		printf("请按任意键回到主菜单");
		fileTotalNum--;
		getch();
		system("cls");
		return;
	}
	// 文件重名检测
	for (int fs = 0; fs < fileTotalNum; fs++) {
		//TODO
		if (strcmp(File[fs].fileName, File[fileNum].fileName) == 0 && fs != fileTotalNum) {
			//TODO
			printf("\033[41;37;5m 该文件已存在！ \033[0m\n");
			printf("请按任意键回到主菜单");
			fileTotalNum--;
			getch();
			system("cls");
			return;
		}
	}
	for (i = 0; i < column; i++)
	{
		for (j = 0; j < line; j++)
		{
			if (map[j][i] == 0)
			{
				b[x] = i * column + j;
				x++;
				if (x == length)
					break;  /* 这个 break ,跳出 j　循环 */
			}
			else
				continue;
		}
		if (x == length)
			break;                  /* 这里 break, 跳出整个 for循环体 */
	}

	if (length > x) {
		printf("\033[41;37;5m 空间不足，无法分配! \033[0m\n");
		printf("请按任意键回到主菜单");
		getch();
		system("cls");
	}else 
	{
		File[fileNum].start = b[0];
		for (int i = 0; i < x; i++)
		{
			int	x1 = b[i] / column;
			int	y1 = b[i] % column;
			map[y1][x1] = 1; /* 置1  代表使用 过 */
		}
	}

}


/*
 * *函数名：recovery(char s[])
 * *描述：  通过文件名回收文件占用空间，并将位示图中对应标志位重新初始化为0
 * *参数： char s[]  文件名
 * *返回值： 无
 **/
void recovery(char s[])
{
	int cnt = -1;
	for (int i = 0; i < fileTotalNum; i++)
	{
		if (strcmp(s, File[i].fileName) == 0)
		{
			cnt = i; /* 记录下  第几个 文件 */
			break;
		}
	}
	if (cnt == -1)
	{
		printf("没有此文件，请重新输入!\n");
	}
	int	start = File[cnt].start;
	int	length = File[cnt].length;
	for (int i = start; i < start + length; i++)
	{
		int	x1 = i / column;
		int	y1 = i % column;
		map[y1][x1] = 0;
	}
	for (int i = cnt + 1; i < fileTotalNum; i++) /*删除文件后 将其后面的文件前移  覆盖原来文件 */
	{
		strcpy(File[i - 1].fileName, File[i].fileName);
		File[i - 1].start = File[i].start;
		File[i - 1].length = File[i].length;
	}
	printf("回收成功\n");
	printf("按任意键返回主菜单\n");
	getch();
}


/*
 * *函数名： allocInit()
 * *描述：   分配初始化
 * *参数： 无
 * *返回值： 无
 **/
void  allocInit()
{
	printf("请输入文件名\n");
	scanf("%s", &File[fileTotalNum].fileName);
	printf("请输入文件长度\n");
	scanf("%d", &File[fileTotalNum].length);

	allocation(fileTotalNum);
	fileTotalNum++;

	showWST();
}


/*
 * *函数名： recoverInit()
 * *描述：   回收初始化
 * *参数： 无
 * *返回值： 无
 **/
void recoverInit()
{
	char name[30];
	printf("请输入回收文件名\n");
	scanf("%s", &name);
	recovery(name);
	fileTotalNum--;

	showWST();
}


/*
 * *函数名： showDir()
 * *描述：   显示所有文件信息
 * *参数： 无
 * *返回值： 无
 **/
void  showDir()
{
	if (fileTotalNum == 0) /* 文件为空时 */
		printf("没有文件，列表为空\n");
	else
		for (int i = 0; i < fileTotalNum; i++)
		{
			printf("文件名:%s\n", File[i].fileName);
			printf("开始位置:%d\n", File[i].start);

			printf("文件长度:%d\n", File[i].length);
		}
	printf("按任意键会主菜单!");
	getch();
}




int main()
{
	int mode;
	mapInit();
	while (1)
	{

		printf("1为创建文件,2为回收文件，3为显示所有文件信息\n");
		printf("请选择操作模式\n");
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:   allocInit(); break;
		case 2:   recoverInit(); break;
		case 3:   showDir(); break;
		default: printf("不存在该操作,请重新输入\n"); break;
		}
	}
}


