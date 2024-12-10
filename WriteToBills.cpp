#include <stdio.h>
#include <time.h>
#include "Functions.h"

void WriteDetailToBills (DishNode* current,int DishNumber) {
    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"%s*%d\n",current->dish.name,DishNumber);
    fclose(file);
}

void WriteDataToBills (float TotalPrice,float TotalCost,float TotalProfit) {
    time_t t;
    time(&t); // ��ȡ��ǰ��ʱ���
    tm *localTime = localtime(&t);// ��ʱ���ת��Ϊ����ʱ��

    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"\n�����ܶ%.1fԪ\n",TotalPrice);
    fprintf(file,"�����ܳɱ���%.1fԪ\n",TotalCost);
    fprintf(file,"����������%.1fԪ\n",TotalProfit);
    fprintf(file,"�µ�ʱ�䣺%04d-%02d-%02d %02d:%02d:%02d\n",
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
    time(&t); // ��ȡ��ǰ��ʱ���
    tm *localTime = localtime(&t);// ��ʱ���ת��Ϊ����ʱ��

    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"%04d-%02d-%02d\n",
           localTime->tm_year + 1900,
           localTime->tm_mon + 1,
           localTime->tm_mday);
    fprintf(file,"���������۶%.1fԪ\n",S_Price);
    fprintf(file,"����ʳ���ܳɱ���%.1fԪ\n",S_Cost);
    fprintf(file,"����������%.1fԪ\n\n",S_Profit);
    fclose(file);
}