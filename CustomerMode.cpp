#include <stdio.h>
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
        DishNode *dishes = NULL;
        char mode;                                  //ѡ����ģʽ�ı���
        TC tc={0,0};                 //������ʳ�˿Ͷ���
        TKC tkc={0,0};           //�������͹˿Ͷ���
        while (true) {
            printf("��ѡ���ͷ�ʽ��A-��ʳ��B-���ͣ�Q-����\n");
            scanf_s(" %c",&mode);

            if (mode == 'A'||mode == 'a') {
                BillID++;
                ReadMenu(&dishes);
                Order(dishes,&TotalProfit,&TotalCost,&TotalPrice);
                TableFeedback (tc,&TotalPrice);
                AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);
                break;
            }
            else if (mode == 'B'||mode == 'b') {
                BillID++;
                ReadMenu(&dishes);
                Order(dishes,&TotalProfit,&TotalCost,&TotalPrice);
                TakeoutFeedback (tkc,&TotalPrice);
                AddToSum (&sum_price,&sum_profit,&sum_cost,&TotalPrice,&TotalProfit,&TotalCost);
                break;
            }
            else if(mode == 'Q'||mode == 'q') {
                break;
            }else {
                printf("��ʽ�����ڣ�������ѡ��\n");
            }
        }

        printf("�Ƿ��˳����ģʽ����Y-�ǣ�N-��\n");
        char a;
        scanf(" %c",&a);
        if(a=='Y'||a=='y') {
            IdentityVerification();
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