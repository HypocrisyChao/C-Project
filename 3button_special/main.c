#include <stdio.h>
#include <stdlib.h>

int n[26] = {0};

int check56(int n[], int i)
{
    int a[4]={3,3,2,3},b[8]={3,2,3,3,2,2,1,2},c[12]={2,1,3,2,1,3,2,3,3,3,3,1};
    int x=3,y=7,z=11,k,j,t;
    for (j = 1; j <= i; j++)
    {
       if (n[j]==0)
        {
            t=c[z];
            c[z]=b[y];
            b[y]=a[x];
            a[x]=t;
        }
        else
        {
            x=(x+3)%4;
            y=(y+7)%8;
            z=(z+11)%12;
        }
    }
    for (k=0;k<=3;k++)
    {
        if (a[k]!=1) return 0;
    }
        for (k=0;k<=7;k++)
    {
        if (b[k]!=2) return 0;
    }
        return 1;
}

int main()
{
    long long N, max=1;
    int i, j, k, l, flag = 0;

    for (i =30 ; i < 33; i++)
    {   max=1;
        for (k=1;k<=i;k++)
        max*=2;
        for (k = 0; k < max; k++)
        {
            N = k;
            for (j = 0; j <= 25; j++)
                n[j] = 0;
            for (j = 0; j <=i-1; j++)
            {
                n[j]=N%2;
                N=N/2;
            }

            if (check56(n, i))
            {
                printf("%d steps are enough,here's the answer:", i);
                for (l = 1; l <= i; l++)
                {
                    printf("%2d", n[l] + 1);
                    if(l%5==0)
                        printf(" ");
                }

                printf("\n");
                flag = 1;
                return 0;
            }
        }
        if (flag == 0)
            printf("Until %d has been tried,no answer!!!!\n", i);
    }
    if (flag == 0)
        printf("NO ANSWER!!!!\n");
    return 0;
}
