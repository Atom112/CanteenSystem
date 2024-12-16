#include "Functions.h"
/* 用于全局变量总出售额、总利润、总成本的加和 */
void AddToSum (float *S_price,float *S_profit,float *S_cost,float *T_price,float *T_profit,float *T_cost) {
    *S_price += *T_price;
    *S_profit += *T_profit;
    *S_cost += *T_cost;
    *T_price = 0;    //将每一个订单的总和重置，便于下一单的计算
    *T_profit = 0;
    *T_cost = 0;
}