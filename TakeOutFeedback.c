#include <stdio.h>
#include "Functions.h"
void TakeoutFeedback (TKC tkc,float *TotalPrice,int *TotalTime) {
    printf("���������ĵ�ַ��\n");
    scanf("%s",&tkc.address);
    printf("������%s\n", tkc.address);
    printf("�ܽ��%.1fԪ\n", *TotalPrice);
    printf("Ԥ�Ƶȴ������������ͣ�ʱ��%d min\n", *TotalTime);
    printf("ף���ò����\n");
}