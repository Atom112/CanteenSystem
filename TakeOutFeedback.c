#include <stdio.h>
#include "Functions.h"
void TakeoutFeedback (TKC tkc,float *TotalPrice,int *TotalTime) {
    printf("请输入您的地址：\n");
    scanf("%s",&tkc.address);
    printf("外送至%s\n", tkc.address);
    printf("总金额%.1f元\n", *TotalPrice);
    printf("预计等待（不包含外送）时间%d min\n", *TotalTime);
    printf("祝您用餐愉快\n");
}