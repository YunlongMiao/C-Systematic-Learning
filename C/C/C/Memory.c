#define   _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int e;
static int f;
int g = 10;
static int h = 10;

//���ֱ����洢λ��
void AddrNum()
{
	int a;
	int b = 10;
	static int c;
	static int d = 10;
	char* i = "test";
	char* k = NULL;

	printf("&a\t %p\t //�ֲ�δ��ʼ������\n", &a);
	printf("&b\t %p\t //�ֲ���ʼ������\n", &b);

	printf("&c\t %p\t //��̬�ֲ�δ��ʼ������\n", &c);
	printf("&d\t %p\t //��̬�ֲ���ʼ������\n", &d);

	printf("&e\t %p\t //ȫ��δ��ʼ������\n", &e);
	printf("&f\t %p\t //ȫ�־�̬δ��ʼ������\n", &f);

	printf("&g\t %p\t //ȫ�ֳ�ʼ������\n", &g);
	printf("&h\t %p\t //ȫ�־�̬��ʼ������\n", &h);

	printf("i\t %p\t //ֻ������(���ֳ�����)\n", i);

	k = (char*)malloc(10);
	printf("k\t %p\t //��̬������ڴ�\n", k);

	return 0;
}


//�ڴ�����
void Memoryset() {

	int a = 10;
	char buf[10] = "";

	strcpy(buf, "hello");
	printf("%s\n", buf);

	memset(&a, 0, sizeof(a));
	printf("%d\n", a);

	memset(buf, 0, sizeof(buf));
	printf("%s\n", buf);

	memset(buf, 'a', sizeof(buf)-1);
	printf("%s\n", buf);

	memset(buf, '0', sizeof(buf) - 9);
	printf("%s\n", buf);
}

//�ڴ濽�� memcpy
void Memorycpy() {

	int i = 0;
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int b[10] = { 0 };

	char str1[128] = "";
	char str2[128] = "abc\0def\0dadfa";


	printf("memcpy��");
	memcpy(b, a, sizeof(int) * 5);
	for (i=0; i<sizeof(b)/sizeof(b[0]); i++)
		printf("%d ",b[i]);
	printf("\n");


	printf("memcpy�� ");
	memcpy(str1, str2, sizeof(char) * 10);
	for (i = 0; i < 10; i++)
		printf("%d ", str1[i]);
	printf("\n");

	 
	//��memcpy��ȣ�strncpy��0�۶�
	printf("strncpy��");
	strncpy(str1, str2, sizeof(char) * 10);
	for (i = 0; i < 10; i++)
		printf("%d ", str1[i]);
	printf("\n");
}


//memmov


//�ڴ�Ƚ� memcmp
void Memorycmp() {

	char num1[] = { 1,3,3,4,5,6,7 };
	char num2[] = { 1,2,3,4,5,6,7 };

	char str1[] = "asdf\0qwer";
	char str2[] = "asdf\0zwer";

	printf("%d\n", memcmp(num1, num2, sizeof(char) * 7));

	printf("%d\n", memcmp(str1, str2, sizeof(str1)));

	//��memcmp��ȣ�strncmp��0�۶�
	printf("%d\n", strncmp(str1, str2, sizeof(str1)));
}


//�ڴ������ͷ� malloc free
void MemoryMalloc() {

	int i; 

	//����һ�����飬������10��Ԫ�أ�int����
	int *p = (int*)malloc(sizeof(int)*10);
	memset(p, 0, 10);
	*p = 1000;
	*(p + 5) = 50;
	for (i = 0; i < 10; i++)
		printf("%d ", *(p+i));
	free(p);
	printf("\n");

	char* q = malloc(1024);
	memset(q, 0, 1024);
	strncpy(q, "helloworld");
	printf("%s\n", q);
	free(q);
}

//MemoryAddrTest
#if 1
//���ر�����ַ
int *MemoryAddr() {

	//int p = 10;			//�ֲ������ں������н������ͷſռ䣬���������static����
	static int p = 10;		//��̬��������һֱ���ڣ�ֱ���������
	p *= 10;
	return &p;
}
void MemoryAddrTest() {

	int* p = MemoryAddr();
	printf("%d\n", *p);
	*p = 1000;              //err: p��ָ�Ŀռ��Ѿ��ͷ�
	printf("%d\n", *p);
}

#endif


//MemoryHeapTest
#if 1	
//������ַ
int *MemoryHeap1(int num) {

	num += 100;
	return &num;
}

int* MemoryHeap2(int *num) {

	*num += 102;
	return num;
}

char* MemoryHeap3() {

	char* q = malloc(100);
	return q;
}

void MemoryHeapTest() {

	int num = 10;

//MemoryHeap1:
 
	//int *p = MemoryHeap1(num);      //err: �����Է����βε�ַ
	//*p = 1000;
	//printf("%d\n", *p);

//MemoryHeap2:

	//int* p = MemoryHeap2(&num);    //���ԣ�����ʵ�ʲ�������num�ĵ�ַ
	//*p = 1000;
	//printf("%d\n", *p);


//MemoryHeap3:

	char* p = MemoryHeap3();    //malloc����Ķ��������ͷţ����Դ���

	/*������仰�����⣬�ַ�����ַ���ݵĹ����л���ַ����׵�ַ���ݸ�p,
	 ��ʹ��p�ĵ�ַ����ָ��malloc����ĵ�ַ�����ִ���*/
	//*p = "hello";		//err	
	strcpy(p, "hello");	//��ȷ����
	printf("%s\n", p);	//�ַ���������Ҫ*p,ֱ�Ӵ����׵�ַ
	free(p);

}

#endif



//�ڴ���Ⱦ
char* MemoryPollution(char *q) {

	q = malloc(1024);
	return q;
}

void MemoryPollution1(char** K) {

	*K = malloc(1024);	//*K��  *p = NULL �ĵ�ַ
}

void MemoryPollutionTest() {

	char* p = NULL;

	//err:ͨ��������ֵ���ݣ����ܸı�ʵ�ε�ֵ��
	
	//MemoryPollution(p);

	//p = MemoryPollution(p);	//��ȷ������p����malloc����ĵ�ַ
	//strcpy(p, "hello");
	//printf("%s\n", p);


	//��ʵ�εĵ�ַ�������ڵ��õ�ʱ��ı�ʵ�ε�ֵ

	MemoryPollution1(&p);	//��һ�ַ�ʽ������ָ��
	strcpy(p, "hello");
	printf("%s\n", p);

}