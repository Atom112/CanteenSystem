#include <stdio.h>
#include <time.h>
#include "Functions.h"
extern int mintime;
void TakeoutFeedback (TKC tkc,float *TotalPrice) {
    time_t t;
    time(&t); // ��ȡ��ǰ��ʱ���
    tm *localTime = localtime(&t);// ��ʱ���ת��Ϊ����ʱ��
    int plushour=0;
    int plusminute=0;
    TimeTransform(&plushour,&plusminute,mintime);
    printf("���������ĵ�ַ��\n");
    scanf("%s",&tkc.address);
    printf("������%s\n", tkc.address);
    printf("�ܽ��%.1fԪ\n", *TotalPrice);
    printf("Ԥ���������ʱ�䣨�������ͣ�%02d:%02d\n",
           localTime->tm_hour + plushour,
           localTime->tm_min + plusminute);
    printf("ף���ò����\n");
}