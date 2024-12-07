#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Functions.h"
extern int BillID;
extern float sum_price;          //全部订单总销售额
extern float sum_profit;         //全部订单总利润
extern float sum_cost;           //全部订单总成本
extern float TotalCost;
extern float TotalPrice;
extern float TotalProfit;

void CustomerMode () {
    while (true) {
        int TotalTime = 0;
        DishNode *dishes = NULL;
        char mode;                                  //选择点餐模式的变量
        TC tc={0,0};                 //创建堂食顾客对象
        TKC tkc={0,0};           //创建外送顾客对象

        printf("请选择点餐方式：A-堂食，B-外送\n");
        scanf_s(" %c",&mode);
        ReadMenu(&dishes);

        if (mode == 'A'||mode == 'a') {
            BillID++;
            Order(dishes,&TotalProfit,&TotalCost,&TotalPrice,&TotalTime);
            TableFeedback (tc,&TotalPrice,&TotalTime);
            AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);
        }
        else if (mode == 'B'||mode == 'b') {
            BillID++;
            Order(dishes,&TotalProfit,&TotalCost,&TotalPrice,&TotalTime);
            TakeoutFeedback (tkc,&TotalPrice,&TotalTime);
            AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);
        }else {
            perror("方式不存在，请重新选择");
        }

        printf("是否退出点餐模式？（Y-是，N-否）\n");
        char a;
        scanf(" %c",&a);
        if(a=='Y'||a=='y') {
            DishNode* current = dishes;
            WriteSumToBills(sum_price,sum_cost,sum_profit);
            while (current != NULL) {
                DishNode* temp = current;
                current = current->next;
                free(temp);
            }
            break;
        }
    }
}