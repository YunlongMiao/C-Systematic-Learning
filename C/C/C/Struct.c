#define   _CRT_SECURE_NO_WARNINGS


#include<stdio.h>



struct student {
    int num;
    char name[20];
    char sex[10];
    int age;
};

void Struct() {

    struct student s = { .num = 2021, .name = "ʮ���", .sex = "man", .age = 152 };
    struct student str[3];

    printf("%d\n", sizeof(s));

    scanf("%d%s%s%d", &s.num, &s.name, &s.sex, &s.age);
    printf("%d %s %s %d\n", s.num, s.name, s.sex, s.age);

    scanf("%d%s%s%d", &str[0].num, &str[0].name, &str[0].sex, &str[0].age);
    printf("%d %s %s %d\n", str[0].num, str[0].name, str[0].sex, str[0].age);

}


struct stu
{
    int id;
    int age;
    char name[128];
} a;


void StructBasic() {

    //struct stu s1 = { 1,20,"����" };
    //struct stu s2 = { .age = 20 };

    //ͨ����ַ������Ա��ʹ��->
    (&a)->id = 4;
    /*(&a)->name = "wangwu";*/     //����
    strcpy((&a)->name, "wangwu");
    printf("%d %s\n",(&a)->id, (&a)->name);

    strcpy(a.name, "��˹");
    printf("%s\n", a.name);
}




//�ṹ������
void StructArray()
{
    struct stu num[5] = { {1,11,"zangsan"}, {2,12,"lisi"}, 
                          {3,13,"wangwu"}, {4,14,"liliu"}, 
                          {5,15,"qinqi"} };
     
    for (int i = 0; i < sizeof(num) / sizeof(num[0]); i++)
        printf("%d %d %s\n", num[i].id, num[i].age, num[i].name);
    
}



//�ṹ���׽ṹ��
struct stuHub{
    
    struct stu s;
    char subject[128];
};

void StructMultiple() {

    struct stuHub Multiple;
    Multiple.s.id = 1;
    strcpy(Multiple.s.name, "����");
    strcpy(Multiple.subject, "���Ծ�����");

    printf("%d %s %s\n", Multiple.s.id, Multiple.s.name, Multiple.subject);
}



//�ṹ�帳ֵ

void Memcpy_Struct(struct stu *x,struct stu *y) {

    memcpy(x, y, sizeof(x));
}

void StructAssignment() {

    struct stu a = { 1,11,"zangsan" };
    struct stu b;
    Memcpy_Struct(&b, &a);
    //b = a;
    printf("%d %d %s\n", b.id, b.age, b.name);

}


//�ṹ��ָ��
void StructPoint() {

    struct stu s;
    //struct stu* p;  //�����������壬ΪҰָ��
    struct stu* p = &s;

    //struct stu* p = (struct stu*)malloc(sizeof(struct stu)); //����
    printf("%d\n", sizeof(struct stu));
    p->id = 2;
    p->age = 50;
    strcpy(p->name, "zhangsan");
    printf("%d %d %s\n", p->id, p->age, p->name);
}


//�ṹ����ָ��
struct t {
    int a;
};

struct tea {
    int id;
    char* p;
    struct t* a0;
};

void StructMultiplePoint() {

    struct t aa;
    struct tea tem;
    struct tea* temp = &tem;
    temp->a0 = &aa;
    //struct tea* temp = (struct tea*)malloc(sizeof(struct tea));
    //temp->p = (char*)malloc(128);

    temp->id = 100;
    temp->p = "hello";
    //temp->a0 = (struct t*)malloc(sizeof(struct t));
    temp->a0->a = 100;      //a0��Ұָ�룬����ֱ�Ӹ�ֵ
    //strcpy(temp->id, "hello");  //����Ұָ��

    printf("%d\n", (temp->id));
    printf("%s\n", (temp->p));
    printf("%d\n", temp->a0->a);


}




//�ṹ����Ϊ�����β�
struct stu161 {

    int id163;
    char name164[128];
};

void set_num(struct stu161 *p,int n) {

    for (int i = 0; i < n; i++) {

        //(*(p + i)).id163 = i + 10;
        p[i].id163 = i + 10;
        //(p + i)->id163 = i + 10;
    }
}

void StructArrayParameter() {

    struct stu161 stu170[10];

    //memset(stu170, 0, sizeof(stu170));
    set_num(stu170, sizeof(stu170) / sizeof(stu170[0]));
    for (int i = 0; i < sizeof(stu170) / sizeof(stu170[0]); i++)
        printf("%d\n", stu170[i].id163);
}