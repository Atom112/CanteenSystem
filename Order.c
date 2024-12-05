#include <stdbool.h>
#include <stdio.h>
#include "Functions.h"

void Order(int MDN,Dish dishes[],float *T_Profit,float *T_Cost,float *T_Price,int *T_Time) {
    int TotalDish = 0;              //当前订单中含有的菜数
    int Choice = 0;                 //选择模式
    int DishOrderNumber = 0;        //点餐的份数
    printf("请输入点餐的餐品编号及份数：（结算请输入'-1'）\n");

    while(true) {
        printf("餐品编号：");
        scanf("%d", &Choice);

        if(Choice==-1) {
            break;
        }

        if (Choice <= 0 || Choice > MDN) {
            perror("餐品编号不存在！请重新选择");
            continue;
        }

        printf("餐品份数：");
        scanf("%d", &DishOrderNumber);

        *T_Cost += dishes[Choice-1].cost * (float)DishOrderNumber;
        *T_Price += dishes[Choice-1].price * (float)DishOrderNumber;
        *T_Profit += dishes[Choice-1].profit * (float)DishOrderNumber;
        *T_Time += dishes[Choice-1].time * DishOrderNumber;
        TotalDish += DishOrderNumber;
    }
    printf("总份数%d\n", TotalDish);
}
