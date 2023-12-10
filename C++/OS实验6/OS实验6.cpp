#define   _CRT_SECURE_NO_WARNINGS
#define   _CRT_NONSTDC_NO_DEPRECATE

/*
* �ڽ���ʾ��Ϊ���������ʾ�޸ĵĹ�����ʧ�ܣ�1����Сʱû�Ǻ�
*/


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


#define MAX_LINE 100		//λʾͼ�����
#define MAX_COLUMN 100		//λʾͼ�����
using namespace std;	

int map[MAX_LINE][MAX_COLUMN];	//λʾͼ

typedef struct file		//�ļ����ݽṹ
{
	char	fileName[30];   /* �ļ����� */
	int	length;         	/* �ļ����� */
	int	start;          	/* �ļ��洢ʱ �ĳ�ʼλ�� */
}file;



file	File[60];
int	line, column;           /* ��  �� */
int	fileTotalNum = 0;       /* ���ļ��� */


void showWST() {
	printf("��ǰλʾͼΪ%dX%d", line, column);
	printf("\033[44;37;5m ��ǰλʾͼΪ�� \033[0m\n");
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
 * *��������mapInit()
 * *������ ��λʾͼ���г�ʼ��
 * *������ ��
 * *����ֵ�� ��
 **/
void  mapInit()
{
	int i, j;
	printf("λʾͼ��ʼ��\n");
	printf("�������к��У�");
	scanf("%d%d", &line, &column);

	while (line > MAX_LINE || column > MAX_COLUMN) {
		if (line > MAX_LINE) {
			printf("\033[41;37;5m ���֧��100��! \033[0m\n");
		}
		if (column > MAX_COLUMN) {
			printf("\033[41;37;5m ���֧��100��! \033[0m\n");
		}
		printf("�����������к��У�");
		scanf("%d%d", &line, &column);
	}

	//λʾͼ��ֵ��0
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			map[i][j] = 0;
		}
	}

	printf("��ʼ�����");
	system("cls");

	showWST();

}



/*
 * *��������allocation(int fileNum)
 * *������ ����ռ���ļ��������������䷽ʽ
 * *������ fileNum  �ڼ����ļ�
 * *����ֵ�� ��
 **/
void  allocation(int fileNum)
{
	int	length = File[fileNum].length;		//��¼�ļ�����
	int	b[MAX_LINE * MAX_COLUMN];	//��¼���п�����λʾͼ��λ��
	int	i, j;
	int	x = 0;	//��¼�������п������
	if (length == 0) {
		
		printf("\033[41;37;5m ���ļ����������� \033[0m\n");
		printf("�밴������ص����˵�");
		fileTotalNum--;
		getch();
		system("cls");
		return;
	}
	// �ļ��������
	for (int fs = 0; fs < fileTotalNum; fs++) {
		//TODO
		if (strcmp(File[fs].fileName, File[fileNum].fileName) == 0 && fs != fileTotalNum) {
			//TODO
			printf("\033[41;37;5m ���ļ��Ѵ��ڣ� \033[0m\n");
			printf("�밴������ص����˵�");
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
					break;  /* ��� break ,���� j��ѭ�� */
			}
			else
				continue;
		}
		if (x == length)
			break;                  /* ���� break, �������� forѭ���� */
	}

	if (length > x) {
		printf("\033[41;37;5m �ռ䲻�㣬�޷�����! \033[0m\n");
		printf("�밴������ص����˵�");
		getch();
		system("cls");
	}else 
	{
		File[fileNum].start = b[0];
		for (int i = 0; i < x; i++)
		{
			int	x1 = b[i] / column;
			int	y1 = b[i] % column;
			map[y1][x1] = 1; /* ��1  ����ʹ�� �� */
		}
	}

}


/*
 * *��������recovery(char s[])
 * *������  ͨ���ļ��������ļ�ռ�ÿռ䣬����λʾͼ�ж�Ӧ��־λ���³�ʼ��Ϊ0
 * *������ char s[]  �ļ���
 * *����ֵ�� ��
 **/
void recovery(char s[])
{
	int cnt = -1;
	for (int i = 0; i < fileTotalNum; i++)
	{
		if (strcmp(s, File[i].fileName) == 0)
		{
			cnt = i; /* ��¼��  �ڼ��� �ļ� */
			break;
		}
	}
	if (cnt == -1)
	{
		printf("û�д��ļ�������������!\n");
	}
	int	start = File[cnt].start;
	int	length = File[cnt].length;
	for (int i = start; i < start + length; i++)
	{
		int	x1 = i / column;
		int	y1 = i % column;
		map[y1][x1] = 0;
	}
	for (int i = cnt + 1; i < fileTotalNum; i++) /*ɾ���ļ��� ���������ļ�ǰ��  ����ԭ���ļ� */
	{
		strcpy(File[i - 1].fileName, File[i].fileName);
		File[i - 1].start = File[i].start;
		File[i - 1].length = File[i].length;
	}
	printf("���ճɹ�\n");
	printf("��������������˵�\n");
	getch();
}


/*
 * *�������� allocInit()
 * *������   �����ʼ��
 * *������ ��
 * *����ֵ�� ��
 **/
void  allocInit()
{
	printf("�������ļ���\n");
	scanf("%s", &File[fileTotalNum].fileName);
	printf("�������ļ�����\n");
	scanf("%d", &File[fileTotalNum].length);

	allocation(fileTotalNum);
	fileTotalNum++;

	showWST();
}


/*
 * *�������� recoverInit()
 * *������   ���ճ�ʼ��
 * *������ ��
 * *����ֵ�� ��
 **/
void recoverInit()
{
	char name[30];
	printf("����������ļ���\n");
	scanf("%s", &name);
	recovery(name);
	fileTotalNum--;

	showWST();
}


/*
 * *�������� showDir()
 * *������   ��ʾ�����ļ���Ϣ
 * *������ ��
 * *����ֵ�� ��
 **/
void  showDir()
{
	if (fileTotalNum == 0) /* �ļ�Ϊ��ʱ */
		printf("û���ļ����б�Ϊ��\n");
	else
		for (int i = 0; i < fileTotalNum; i++)
		{
			printf("�ļ���:%s\n", File[i].fileName);
			printf("��ʼλ��:%d\n", File[i].start);

			printf("�ļ�����:%d\n", File[i].length);
		}
	printf("������������˵�!");
	getch();
}




int main()
{
	int mode;
	mapInit();
	while (1)
	{

		printf("1Ϊ�����ļ�,2Ϊ�����ļ���3Ϊ��ʾ�����ļ���Ϣ\n");
		printf("��ѡ�����ģʽ\n");
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:   allocInit(); break;
		case 2:   recoverInit(); break;
		case 3:   showDir(); break;
		default: printf("�����ڸò���,����������\n"); break;
		}
	}
}


