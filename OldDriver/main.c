#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")                        //�������ֵ�ͷ�ļ�


typedef struct car                                      //����״̬���ýṹ�屣�棩
{
    COORD   place;                                        //����λ��
    int     scord;                                          //����
} Car;

typedef struct player                                   //�ϲ���Ҽ�¼
{
    char    name[10];
    int     scord[5];
} PLAYER;

typedef struct playerlist                               //��Ҽ�¼����
{
    PLAYER  Player;
    struct  playerlist *next;
} PLIST;



typedef struct wall                                     //�ϰ���
{
    COORD   place;                                        //λ��
    int     REWARD;                                         //��Ʒ
    int     preward;                                        //��Ʒλ��
} WALL;

PLIST       *p,*h;                                            //�������ָ��
int         lvcounter=0,lv=0,CGAP=5;                            //�Ѷȳ�ʼ��
int         GAP;                                                //��϶
int         god=0,rtime=0;                                      //��Ʒ
char        name[10];

PLIST       *Creat();

void Gotoxy(int x ,int y)                                //��λ���
{
    COORD   coord = {x ,y};
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int OpenGame()                                          //��ʼ����
{
    int     k;
    char    *pname;
    system("color 3F");                                 //������ɫ
    printf("�����˾������ʼ쭳�ǰ������뷨��ΪӢ�ģ��Ѵ�����󻯣����ں����ο������Ǿͳ�������\n");
Choose:
    printf("���������ֲ��س���1���鿴��Ϸ˵����2����ʼ��Ϸ��3���鿴��ǰ��¼��4���˳���Ϸ:");
    while (scanf("%d" ,&k)!=0)
    {
        switch (k)
        {
        case 1:
            printf("\n���ǿ���ģ������'-----'Ϊ�ϰ��ǧ��Ҫײ����Ӵ������'a'����С�������ƶ�������'d'����С�������ƶ�����Ϸ�����ŷ���������Խ��Խ�ѡ���Ʒ\n'G'�ǿ�������һ���˺�\n'T'�ǿ��Լ����ٶ�\n'D'�������\n'C'һ�����\n");
            goto Choose;                                //����ѡ��
        case 2:
            pname = &name;
            printf("���������֣��𳬹�10���֣���");
            scanf("%s",name);
            while (getchar()!='\n');
            return 1;
            break;
        case 3:
            CheckRecord();
            goto Choose;                                //����ѡ��
        case 4:
            return 0;
            break;
        }
    }
    while (getchar()!='\n');
    goto Choose;
}

void CheckRecord()                                      //�鿴��¼
{
    int     name ,scord ,k ,i ,n;
    char    buf[10];
    PLIST   * head;
    FILE    *fp;
    head = Creat();                                     //��������
    if((fp = fopen("GameRecord.txt","r"))==NULL)
    {
        printf("��Ϸ��¼����ʧ��������Ҫ����һ����ϷŶ(>�n<��)~\n");          //��ֹ�ļ�����ʧ��
        return 0;
    }
    for (i=0; i<20; i++)
    {
        p =head;
        for (k=0; k<i+1; k++)
        {
            p = p->next;
        }
        fscanf(fp,"%d %s",p->Player.scord,p->Player.name);
    }
    Sort(head);                                             //����
    Merge(head);                                            //����ͬ��Ҳ�ͬ����������һ��
    for (i=0; i<20; i++)
    {
        p = head;
        for (k=0; k<i+1; k++)
        {
            p = p->next;
        }
        if (p->Player.scord[0]<=0)                          //������շ���
            continue;
        if (i==0)                                           //��һ����ҵ�������ɫ��ͬ
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),61);
        printf("%s",p->Player.name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
        for (n=0; n<5; n++)
        {
            if (i==0)                                       //��һ����ҵ�������ɫ��ͬ
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),61);
            if (p->Player.scord[n]!=0)
                printf(",%d",p->Player.scord[n]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
        }
        printf("\n");
    }
    p =head;
    for (k=0; k<20; k++)                                    //�ͷ��ڴ�
    {
        h = p;
        p = p->next;
        free(h);
    }
    fclose(fp);                                             //�ر��ļ�
    return 0;

}

