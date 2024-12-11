#include <stdio.h>
#include "Functions.h"
int BillID = 0;
float sum_price = 0;          //全部订单总销售额
float sum_profit = 0;         //全部订单总利润
float sum_cost = 0;           //全部订单总成本
float TotalCost = 0;
float TotalPrice = 0;
float TotalProfit = 0;
int main() {
    printf("餐厅管理系统V1.0\n");
    while (true) {
        printf("请选择模式（M-管理模式，C-用户点餐模式，Q-退出系统）\n");
        char system_mode;
        scanf_s(" %c",&system_mode);
        if (system_mode == 'M'|| system_mode == 'm') {
            bool is = IdentityVerification();
            if (is) {
                ManagerMode ();
            }
        }else if(system_mode == 'C'|| system_mode == 'c') {
            CustomerMode ();
        }else if(system_mode == 'Q'|| system_mode == 'q') {
            break;
        }else {
            printf("模式不存在，请重新选择\n");
        }
    }
    return 0;
}