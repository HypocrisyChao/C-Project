#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define w1 0.1
#define length 40
#define rp 14
//0,1,2为左中右,3不动.
//
//        int y[4]= {2,2,2,1},r[8]= {1,2,1,2,2,1,1,0},g[12]= {0,1,0,2,1,0,2,1,2,2,2,2},

struct individual
{
    int gene[length];
    float fitness;
    int empty;
} ind[1750],temp;

int y1[4]= {2,2,2,1},r1[8]= {1,2,1,2,2,1,1,0},g1[12]= {0,1,0,2,1,0,2,1,2,2,2,2};
int y[4],r[8],g[12],a1,b1,c1;

void fprint(int type)
{
    int i,j,k;
    switch(type)
    {
    case 0:
        printf("No answer.The best ones are listed as follows:\n");
        break;
    case 2:
        printf("Success!!The procceess is listed as follows:\n");
        break;
    case 1:
        printf("Very close!~ The first half:\n");
        break;
    }
    k=1;
    for (i=0; i<k; i++)
    {
        for (j=0; j<length; j++)
        {
            if (ind[i].gene[j]==3)
                printf("  ");
            else
                printf("%2d",ind[i].gene[j]+1);
            if(j%5==4)
                printf(" ");
        }
        printf("   fitness:%f\n",ind[i].fitness+ind[i].empty*w1);
    }
}

void sort(int beginer,int ender)
{
    int j,k;
    for(j=beginer; j<ender; j++)
    {
        for(k=beginer; k<ender-j-1; k++)
        {
            if(ind[k].fitness < ind[k+1].fitness)
            {
                temp=ind[k];
                ind[k]=ind[k+1];
                ind[k+1]=temp;
            }
        }
    }
}


void change()
{
    int i,j,k,m,ch1,ch2;

    for (j=0; j<10; j++)
    {
        m=3*j+rand()%3;
        for (i=0; i<30; i++)
        {
            ind[i+100+30*j]=ind[i];
            ind[i+100+30*j].gene[m]=rand()%4;
        }
    }
    for (j=0; j<5; j++)
    {
        m=4*j+rand()%4;
        for (i=30; i<100; i++)
        {
            ind[i+400+70*j]=ind[i];
            ind[i+400+70*j].gene[m]=rand()%4;
        }
    }
    for (i=0; i<1000; i++)
    {
        ch1=rand()%100;
        ch2=rand()%length;
        ind[750+i]=ind[ch1];
        ind[750+i].gene[ch2]=rand()%4;
        for (j=0; j<rp; j++)
        {
            ch2=rand()%length;
            ind[750+i].gene[ch2]=rand()%4;
        }
    }
}

void fit(int beginer,int ender)
{
    int i,j,k,l,t;
    for(k=0; k<100; k++)
    {
        ind[k].fitness=0;
    }
    for (i=beginer; i<ender; i++)
    {
        int y[4],r[8],g[12],a=0,b=0,c=0;
    for (t=0;t<4; t++)
        y[t]=y1[t];
    for (t=0;t<8; t++)
        r[t]=r1[t];
    for (t=0;t<12; t++)
        g[t]=g1[t];
        for (j=0; j<length; j++)
        {
            switch(ind[i].gene[j])
            {
choose:
            case 0:
                if (j<length-1&&ind[i].gene[j+1]==2)
                {
                    ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose;
                }
                a=(a+1)%4;
                b=(b+1)%8;
                c=(c+1)%12;
                break;
            case 1:
                if (j<length-2&&ind[i].gene[j+1]==1&&ind[i].gene[j+2]==1)
                {
                    ind[i].gene[j+2]=ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose;
                }
                t=g[c];
                g[c]=r[b];
                r[b]=y[a];
                y[a]=t;
                break;
            case 2:
                if (j<length-1&&ind[i].gene[j+1]==0)
                {
                    ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose;
                }
                a=(a+3)%4;
                b=(b+7)%8;
                c=(c+11)%12;
                break;
            case 3:
                break;
            }
        }
        ind[i].fitness=0;
        ind[i].empty=0;
        for (j=0; j<4; j++)
        {
            if (y[j]==0)
                ind[i].fitness++;

        }
        for (j=0; j<8; j++)
        {
            if (r[j]==1)
                ind[i].fitness++;
        }
        for (j=0; j<12; j++)
        {
            if (g[j]==2)
                ind[i].fitness++;
        }
        for (j=0; j<length; j++)
        {
            if (ind[i].gene[j]==3)
                ind[i].empty++;
        }

        if ( fabs(ind[i].fitness-24)<=0.01)
        {
            fprint(2);
            exit(1);
        }
        ind[i].fitness=ind[i].fitness-ind[i].empty*w1;
    }
}

