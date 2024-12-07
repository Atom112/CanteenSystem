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
    fprintf(file,"\n订单总额：%.1f元\n",TotalPrice);
    fprintf(file,"订单总成本：%.1f元\n",TotalCost);
    fprintf(file,"订单总利润：%.1f元\n",TotalProfit);
    fprintf(file,"#---------------------------#\n\n");
    fclose(file);
}

void WriteSumToBills (float S_Price,float S_Cost,float S_Profit) {
    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"当日总销售额：%.1f元\n",S_Price);
    fprintf(file,"当日食材总成本：%.1f元\n",S_Cost);
    fprintf(file,"当日总利润：%.1f元\n\n",S_Profit);
    fclose(file);
}