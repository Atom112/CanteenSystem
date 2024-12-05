#include <stdio.h>
#include "Functions.h"
void TableFeedback (TC tc,float *TotalPrice,int *TotalTime) {
    printf("请输入您的桌号：\n");
    scanf_s("%d",&tc.TableID);
    printf("送至%d桌\n",tc.TableID);
    printf("总金额%.1f元\n", *TotalPrice);
    printf("预计等待时间%d min\n", *TotalTime);
    printf("祝您用餐愉快\n");
}