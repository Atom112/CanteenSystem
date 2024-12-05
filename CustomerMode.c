#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"

float sum_price = 0;          //全部订单总销售额
float sum_profit = 0;         //全部订单总利润
float sum_cost = 0;           //全部订单总成本
float TotalCost = 0;
float TotalPrice = 0;
float TotalProfit = 0;

void CustomerMode () {
    while (true) {
        int TotalTime = 0;
        int MenuDishNumber = 0;                     //统计菜单菜品数量的变量
        char mode;                                  //选择点餐模式的变量
        Dish dishes[MAX_DISHES];                    //创建Dish结构体数组，用来存储n道菜
        TC tc={0,0};                 //创建堂食顾客对象
        TKC tkc={0,0};           //创建外送顾客对象

        printf("请选择点餐方式：A-堂食，B-外送\n");
        scanf_s(" %c",&mode);
        MenuDishNumber = ReadMenu(&MenuDishNumber,dishes);

        if (mode == 'A'||mode == 'a') {
            Order(MenuDishNumber,dishes,&TotalProfit,&TotalCost,&TotalPrice,&TotalTime);
            TableFeedback (tc,&TotalPrice,&TotalTime);
            AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);
        }
        else if (mode == 'B'||mode == 'b') {
            Order(MenuDishNumber,dishes,&TotalProfit,&TotalCost,&TotalPrice,&TotalTime);
            TakeoutFeedback (tkc,&TotalPrice,&TotalTime);
            AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);
        }else {
            perror("方式不存在，请重新选择");
        }

        printf("是否退出点餐模式？（Y-是，N-否）\n");
        char a;
        scanf(" %c",&a);

        if(a=='Y'||a=='y') {
            break;
        }
    }
}