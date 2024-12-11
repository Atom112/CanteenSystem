#include <stdio.h>
#include <time.h>
#include "Functions.h"
extern int mintime;
void TakeoutFeedback (TKC tkc,float *TotalPrice) {
    time_t t;
    time(&t); // 获取当前的时间戳
    tm *localTime = localtime(&t);// 将时间戳转换为本地时间
    int plushour=0;
    int plusminute=0;
    TimeTransform(&plushour,&plusminute,mintime);
    printf("请输入您的地址：\n");
    scanf("%s",&tkc.address);
    printf("外送至%s\n", tkc.address);
    printf("总金额%.1f元\n", *TotalPrice);
    printf("预计制作完成时间（不含外送）%02d:%02d\n",
           localTime->tm_hour + plushour,
           localTime->tm_min + plusminute);
    printf("祝您用餐愉快\n");
}