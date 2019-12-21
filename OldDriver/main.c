#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")                        //播放音乐的头文件


typedef struct car                                      //车的状态（用结构体保存）
{
    COORD   place;                                        //车的位置
    int     scord;                                          //分数
} Car;

typedef struct player                                   //合并玩家记录
{
    char    name[10];
    int     scord[5];
} PLAYER;

typedef struct playerlist                               //玩家记录链表
{
    PLAYER  Player;
    struct  playerlist *next;
} PLIST;



typedef struct wall                                     //障碍物
{
    COORD   place;                                        //位置
    int     REWARD;                                         //奖品
    int     preward;                                        //奖品位置
} WALL;

PLIST       *p,*h;                                            //玩家链表指针
int         lvcounter=0,lv=0,CGAP=5;                            //难度初始化
int         GAP;                                                //空隙
int         god=0,rtime=0;                                      //奖品
char        name[10];

PLIST       *Creat();

void Gotoxy(int x ,int y)                                //定位光标
{
    COORD   coord = {x ,y};
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int OpenGame()                                          //开始界面
{
    int     k;
    char    *pname;
    system("color 3F");                                 //界面颜色
    printf("你好老司机！开始飙车前请把输入法换为英文，把窗口最大化，调节好座椅靠背我们就出发啦！\n");
Choose:
    printf("请输入数字并回车（1）查看游戏说明（2）开始游戏（3）查看以前记录（4）退出游戏:");
    while (scanf("%d" ,&k)!=0)
    {
        switch (k)
        {
        case 1:
            printf("\n这是开车模拟器，'-----'为障碍物，千万不要撞到它哟，按下'a'控制小车向左移动，按下'd'控制小车向右移动，游戏会随着分数的增加越来越难。奖品\n'G'是可以免疫一次伤害\n'T'是可以减缓速度\n'D'两点积分\n'C'一点积分\n");
            goto Choose;                                //重新选择
        case 2:
            pname = &name;
            printf("请输入名字（别超过10个字）；");
            scanf("%s",name);
            while (getchar()!='\n');
            return 1;
            break;
        case 3:
            CheckRecord();
            goto Choose;                                //重新选择
        case 4:
            return 0;
            break;
        }
    }
    while (getchar()!='\n');
    goto Choose;
}

void CheckRecord()                                      //查看记录
{
    int     name ,scord ,k ,i ,n;
    char    buf[10];
    PLIST   * head;
    FILE    *fp;
    head = Creat();                                     //创建链表
    if((fp = fopen("GameRecord.txt","r"))==NULL)
    {
        printf("游戏记录加载失败啦，需要先玩一把游戏哦(>﹏<。)~\n");          //防止文件加载失败
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
    Sort(head);                                             //排序
    Merge(head);                                            //把相同玩家不同分数整合在一起
    for (i=0; i<20; i++)
    {
        p = head;
        for (k=0; k<i+1; k++)
        {
            p = p->next;
        }
        if (p->Player.scord[0]<=0)                          //不输出空分数
            continue;
        if (i==0)                                           //第一名玩家的名字颜色不同
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),61);
        printf("%s",p->Player.name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
        for (n=0; n<5; n++)
        {
            if (i==0)                                       //第一名玩家的名字颜色不同
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),61);
            if (p->Player.scord[n]!=0)
                printf(",%d",p->Player.scord[n]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
        }
        printf("\n");
    }
    p =head;
    for (k=0; k<20; k++)                                    //释放内存
    {
        h = p;
        p = p->next;
        free(h);
    }
    fclose(fp);                                             //关闭文件
    return 0;

}

PLIST *Creat()                                              //创建链表
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
    PLAYER  clean= {0};                                   //清理多余的分数
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
    Sort(head);                                             //重新排序
    return 0;

}


void Sort(PLIST *head)                                             //排序
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

int CheckCrash(WALL * wall,Car * car)                   //检查撞击
{
    if (car->place.Y==wall[2].place.Y)                  //撞击障碍物判定
    {
        if (rtime>0)
            rtime=rtime-2;                      //奖励的减缓
        if (car->place.X<wall[2].place.X||car->place.X+1>=wall[2].place.X+GAP)
            if (god>0)
            {
                god--;                                  //奖励的免疫
            }
            else
            {
                return 0;
            }
        //不同奖励不同效果
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==0)
            car->scord++;
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==1)
            car->scord=car->scord+2;
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==2)
            rtime=rtime+10;
        if (car->place.X<=wall[2].place.X+wall[2].preward && car->place.X+2>=wall[2].place.X+wall[2].preward&&wall[2].REWARD==3)
            god++;
        lvcounter++;
        lv = lvcounter/8;                               //等级系统

    }
    if (car->place.X<70||car->place.X>110)               //边界判定
    {
        return 0;
    }

    return 1;
}

void Star(WALL * wall,Car * car)                                             //游戏初始化
{
    int     i;
    system("cls");                                      //清屏
    for (i=0; i<30; i++)                                //生成边界
    {
        Gotoxy(110,i);
        printf("|");
        Gotoxy(70,i);
        printf("|");
    }
    car->place.X=90;                                   //重设游戏
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
    system("color 37");                                 //更换颜色
}

void ShowScord(Car * car)
{
    HideCursor();
    if (lv==0)                                          //显示分数
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
    Gotoxy(110,30);                                     //显示以获得的奖励
    printf("god:%d,slow:%4d",god,rtime);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),63);
}

void ShowWall(WALL wall[])                             //显示障碍物
{
    int     i,k,a;
    HideCursor();
    srand(time(NULL));                                  //随机空隙
    WALL newwall = {rand()%10+85,wall[2].place.Y-30};
    if (wall[2].place.Y>=30)                            //障碍物“消失”
    {

        wall[2]=wall[1];
        wall[1]=wall[0];
        wall[0]=newwall;
        a = rand()%30;                                  //按一定概率随机奖励
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
    for (i=0; i<3; i++)                                 //障碍物动画
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

void ShowReward(WALL * wall,int i)                      //奖励动画
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




void ShowCar(Car * car)                                 //显示小车/更改颜色
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


void MarkRecord(int scord)                              //保存记录
{
    FILE    *fp;
    fflush(stdin);
    if((fp = fopen("GameRecord.txt","at+"))==NULL)      //打开文件
    {
        printf("游戏记录加载失败啦(>﹏<。)~");
        return 0;
    }
    fprintf(fp,"%d %s\n",scord,name);                 //输出数据到文件中
    fclose(fp);                                        //关闭文件
    system("pause");
    return 0;
}

int main()                                              //主函数
{
    Car     car;
    WALL    wall[3];
    char    ch;
    int     i;
    while (OpenGame())                                  //初始界面
    {
        Star(wall,&car);
        mciSendString("open music.mp3", NULL, 0, NULL);
        mciSendString("play music.mp3 repeat", NULL, 0, NULL);        //循环播放音乐
        while (CheckCrash(wall,&car)||god)                   //判断撞击
        {
            HideCursor();
            ShowScord(&car);
            if (lv<7)
                GAP = CGAP-lv/2;
            ShowWall(wall);
            ShowCar(&car);
            Sleep(150-lv*8+rtime);                           //速度由难度和奖励决定
            if (GetAsyncKeyState('A'))                                //检测输入
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
        mciSendString("stop music.mp3", NULL, 0, NULL);		//停止播放音乐
        mciSendString("close music.mp3", NULL, 0, NULL);    //关闭音乐
        printf("你挂了");
        Sleep(500);
        system("cls");                                      //清屏
        MarkRecord(car.scord);                              //保存记录
    }

    return 0;
}
