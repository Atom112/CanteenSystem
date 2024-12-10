#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
extern int BillID;
int mintime;
void Order(DishNode *head, float *T_Profit, float *T_Cost, float *T_Price) {
    extern int best;
    int TotalDish = 0;              //当前订单中含有的菜数
    int Choice = 0;                 //选择模式
    int DishOrderNumber = 0;        //点餐的份数
    int ListId = 0;
    int k =3;
    int *DishTime= (int *)malloc(sizeof(int)*MAX_DISHES);

    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"订单编号：%d\n\n",BillID);
    fclose(file);

    printf("请输入点餐的餐品编号及份数：（结算请输入'-1'）\n");

    while(true) {
        printf("餐品编号：");
        scanf("%d", &Choice);

        if(Choice==-1) {
            break;
        }

        DishNode* current = head;
        while (current != NULL) {
            if (current->dish.id == Choice) {
                break; // 找到菜品
            }
            current = current->next;
        }

        if (current == NULL) {
            perror("餐品编号不存在！请重新选择");
            continue;
        }

        printf("餐品份数：");
        scanf("%d", &DishOrderNumber);
        if (DishOrderNumber <= 0) {
            printf("点餐份数必须大于零！");
            continue;
        }
        TotalDish += DishOrderNumber;

        while(ListId < TotalDish) {
            DishTime[ListId] = current->dish.time;
            ListId++;
        }

        *T_Cost += current->dish.cost * (float)DishOrderNumber;
        *T_Price += current->dish.price * (float)DishOrderNumber;
        *T_Profit += current->dish.profit * (float)DishOrderNumber;
        WriteDetailToBills(current,DishOrderNumber);
    }

    printf("总份数%d\n", TotalDish);
    WriteDataToBills(*T_Price,*T_Cost,*T_Profit);
    mintime=calculate_min_cook_time(DishTime,TotalDish);

}