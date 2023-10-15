#define   _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

#define PATHFILE "test.txt"

/*

fopen:打开一个文件
fclose:关闭一个文件，程序最多打开文件数1024
fputc:写入
perror:打印错误信息
fgetc:读纯文本
feof:判断文件指针是否处在文件尾

*/


FILE* FileOpen(const char* Command) {

	FILE* fp = fopen(PATHFILE, Command);

	if (fp == NULL) {

		perror("File");
		return 0;
	}

	return fp;
}


//写
void FileFopenWrite() {

	char buf[] = "Hello World!";
	//FILE* fp = fopen("./test.txt", "r");
	FILE* fp = fopen("./test.txt", "a");
	if (fp == NULL) {
		perror("file");	//打印错误信息
		return;
	}
	for(int i = 0; i<sizeof(buf)/sizeof(buf[1])-1; i++)
		fputc(buf[i], fp);

	fclose(fp);
}


//读，内容为纯文本
void FileFopenRead() {

	char buf[128] = "";
	int i = 0;

	FILE* fp = fopen("./test.txt", "r");

	if (fp == NULL) {
		perror("file");	//打印错误信息
		return;
	}

	while ((buf[i++] = fgetc(fp)) != EOF);

	printf("%s\n", buf);

}


//读，内容任意
void FileFopenRead1() {

	char buf[128] = "";
	int i = 0;

	FILE* fp = fopen("./test.txt", "r");

	if (fp == NULL) {
		perror("file");	//打印错误信息
		return;
	}

	do {

		buf[i++] = fgetc(fp);

	} while (!feof(fp));

	printf("%s\n", buf);

}



//fprintf、fscanf:字符格式化函数
void PrintfTest()
{
	int a = 0;
	char stu[20] = "";

	FILE* fp = FileOpen("a");

	sprintf(stu, "%s\n", "Hello");
	printf("%s\n", stu);
	fprintf(fp, "%s\n", "Hello");	//写入文件
}


//fscanf、sscanf
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



//fwrite:写文件

typedef struct _FwriteFile {

	int id;
	char stu[20];
}STUW;

void FwriteFile() {

	int cont = 0;
	STUW num[3] = { {1,"lucy"},{2,"bob"},{3,"lili"} };

	FILE* fp = FileOpen("a");

	//第二个参数写一，返回值刚好是写入文件的字节数
	cont = fwrite(num, 1, sizeof(num), fp);
	printf("%d\n", cont);

	fclose(fp);
}



//fread:读文件

void FreadFile() {

	STUW num[3] = {0};
	FILE* fp = FileOpen("r");

	fread(num, 1, sizeof(num), fp);

	for (int i = 0; i < 3; i++)
		printf("%d %s\n", num[i].id, num[i].stu);

	fclose(fp);
}

/*
fseek:移动光标
rewind:光标移动至文件开头
ftell:返回光标相对开头的位置
stat:获取文件状态
remove:删除文件
rename:重命名
fflush:强制刷新缓冲区
*/

/*
	fseek(fp, 5, SEEK_SET);	//光标相对于开头向后移动5个字节

	fseek(fp, 0, SEEK_SET);	//移植开头

	fseek(fp, 4, SEEK_CUR);	//光标相对当前向后移动4个字节

	fseek(fp, -4, SEEK_CUR);	//光标相对当前向前移动4个字节

	fseek(fp, -4, SEEK_END);	//光标相对文件末尾向前移动4个字节
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

//rename、remove
	printf("%d\n", rename(PATHFILE, "new.txt"));
	printf("%d\n", remove("new.txt"));
	//rename(PATHFILE, "new.txt");
	//remove(PATHFILE);

	fp = FileOpen("w");
	fclose(fp);
}