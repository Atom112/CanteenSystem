#include <stdio.h>
#include <time.h>
#include "Functions.h"
extern int mintime;
void TableFeedback (TC tc,float *TotalPrice) {

    time_t t;
    time(&t); // 获取当前的时间戳
    tm *localTime = localtime(&t);// 将时间戳转换为本地时间
    int plushour=0;
    int plusminute=0;
    TimeTransform(&plushour,&plusminute,mintime);
    printf("请输入您的桌号：\n");
    scanf_s("%d",&tc.TableID);
    printf("送至%d桌\n",tc.TableID);
    printf("总金额%.1f元\n", *TotalPrice);
    printf("预计制作完成时间 %02d:%02d\n",
            localTime->tm_hour + plushour,
            localTime->tm_min + plusminute);
    printf("祝您用餐愉快\n");
}