PLIST *Creat()                                              //��������
{
    int     i,k;
    PLIST   *head = NULL;
    p = (PLIST *)malloc(sizeof(PLIST));
    head = p;
    h = p;
    for (i=1; i<=20; i++)
    {
        p = (PLIST *)malloc(sizeof(PLIST));
        h->next = p;
        for (k=0; k<5; k++)
        {
            h->Player.scord[k]=0;
        }
        h = p;
    }
    p->next = NULL;
    return head;
}


void Merge(PLIST *head)

{
    int     i, k, n,j,o;
    PLAYER  clean= {0};                                   //�������ķ���
    for (i=0; i<20; i++)
    {
        p =head;
        for (j=0; j<i+1; j++)
        {
            p = p->next;
        }
        n=0;
        h = p->next;
        for (o=0; o<20-i-1; o++)
        {
            if (strcmp(h->Player.name,p->Player.name)==0&&h->Player.scord[0]>0)
            {
                if (n<5)
                    p->Player.scord[n+1] = h->Player.scord[0];
                h->Player = clean;
                n++;
            }
            h = h->next;
            if (h==NULL)
                break;
        }
    }
    Sort(head);                                             //��������
    return 0;

}


void Sort(PLIST *head)                                             //����
{
    int     i, k,j,o;
    PLAYER  temp;
    for (i=0; i<20; i++)
    {
        p =head;
        for (j=0; j<i+1; j++)
        {
            p = p->next;
        }
        h = p->next;
        for (o=0; o<20; o++)
        {
            if (h==NULL)
                break;
            if (h->Player.scord[0]>p->Player.scord[0])
            {
                temp =h->Player;
                h->Player = p->Player;
                p->Player = temp;
            }
            h = h->next;

        }
    }
    return 0;
}

int CheckCrash(WALL * wall,Car * car)                   //���ײ��
{
    if (car->place.Y==wall[2].place.Y)                  //ײ���ϰ����ж�
    {
        if (rtime>0)
            rtime=rtime-2;                      //�����ļ���
        if (car->place.X<wall[2].place.X||car->place.X+1>=wall[2].place.X+GAP)
            if (god>0)
            {
                god--;                                  //����������
            }
            else
            {
                return 0;
            }
        //��ͬ������ͬЧ��
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==0)
            car->scord++;
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==1)
            car->scord=car->scord+2;
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==2)
            rtime=rtime+10;
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==3)
            god++;
        lvcounter++;
        lv = lvcounter/8;                               //�ȼ�ϵͳ

    }
    if (car->place.X<70||car->place.X>110)               //�߽��ж�
    {
        return 0;
    }

    return 1;
}

void Star(WALL * wall,Car * car)                                             //��Ϸ��ʼ��
{
    int     i;
    system("cls");                                      //����
    for (i=0; i<30; i++)                                //���ɱ߽�
    {
        Gotoxy(110,i);
        printf("|");
        Gotoxy(70,i);
        printf("|");
    }
    car->place.X=90;                                   //������Ϸ
    car->place.Y=25;
    car->scord = 0;
    wall[0].place.X =89;
    wall[1].place.X = 89;
    wall[2].place.X = 89;
    wall[0].place.Y =0;
    wall[1].place.Y = 10;
    wall[2].place.Y = 20;
    lv = 0;
    rtime = 0;
    system("color 37");                                 //������ɫ
}

void ShowScord(Car * car)
{
    HideCursor();
    if (lv==0)                                          //��ʾ����
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
    if (lv==1)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
    if (lv==2)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),58);
    if (lv==3)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),59);
    if (lv==4)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),62);
    if (lv==5)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),61);
    if (lv==6)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),60);
    Gotoxy(70,30);
    printf("%d",car->scord);
    Gotoxy(110,30);                                     //��ʾ�Ի�õĽ���
    printf("god:%d,slow:%4d",god,rtime);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
}

