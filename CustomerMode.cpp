#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
extern int BillID;          //订单编号
extern float sum_price;
extern float sum_profit;
extern float sum_cost;
extern float TotalCost;
extern float TotalPrice;
extern float TotalProfit;

void CustomerMode () {
    while (true) {
        DishNode *dishes = NULL;                   //初始化链表
        char mode;                                 //选择点餐模式的变量
        TC tc={0,0};                 //创建堂食顾客对象
        TKC tkc={0,0};           //创建外送顾客对象
        while (true) {
            printf("请选择点餐方式：A-堂食，B-外送，Q-返回\n");
            scanf_s(" %c",&mode);
            //简单的选择来实现各种模式
            if (mode == 'A'||mode == 'a') {
                BillID++;
                ReadMenu(&dishes);
                Order(dishes,&TotalProfit,&TotalCost,&TotalPrice);
                TableFeedback (tc,&TotalPrice);
                AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);

            }
            else if (mode == 'B'||mode == 'b') {
                BillID++;
                ReadMenu(&dishes);
                Order(dishes,&TotalProfit,&TotalCost,&TotalPrice);
                TakeoutFeedback (tkc,&TotalPrice);
                AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);
            }
            else if(mode == 'Q'||mode == 'q') {
                break;
            }else {
                printf("方式不存在，请重新选择\n");
            }
        }
        printf("是否退出点餐模式？（Y-是，N-否）\n");
        char a;
        scanf(" %c",&a);
        if(a=='Y'||a=='y') {
            IdentityVerification();
            DishNode* current = dishes;
            WriteSumToBills(sum_price,sum_cost,sum_profit);
            //释放链表空间
            while (current != NULL) {
                DishNode* temp = current;
                current = current->next;
                free(temp);
            }
            break;
        }
    }
}