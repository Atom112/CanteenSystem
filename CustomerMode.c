#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"

float sum_price = 0;          //ȫ�����������۶�
float sum_profit = 0;         //ȫ������������
float sum_cost = 0;           //ȫ�������ܳɱ�
float TotalCost = 0;
float TotalPrice = 0;
float TotalProfit = 0;

void CustomerMode () {
    while (true) {
        int TotalTime = 0;
        int MenuDishNumber = 0;                     //ͳ�Ʋ˵���Ʒ�����ı���
        char mode;                                  //ѡ����ģʽ�ı���
        Dish dishes[MAX_DISHES];                    //����Dish�ṹ�����飬�����洢n����
        TC tc={0,0};                 //������ʳ�˿Ͷ���
        TKC tkc={0,0};           //�������͹˿Ͷ���

        printf("��ѡ���ͷ�ʽ��A-��ʳ��B-����\n");
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
            perror("��ʽ�����ڣ�������ѡ��");
        }

        printf("�Ƿ��˳����ģʽ����Y-�ǣ�N-��\n");
        char a;
        scanf(" %c",&a);

        if(a=='Y'||a=='y') {
            break;
        }
    }
}