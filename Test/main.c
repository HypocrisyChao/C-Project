#include  <stdio.h>
#define STUD   30           /* �����ܵ�ѧ������ */
#define COURSE 5            /* �����ܵĿ��Կ�Ŀ�� */
void  Total(int *pScore, int sum[], float aver[], int m, int n);
void  Print(int *pScore, int sum[], float aver[], int m, int n);
int main()
{
    int     i, j, m, n, Score[STUD][COURSE], sum[STUD] ,*pScore;
    float   aver[STUD];
    printf("How many students?");
    scanf("%d", &m);
    printf("How many courses?");
    scanf("%d", &n);
    printf("Input scores:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &Score[i][j]);
        }
    }
    Total(*Score, sum, aver, m, n);
    Print(*Score, sum, aver, m, n);
    return 0;
}
void  Total(int *pScore, int sum[], float aver[], int m, int n)
{
    int  i, j;
    for (i = 0; i < m; i++)
    {
        sum[i] = 0;
        for (j = 0; j < n; j++)
        {
            sum[i] = sum[i] + pScore[i * 5 + j];
        }
        aver[i] = (float) sum[i] / n;
    }
}
void  Print(int *pScore, int sum[], float aver[], int m, int n)
{
    int  i, j;
    printf("Result:\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%4d\t", pScore[i * 5 + j]);
        }
        printf("%5d\t%6.1f\n", sum[i], aver[i]);
    }
}
