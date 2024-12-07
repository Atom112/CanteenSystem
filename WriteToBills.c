#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"
void WriteDetailToBills (DishNode* current,int DishNumber) {
    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"%s*%d\n",current->dish.name,DishNumber);
    fclose(file);
}

void WriteDataToBills (float TotalPrice,float TotalCost,float TotalProfit) {
    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"\n�����ܶ%.1fԪ\n",TotalPrice);
    fprintf(file,"�����ܳɱ���%.1fԪ\n",TotalCost);
    fprintf(file,"����������%.1fԪ\n",TotalProfit);
    fprintf(file,"#---------------------------#\n\n");
    fclose(file);
}

void WriteSumToBills (float S_Price,float S_Cost,float S_Profit) {
    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"���������۶%.1fԪ\n",S_Price);
    fprintf(file,"����ʳ���ܳɱ���%.1fԪ\n",S_Cost);
    fprintf(file,"����������%.1fԪ\n\n",S_Profit);
    fclose(file);
}