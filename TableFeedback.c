#include <stdio.h>
#include "Functions.h"
void TableFeedback (TC tc,float *TotalPrice,int *TotalTime) {
    printf("�������������ţ�\n");
    scanf_s("%d",&tc.TableID);
    printf("����%d��\n",tc.TableID);
    printf("�ܽ��%.1fԪ\n", *TotalPrice);
    printf("Ԥ�Ƶȴ�ʱ��%d min\n", *TotalTime);
    printf("ף���ò����\n");
}