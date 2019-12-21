#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Game check0
int n[26]= {0};

int check0(int n[],int i)
{return 0;
}
int check60(int n[],int i)
{
    int q=-4,w=0,e=4,a=16,s=-21,d=5,j;
    for (j=1; j<=i; j++)
    {
        switch (n[j])
        {
        case 0:
            a-=2;
            s+=2;
            d--;
            w++;
            e--;
            q++;
            break;
        case 1:
            w-=3;
            a++;
            s++;
            d++;
            break;
        case 2:
            q--;
            w++;
            s--;
            e++;
            break;
        }
    }
    if(a==0&&s==0&&d==0&&q==0&&w==0&&e==0) return 1;
    return 0;
}

int check17(int n[],int i)
{
    int j,k,l,a=5,b=5,c=5;
    for (j=1; j<=i; j++)
    {
        switch (n[j])
        {
        case 0:
            a=(a+1)%10;
            b=(b+1)%10;
            break;
        case 1:
            b=9-b;
            break;
        case 2:
            b=(b+9)%10;
            c=(c+9)%10;
            break;
        }
    }
    if (a+b+c==0)
        return 1;
    return 0;
}


int main()
{
    int i,j,k,l,N,max1,flag=0;
    for (i=15; i<16; i++)
    {
        max1=(int)(pow(3,i)+0.00001);
        for(k=0; k<max1; k++)
        {
            N=k;
            for (j=0; j<=25; j++)
                n[j]=0;
            for (j=i-1; j>=0; j--)
            {

                n[j+1]=(int)(N/pow(3,j));
                N=N%(int)(pow(3,j));
            }
            if (Game(n,i))
            {   printf("%d steps are enough,here's the answer:",i);
                for(l=1; l<=i; l++)
                    printf("%2d",n[l]+1);
                printf("\n");
                flag=1;
                return 0;
            }
        }
       if (flag==0)
        printf("Until %d has been tried£¬no answer!!!!\n",i);
    }
    if (flag==0)
        printf("NO ANSWER!!!!\n");
    return 0;
}
