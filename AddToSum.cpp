#include "Functions.h"
/* ����ȫ�ֱ����ܳ��۶�������ܳɱ��ļӺ� */
void AddToSum (float *S_price,float *S_profit,float *S_cost,float *T_price,float *T_profit,float *T_cost) {
    *S_price += *T_price;
    *S_profit += *T_profit;
    *S_cost += *T_cost;
    *T_price = 0;    //��ÿһ���������ܺ����ã�������һ���ļ���
    *T_profit = 0;
    *T_cost = 0;
}