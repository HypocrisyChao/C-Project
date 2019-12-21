#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMBER 52

typedef struct poker
{
    int name;
    struct poker *next;
} Poker;

Poker stack[10];
Poker *p,*h,*a,*b,*c,*d,*e,*f;

Poker* creat()
{
    int i;
    Poker *head = NULL;
    p = (Poker *)malloc(sizeof(Poker));
    head = p;
    h = p;
    for (i=1; i<=NUMBER; i++)
    {
        p = (Poker *)malloc(sizeof(Poker));
        h->next = p;
        h = p;
        p->name = i;
    }
    p->next = NULL;
    return head;
}

void Wash (Poker *head)
{
    int i,tar1,tar2,k,ranmid;
    for (i=0; i<1000; i++)
    {
        ranmid=rand()%47+4;
        tar1 = rand()%(ranmid-3);
        tar2 = (rand()%(50-ranmid+2))+ranmid;
        p = head;
        for (k=0; k<tar1; k++)
        {
            p = p->next;
        }
        a = p;
        b = a->next;
        c = b->next;
        p = head;
        for (k=0; k<tar2; k++)
        {
            p = p->next;
        }
        d = p;
        e = d->next;
        f = e->next;
        b->next = f;
        e->next = c;
        a->next = e;
        d->next = b;


    }
}

void Print(Poker *head)
{
    p = head->next;
    while (p!=NULL)
    {
        printf("%d\n",p->name);
        p = p->next;
    }
}

void Free(Poker *head)
{
    p = head;
    while (p!=NULL)
    {
        h = p;
        p = p->next;
        free(h);
    }
}

int Play (Poker *head)
{
    int i,n,k;
    printf("请输入分多少叠牌（<10）:\n");
    scanf("%d",&n);
    for (i=0; i<n; i++)
    {
        stack[i].name = 53+i;
    }
    for (i=0; i<n; i++)
    {
        p = head->next;
        for (k=0; k<i; k++)
        {
            p = p->next;
        }
        stack[i].next = p;
        while (p!=NULL)
        {
            h = p;
            for (k=0; k<n; k++)
            {
                if (p!=NULL)
                    p = p->next;
            }
            h->next = p;
        }
    }
}


void Show(int n)
{
    int i,k;
    for (i=0; i<n; i++)
    {
        p = &stack[i];
        while (p!=NULL)
        {
            printf("%d  ",p->name);
            p = p->next;
        }
    }
}

int main()
{
    int i,n;
    Poker *head;
    srand(time(NULL));
    head = creat();
    Print(head);
    printf("\n\n");
    //Wash(head);
    Print(head);
    n=Play(head);
    Show(n);
    Free(head);
    return 0;
}
