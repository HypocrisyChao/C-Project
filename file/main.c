#include<stdio.h>
#define N 2
struct stu{
    char name[10];
    int num;
    int age;
    float score;
} boya[N], boyb[N], *pa, *pb;
int main(){
    FILE *fp;
    int i;
    pa=boya;
    pb=boyb;
    if( (fp=fopen("demo.txt","wt+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    //�Ӽ��̶������ݣ����浽boya
    printf("Input data:\n");
    for(i=0; i<N; i++,pa++){
        scanf("%s %d %d %f", pa->name, &pa->num, &pa->age, &pa->score);
    }
    pa = boya;
    //��boya�е�����д�뵽�ļ�
    for(i=0; i<N; i++,pa++){
        fprintf(fp,"%s %d %d %f\n", pa->name, pa->num, pa->age, pa->score);
    }
    //�����ļ�ָ��
    rewind(fp);
    //���ļ��ж�ȡ���ݣ����浽boyb
    for(i=0; i<N; i++,pb++){
        fscanf(fp, "%s %d %d %f\n", pb->name, &pb->num, &pb->age, &pb->score);
    }
    pb=boyb;
    //��boyb�е������������ʾ��
    for(i=0; i<N; i++,pb++){
        printf("%s  %d  %d  %f\n", pb->name, pb->num, pb->age, pb->score);
    }
    fclose(fp);
    return 0;
}
