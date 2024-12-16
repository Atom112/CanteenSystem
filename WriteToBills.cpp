#include <stdio.h>
#include <time.h>
#include "Functions.h"

void WriteDetailToBills (DishNode* current,int DishNumber) {
    FILE *file;
    file = fopen("Bills.dll","a");
    fprintf(file,"%s*%d\n",current->dish.name,DishNumber);
    fclose(file);
}

void WriteDataToBills (float TotalPrice,float TotalCost,float TotalProfit) {
    time_t t;
    time(&t); // 获取当前的时间戳
    tm *localTime = localtime(&t);// 将时间戳转换为本地时间

    FILE *file;
    file = fopen("Bills.dll","a");
    fprintf(file,"\n订单总额：%.1f元\n",TotalPrice);
    fprintf(file,"订单总成本：%.1f元\n",TotalCost);
    fprintf(file,"订单总利润：%.1f元\n",TotalProfit);
    fprintf(file,"下单时间：%04d-%02d-%02d %02d:%02d:%02d\n",
           localTime->tm_year + 1900,
           localTime->tm_mon + 1,
           localTime->tm_mday,
           localTime->tm_hour,
           localTime->tm_min,
           localTime->tm_sec);
    fprintf(file,"#---------------------------#\n\n");
    fclose(file);
}

void WriteSumToBills (float S_Price,float S_Cost,float S_Profit) {
    time_t t;
    time(&t); // 获取当前的时间戳
    tm *localTime = localtime(&t);// 将时间戳转换为本地时间

    FILE *file;
    file = fopen("Bills.dll","a");
    fprintf(file,"%04d-%02d-%02d\n",
           localTime->tm_year + 1900,
           localTime->tm_mon + 1,
           localTime->tm_mday);
    fprintf(file,"当日总销售额：%.1f元\n",S_Price);
    fprintf(file,"当日食材总成本：%.1f元\n",S_Cost);
    fprintf(file,"当日总利润：%.1f元\n\n",S_Profit);
    fclose(file);
}