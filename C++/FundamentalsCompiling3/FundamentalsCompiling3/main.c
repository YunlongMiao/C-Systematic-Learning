#define   _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "string.h"

#define ACC -2
#define a 7
#define hashsign 10
#define S 11
#define tempsy 15
#define plus 34
#define times 36
#define becomes 38
#define lparent 48
#define rparent 49
#define ident 56
#define intconst 57


char ch = '\0';
int count = 0;
static char spelling[10] = { "" };//���ʶ�����
static char line[81] = { "" };
static char* pline;//�ַ�������ָ��
static char vartab[100][10]; //��������

struct sym
{
    int sy1;//���� 
    int pos;//��ַ
}buf[1000],//�ʷ��������������
n,//��ȡ��Ԫʽ�ĵ�ǰ�ַ�
n1,//��ǰ���ʽ�е��ַ�
E,//���ս��
sstack[100],//���ʽ���崦��ķ���ջ
ibuf[100],//���ʽʹ�õĻ�����
stack[1000];//�﷨�����ķ���ջ


struct sym oth;//��Ԫʽ�հ�λ��

struct fourexp {
    char op[10];
    struct sym arg1;
    struct sym arg2;
    int result;
}fexp[200];//��Ԫʽ


int ssp = 0;//ָ�� sstack ջ��ָ��
struct sym* pbuf = buf;//�ʷ�����������ָ��
int nlength = 0;//���ʵĳ���
int lnum = 0;//Դ��������
int tt1 = 0;//��������ָ��
FILE* cfile;//Դ����~Ϊ������         
int newt = 0;//��ʱ����������
int nxq = 100;
int lr;//ɨ������ LR ����������б���ĵ�ǰ״ֵ̬
int lr1;//ɨ����ʽ�� LR ����������б���ĵ�ǰ״ֵ̬
int sp = 0;//���� LR ������ʱ��״̬ջ��ջ��ָ��
int stack1[100];//״̬ջ1
int sp1 = 0;//״̬ջ 1 ��ջ��ָ��
int num = 0;//���ʽ������ָ��

/*****************�������ʽ��LR������****************************/
static int action1[10][7] =
{
    {3,-1, -1,2,-1,-1, 1},      //0
    {-1,4,5,-1,-1,ACC,-1},      //1
    {3,-1,-1,2,-1,-1,6},        //2
    {-1,104,104,-1,104,104,-1}, //3
    {3,-1,-1,2,-1,-1, 7},       //4
    {3,-1,-1,2,-1,-1,8},        //5
    {-1,4,5,-1,9,-1,-1},        //6
    {-1, 101, 5,-1, 101, 101,-1},       //7
    {-1, 102, 102,-1, 102, 102, -1},    //8
    {-1, 103,103,-1, 103,103,-11}
}; //9
readline(FILE* cfile)
{
    char ch1;
    pline = line;
    ch1 = getc(cfile);
    while (ch1 != '\n') {
        *pline = ch1;
        pline++;
        ch1 = getc(cfile);
    }

    *pline = '\0';
    pline = line;

}


readch(FILE* cfile)
{
    if (ch == '\0')
    {
        readline(cfile);
        lnum++;
    }
    ch = *pline;
    pline++;
}




find(char spel[])
{
    int ss1 = 0;
    int ii = 0;
    while ((ss1 == 0) && (ii < nlength))
    {
        if (!strcmp(spel, vartab[ii])) ss1 = 1;
        ii++;
    }
    if (ss1 == 1) return ii - 1;
    else return -1;
}


