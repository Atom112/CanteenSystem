#include <stdio.h>
#include <time.h>
#include "Functions.h"
extern int mintime;
void TableFeedback (TC tc,float *TotalPrice) {

    time_t t;
    time(&t); // ��ȡ��ǰ��ʱ���
    tm *localTime = localtime(&t);// ��ʱ���ת��Ϊ����ʱ��
    int plushour=0;
    int plusminute=0;
    TimeTransform(&plushour,&plusminute,mintime);
    printf("�������������ţ�\n");
    scanf_s("%d",&tc.TableID);
    printf("����%d��\n",tc.TableID);
    printf("�ܽ��%.1fԪ\n", *TotalPrice);
    printf("Ԥ���������ʱ�� %d:%d\n",
            localTime->tm_hour + plushour,
            localTime->tm_min + plusminute);
    printf("ף���ò����\n");
}