void ready()
{
    int i=0,j,k,l,t,a=0,b=0,c=0;
    for (t=0;t<4; t++)
        y[t]=y1[t];
    for (t=0;t<8; t++)
        r[t]=r1[t];
    for (t=0;t<12; t++)
        g[t]=g1[t];
    for (j=0; j<length; j++)
        {
            switch(ind[i].gene[j])
            {
choose2:
            case 0:
                if (j<length-1&&ind[i].gene[j+1]==2)
                {
                    ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose2;
                }
                a=(a+1)%4;
                b=(b+1)%8;
                c=(c+1)%12;
                break;
            case 1:
                if (j<length-2&&ind[i].gene[j+1]==1&&ind[i].gene[j+2]==1)
                {
                    ind[i].gene[j+2]=ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose2;
                }
                t=g[c];
                g[c]=r[b];
                r[b]=y[a];
                y[a]=t;
                break;
            case 2:
                if (j<length-1&&ind[i].gene[j+1]==0)
                {
                    ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose2;
                }
                a=(a+3)%4;
                b=(b+7)%8;
                c=(c+11)%12;
                break;
            case 3:
                break;
            }
        }
        a1=a;
        b1=b;
        c1=c;
}


void fit1(int beginer,int ender)
{
    int i,j,k,l,t;
    for(k=0; k<100; k++)
    {
        ind[k].fitness=0;
    }
    for (i=beginer; i<ender; i++)
    {
        int y[4],r[8],g[12],a=a1,b=b1,c=c1;
    for (t=0;t<4; t++)
        y[t]=y1[t];
    for (t=0;t<8; t++)
        r[t]=r1[t];
    for (t=0;t<12; t++)
        g[t]=g1[t];
        for (j=0; j<length; j++)
        {
            switch(ind[i].gene[j])
            {
choose1:
            case 0:
                if (j<length-1&&ind[i].gene[j+1]==2)
                {
                    ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose1;
                }
                a=(a+1)%4;
                b=(b+1)%8;
                c=(c+1)%12;
                break;
            case 1:
                if (j<length-2&&ind[i].gene[j+1]==1&&ind[i].gene[j+2]==1)
                {
                    ind[i].gene[j+2]=ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose1;
                }
                t=g[c];
                g[c]=r[b];
                r[b]=y[a];
                y[a]=t;
                break;
            case 2:
                if (j<length-1&&ind[i].gene[j+1]==0)
                {
                    ind[i].gene[j+1]=ind[i].gene[j]=3;
                    goto choose1;
                }
                a=(a+3)%4;
                b=(b+7)%8;
                c=(c+11)%12;
                break;
            case 3:
                break;
            }
        }
        ind[i].fitness=0;
        ind[i].empty=0;
        for (j=0; j<4; j++)
        {
            if (y[j]==0)
                ind[i].fitness++;

        }
        for (j=0; j<8; j++)
        {
            if (r[j]==1)
                ind[i].fitness++;
        }
        for (j=0; j<12; j++)
        {
            if (g[j]==2)
                ind[i].fitness++;
        }
        for (j=0; j<length; j++)
        {
            if (ind[i].gene[j]==3)
                ind[i].empty++;
        }

        if ( fabs(ind[i].fitness-24)<=0.01)
        {
            fprint(2);
            exit(1);
        }
        ind[i].fitness=ind[i].fitness-ind[i].empty*w1;
    }
}

void reserve()
{
    int i,j;
    for (i=100; i<1000; i++)
    {
        for (j=0; j<length; j++)
        {
            ind[i].gene[j]=3;
        }
        ind[i].fitness=0;
        ind[i].empty=0;
    }
}

void replay()
{
    int i,j,k,t,m,n,flag=0,step=0;
    for (i=0;i<4; i++)
        y1[i]=y[i];
    for (i=0;i<8; i++)
        r1[i]=r[i];
    for (i=0;i<12; i++)
        g1[i]=g[i];
    srand(time(NULL));
    for (i=0; i<100; i++)
    {
        for (j=0; j<length; j++)
        {
            ind[i].gene[j]=rand()%4;
        }
    }
    while(step<=200)
    {
        fit1(0,100);
        sort(0,100);
        change();
        fit1(100,1000);
        sort(0,1000);
        reserve();
        step++;
    }
    fprint(0);
}

int main()
{
    int i,j,k,t,m,n,flag=0,step=0;
    srand(time(NULL));
    for (i=0; i<100; i++)
    {
        for (j=0; j<length; j++)
        {
            ind[i].gene[j]=rand()%4;
        }
    }
    while(step<=200)
    {
        fit(0,100);
        sort(0,100);
        change();
        fit(100,1000);
        sort(0,1000);
        reserve();
        if (ind[0].fitness+ind[0].empty*w1>=17.9)
            {fprint(1);
        ready();
        replay();}
        step++;
    }
    fprint(0);
    return 0;
}