identifier(FILE* cfile)
{
    int iii = 0, j, k;
    int ss = 0;
    k = 0;
    do
    {
        spelling[k] = ch;
        k++;
        readch(cfile);
    } while (((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')));

    pline--;
    spelling[k] = '\0';

    buf[count].sy1 = ident;
    j = find(spelling);

    if (j == -1)
    {
        buf[count].pos = tt1,
            strcpy(vartab[tt1], spelling);
        tt1++;
        nlength++;
    }

    else buf[count].pos = j;
    count++;
    for (k = 0; k < 10; k++) spelling[k] = ' ';

}



number(FILE* cfile)
{
    int ivalue = 0;
    int digit;
    do
    {
        digit = ch - '0';
        ivalue = ivalue * 10 + digit;
        readch(cfile);
    } while ((ch >= '0') && (ch <= '9'));

    buf[count].sy1 = intconst;
    buf[count].pos = ivalue;
    count++;
    pline--;
}



scan()
{
    int i;
    while (ch != '~')
    {
        switch (ch)
        {
        case ' ':
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            identifier(cfile);
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            number(cfile);
            break;
        case '(':
            buf[count].sy1 = lparent;
            count++;
            break;
        case ')':
            buf[count].sy1 = rparent;
            count++;
            break;
        case'#':
            buf[count].sy1 = hashsign;
            count++;
            break;
        case '+':
            buf[count].sy1 = plus;
            count++;
            break;
        case'*':
            buf[count].sy1 = times;
            count++;
            break;
        case ':':
            readch(cfile);
            if (ch == '=')
                buf[count].sy1 = becomes;
            count++;
            break;
        }
        readch(cfile);
    }
    buf[count].sy1 = -1;
}



readnu()
{
    if (pbuf->sy1 >= 0) {
        n.sy1 = pbuf->sy1;
        n.pos = pbuf->pos;
        pbuf++;
    }
}


newtemp()
{
    newt++;
    return newt;
}


gen(char op1[], struct sym arg11, struct sym arg22, int result1)
{
    strcpy(fexp[nxq].op, op1);
    fexp[nxq].arg1.sy1 = arg11.sy1;
    fexp[nxq].arg1.pos = arg11.pos;
    fexp[nxq].arg2.sy1 = arg22.sy1;
    fexp[nxq].arg2.pos = arg22.pos;
    fexp[nxq].result = result1;
    nxq++;
    return nxq - 1;
}



/*******************/
change1(int chan)
{
    switch (chan)
    {
    case ident:
    case intconst:
        return 0;
    case plus:
        return 1;
    case times:
        return 2;
    case lparent:
        return 3;
    case rparent:
        return 4;
    case hashsign:
        return 5;
    case tempsy:
        return 6;
    }
}

Irparse1(int num);

/****�������ʽ����*****/
Irparse1(int num)
{
    lr1 = action1[stack1[sp1]][change1(n1.sy1)];
    if (lr1 == -1)
    {
        printf("\n �������ʽ����! \n");
        getch();
        exit(0);
    }
    if ((lr1 < 10) && (lr1 >= 0))//�ƽ�
    {
        sp1++;
        stack1[sp1] = lr1;
        if (n1.sy1 != tempsy)
        {
            ssp++;
            num++;
            sstack[ssp].sy1 = n1.sy1;
            sstack[ssp].pos = n1.pos;
        }
        n1.sy1 = ibuf[num].sy1;
        n1.pos = ibuf[num].pos;
        printf("%d\t\tstack[%d]=%d\t\tsym-%d\t\tn=%d\n",
            lr1, sp1, stack1[sp1], sstack[ssp].sy1, n1.sy1);
        Irparse1(num);
    }
    if ((lr1 >= 100) && (lr1 < 105))
    {
        switch (lr1)
        {
        case 100: //s'->E
            break;
        case 101: //E->E+E
            E.pos = newtemp();
            gen("+", sstack[ssp - 2], sstack[ssp], E.pos + 100);
            ssp = ssp - 2;
            sstack[ssp].sy1 = tempsy;
            sstack[ssp].pos = E.pos;
            sp1 = sp1 - 3;
            break;
        case 102: //E->E*E
            E.pos = newtemp();
            gen("*", sstack[ssp - 2], sstack[ssp], E.pos + 100);
            ssp = ssp - 2;
            sstack[ssp].sy1 = tempsy;
            sstack[ssp].pos = E.pos;
            sp1 = sp1 - 3;
            break;
        case 103: //E->(E)
            E.pos = sstack[ssp - 1].pos;
            ssp = ssp - 2;
            sstack[ssp].sy1 = tempsy;
            sstack[ssp].pos = E.pos;
            sp1 = sp1 - 3;
            break;
        case 104://E->i
            E.pos = sstack[ssp].pos;
            sp1--;
            break;
        }
        printf("%d\t\tstack[%d]=%d\t tE. pos=%d\t tn=%d n", lr1, sp1, stack1[sp1],
            sstack[ssp].pos, n1.sy1);
        n1.sy1 = tempsy;
        n1.pos = E.pos;
        Irparse1(num);
    }
    if ((lr1 = -ACC) && n1.sy1 == hashsign) return ACC;
}


test(int value)//�������ֺ�;
{
    switch (value)
    {
    case intconst:
    case ident:
    case plus:
    case times:
    case becomes:
    case lparent:
    case rparent:
        return 1;
    default:
        return 0;
    }
}


Irparse()//����������﷨�ɷ�
{
    int i1 = 0;
    int num = 0;
    if (test(n.sy1))
    {
        do
        {
            ibuf[i1].sy1 = n.sy1;
            ibuf[i1].pos = n.pos;
            readnu();
            i1++;
        } while (test(n.sy1));
        ibuf[i1].sy1 = hashsign;
        pbuf--;
        sstack[0].sy1 = hashsign;
        ssp = 0;

        sp1 = 0;
        stack1[sp1] = 0;
        n1.sy1 = ibuf[num].sy1;
        n1.pos = ibuf[num].pos;
        printf(" ��  ʼ   \t\tstack[%d]=%d\t\tsym %d\t\tn=%d\n", sp1, stack1[sp1],
            sstack[sp1].sy1, n1.sy1);
        Irparse1(num);
    }
}


disp1()
{
    int temp1 = 0;
    printf("********�ʷ��������********** \n");
    for (temp1 = 0; temp1 <= count; temp1++)
    {
        printf("%d\t%d\n", buf[temp1].sy1, buf[temp1].pos);
        if (temp1 == 20)
        {
            printf("�����������......\n");
            getch();
        }
    }
    getch();
}


disp2()
{
    int temp1 = 100;
    printf("\n*********��Ԫʽ�������************\n");
    for (temp1 = 100; temp1 < nxq; temp1++)
    {
        printf("%d\t", temp1);
        printf("(%s\t,", fexp[temp1].op);
        if (fexp[temp1].arg1.sy1 == ident)
            printf("%s\t,", vartab[fexp[temp1].arg1.pos]);
        else
        {
            if (fexp[temp1].arg1.sy1 == tempsy)
                printf("T%d\t,", fexp[temp1].arg1.pos);
            else {
                if (fexp[temp1].arg1.sy1 = intconst)
                    printf("%d\t,", fexp[temp1].arg1.pos);
                else printf("\t,");
            }
        }
        if (fexp[temp1].arg2.sy1 = ident)
            printf("%s\t,", vartab[fexp[temp1].arg2.pos]);
        else
        {
            if (fexp[temp1].arg2.sy1 == tempsy)
                printf("T%d\t,", fexp[temp1].arg2.pos);
            else
            {
                if (fexp[temp1].arg2.sy1 == intconst)
                    printf("%d\t,", fexp[temp1].arg2.pos);
                else printf("t,");
            }
        }
        if (fexp[temp1].op[0] != 'j')
        {
            if (fexp[temp1].result >= 100)
                printf("T%d\t)", fexp[temp1].result - 100);
            else
                printf("%s\t)", vartab[fexp[temp1].result]);
        }
        else printf("%d\t)", fexp[temp1].result);
        printf("\n");
    }
    getch();
}


disp3()
{
    int ttt;
    printf("\n\n �����ܹ�%d �У�������%d ����Ԫʽ!\n", lnum, count);
    getch();
    printf("\n*********��������************ \n");
    for (ttt = 0; ttt < tt1; ttt++)
        printf("%d\t%s\n", ttt, vartab[ttt]);
    getch();
}
main()
{
    cfile = fopen("p.dat", "r");
    readch(cfile);
    scan(cfile);
    disp1(cfile);
    disp3(cfile);
    stack[sp].pos = 0;
    stack[sp].sy1 = -1;
    stack1[sp1] = 0;
    oth.sy1 = -1;
    printf("\n********״̬ջ�ӹ����̼���Լ˳��***************\n");
    readnu();
    Irparse();
    getch();
    disp2();
    printf("\n �����������!\n");
    getch();
}


