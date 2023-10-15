#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

#define PATHFILE "test.txt"

/*

fopen:��һ���ļ�
fclose:�ر�һ���ļ������������ļ���1024
fputc:д��
perror:��ӡ������Ϣ
fgetc:�����ı�
feof:�ж��ļ�ָ���Ƿ����ļ�β

*/


FILE* FileOpen(const char* Command) {

	FILE* fp = fopen(PATHFILE, Command);

	if (fp == NULL) {

		perror("File");
		return 0;
	}

	return fp;
}


//д
void FileFopenWrite() {

	char buf[] = "Hello World!";
	//FILE* fp = fopen("./test.txt", "r");
	FILE* fp = fopen("./test.txt", "a");
	if (fp == NULL) {
		perror("file");	//��ӡ������Ϣ
		return;
	}
	for(int i = 0; i<sizeof(buf)/sizeof(buf[1])-1; i++)
		fputc(buf[i], fp);

	fclose(fp);
}


//��������Ϊ���ı�
void FileFopenRead() {

	char buf[128] = "";
	int i = 0;

	FILE* fp = fopen("./test.txt", "r");

	if (fp == NULL) {
		perror("file");	//��ӡ������Ϣ
		return;
	}

	while ((buf[i++] = fgetc(fp)) != EOF);

	printf("%s\n", buf);

}


//������������
void FileFopenRead1() {

	char buf[128] = "";
	int i = 0;

	FILE* fp = fopen("./test.txt", "r");

	if (fp == NULL) {
		perror("file");	//��ӡ������Ϣ
		return;
	}

	do {

		buf[i++] = fgetc(fp);

	} while (!feof(fp));

	printf("%s\n", buf);

}



//fprintf��fscanf:�ַ���ʽ������
void PrintfTest()
{
	int a = 0;
	char stu[20] = "";

	FILE* fp = FileOpen("a");

	sprintf(stu, "%s\n", "Hello");
	printf("%s\n", stu);
	fprintf(fp, "%s\n", "Hello");	//д���ļ�
}


//fscanf��sscanf
void ScanfTest() {

	char stu[128] = "";
	char stu1[128] = "";
	char stu2[128] = "";
	char stu3[128] = "";

	FILE* fp = FileOpen("r");

	fscanf(fp, "%s\n%s", stu1, stu2);
	printf("%s\n", stu1);
	printf("%s\n", stu2);

	sscanf(stu1, "%s",stu);
	printf("%s\n", stu);
}



//fwrite:д�ļ�

typedef struct _FwriteFile {

	int id;
	char stu[20];
}STUW;

void FwriteFile() {

	int cont = 0;
	STUW num[3] = { {1,"lucy"},{2,"bob"},{3,"lili"} };

	FILE* fp = FileOpen("a");

	//�ڶ�������дһ������ֵ�պ���д���ļ����ֽ���
	cont = fwrite(num, 1, sizeof(num), fp);
	printf("%d\n", cont);

	fclose(fp);
}



//fread:���ļ�

void FreadFile() {

	STUW num[3] = {0};
	FILE* fp = FileOpen("r");

	fread(num, 1, sizeof(num), fp);

	for (int i = 0; i < 3; i++)
		printf("%d %s\n", num[i].id, num[i].stu);

	fclose(fp);
}

/*
fseek:�ƶ����
rewind:����ƶ����ļ���ͷ
ftell:���ع����Կ�ͷ��λ��
stat:��ȡ�ļ�״̬
remove:ɾ���ļ�
rename:������
fflush:ǿ��ˢ�»�����
*/

/*
	fseek(fp, 5, SEEK_SET);	//�������ڿ�ͷ����ƶ�5���ֽ�

	fseek(fp, 0, SEEK_SET);	//��ֲ��ͷ

	fseek(fp, 4, SEEK_CUR);	//�����Ե�ǰ����ƶ�4���ֽ�

	fseek(fp, -4, SEEK_CUR);	//�����Ե�ǰ��ǰ�ƶ�4���ֽ�

	fseek(fp, -4, SEEK_END);	//�������ļ�ĩβ��ǰ�ƶ�4���ֽ�
*/
void FseekFile() {

	int cont = 0;

//stat
	int sta = 0;
	struct stat buf;
	sta = stat("test.txt", &buf);
	if (sta < 0)
	{
		printf("open file error!");
		//exit(0);
	}
	printf("file_size = %d\n", buf.st_size);

	FILE* fp = FileOpen("w");

//fseek&rewind
	fputs("Helloworld!\nEverything", fp);
	//fseek(fp, 0, SEEK_SET);
	rewind(fp);
	fputs("seekset", fp);

	fseek(fp, 5, SEEK_CUR);
	fputs("seekcur", fp);

	fseek(fp, 0, SEEK_END);
	fputs("\nseekend", fp);

//fflush
	//fflush(fp);
	
	//char buf222[1024];
	//for (int i = 0; i < 1024; i++)
	//{
	//	memset(buf222, '1', sizeof(buf222));
	//	fwrite(buf222, 1, sizeof(buf222), fp);
	//	printf("i=%d\n", i);
	//}
	//while (1);


//ftell
	cont = ftell(fp);
	printf("%d\n", cont);


	fclose(fp);

//rename��remove
	printf("%d\n", rename(PATHFILE, "new.txt"));
	printf("%d\n", remove("new.txt"));
	//rename(PATHFILE, "new.txt");
	//remove(PATHFILE);

	fp = FileOpen("w");
	fclose(fp);
}