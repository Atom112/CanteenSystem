#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Functions.h"
extern int BillID;
extern float sum_price;          //ȫ�����������۶�
extern float sum_profit;         //ȫ������������
extern float sum_cost;           //ȫ�������ܳɱ�
extern float TotalCost;
extern float TotalPrice;
extern float TotalProfit;

void CustomerMode () {
    while (true) {
        int TotalTime = 0;
        DishNode *dishes = NULL;
        char mode;                                  //ѡ����ģʽ�ı���
        TC tc={0,0};                 //������ʳ�˿Ͷ���
        TKC tkc={0,0};           //�������͹˿Ͷ���

        printf("��ѡ���ͷ�ʽ��A-��ʳ��B-����\n");
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
            perror("��ʽ�����ڣ�������ѡ��");
        }

        printf("�Ƿ��˳����ģʽ����Y-�ǣ�N-��\n");
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