void ShowWall(WALL wall[])                             //��ʾ�ϰ���
{
    int     i,k,a;
    HideCursor();
    srand(time(NULL));                                  //�����϶
    WALL newwall = {rand()%10+85,wall[2].place.Y-30};
    if (wall[2].place.Y>=30)                            //�ϰ����ʧ��
    {

        wall[2]=wall[1];
        wall[1]=wall[0];
        wall[0]=newwall;
        a = rand()%30;                                  //��һ�������������
        if (a<=17)
            wall[0].REWARD=0;
        if (a>17&&a<=25)
            wall[0].REWARD=1;
        if (a>25&&a<29)
            wall[0].REWARD=2;
        if (a==29)
            wall[0].REWARD=3;
        wall[0].preward = rand()%GAP;
    }
    for (i=0; i<3; i++)                                 //�ϰ��ﶯ��
    {
        for (k=71; k<wall[i].place.X; k++)
        {
            Gotoxy(k,wall[i].place.Y);
            printf("-");
        }
        for (k=109; k>wall[i].place.X+GAP; k--)
        {
            Gotoxy(k,wall[i].place.Y);
            printf("-");

        }
        for (k=71; k<wall[i].place.X; k++)
        {
            Gotoxy(k,wall[i].place.Y-1);
            printf(" ");
        }

        for (k=109; k>wall[i].place.X+GAP; k--)
        {
            Gotoxy(k,wall[i].place.Y-1);
            printf(" ");
        }
        ShowReward(wall,i);
        for (k=71; k<110; k++)
        {
            Gotoxy(k,29);
            printf(" ");
        }

    }
}

void ShowReward(WALL * wall,int i)                      //��������
{
    if(wall[i].REWARD==0)
    {
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y);
        printf("C");
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y-1);
        printf(" ");
    }
    if(wall[i].REWARD==1)
    {
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y);
        printf("D");
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y-1);
        printf(" ");
    }
    if(wall[i].REWARD==2)
    {
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y);
        printf("T");
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y-1);
        printf(" ");
    }
    if(wall[i].REWARD==3)
    {
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y);
        printf("G");
        Gotoxy(wall[i].place.X+wall[i].preward,wall[i].place.Y-1);
        printf(" ");
    }
}




void ShowCar(Car * car)                                 //��ʾС��/������ɫ
{
    HideCursor();
    Gotoxy(car->place.X,car->place.Y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),48);
    printf("@^@");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);


}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}


void MarkRecord(int scord)                              //�����¼
{
    FILE    *fp;
    fflush(stdin);
    if((fp = fopen("GameRecord.txt","at+"))==NULL)      //���ļ�
    {
        printf("��Ϸ��¼����ʧ����(>�n<��)~");
        return 0;
    }
    fprintf(fp,"%d %s\n",scord,name);                 //������ݵ��ļ���
    fclose(fp);                                        //�ر��ļ�
    system("pause");
    return 0;
}

int main()                                              //������
{
    Car     car;
    WALL    wall[3];
    char    ch;
    int     i;
    while (OpenGame())                                  //��ʼ����
    {
        Star(wall,&car);
        mciSendString("open music.mp3", NULL, 0, NULL);
        mciSendString("play music.mp3 repeat", NULL, 0, NULL);        //ѭ����������
        while (CheckCrash(wall,&car)||god)                   //�ж�ײ��
        {
            HideCursor();
            ShowScord(&car);
            if (lv<7)
                GAP = CGAP-lv/2;
            ShowWall(wall);
            ShowCar(&car);
            Sleep(150-lv*8+rtime);                           //�ٶ����ѶȺͽ�������
            if (GetAsyncKeyState('A'))                                //�������
            {
                Gotoxy(car.place.X+2,25);
                printf(" ");
                car.place.X--;
            }
            else if (GetAsyncKeyState('D'))
            {
                Gotoxy(car.place.X,25);
                printf(" ");
                car.place.X++;
            }
            for (i=0; i<3; i++)
            {
                wall[i].place.Y++;
            }
        }
        mciSendString("stop music.mp3", NULL, 0, NULL);		//ֹͣ��������
        mciSendString("close music.mp3", NULL, 0, NULL);    //�ر�����
        printf("�����");
        Sleep(500);
        system("cls");                                      //����
        MarkRecord(car.scord);                              //�����¼
    }

    return 0;
}
