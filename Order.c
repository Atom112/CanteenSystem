#include <stdbool.h>
#include <stdio.h>
#include "Functions.h"

void Order(int MDN,Dish dishes[],float *T_Profit,float *T_Cost,float *T_Price,int *T_Time) {
    int TotalDish = 0;              //��ǰ�����к��еĲ���
    int Choice = 0;                 //ѡ��ģʽ
    int DishOrderNumber = 0;        //��͵ķ���
    printf("�������͵Ĳ�Ʒ��ż�������������������'-1'��\n");

    while(true) {
        printf("��Ʒ��ţ�");
        scanf("%d", &Choice);

        if(Choice==-1) {
            break;
        }

        if (Choice <= 0 || Choice > MDN) {
            perror("��Ʒ��Ų����ڣ�������ѡ��");
            continue;
        }

        printf("��Ʒ������");
        scanf("%d", &DishOrderNumber);

        *T_Cost += dishes[Choice-1].cost * (float)DishOrderNumber;
        *T_Price += dishes[Choice-1].price * (float)DishOrderNumber;
        *T_Profit += dishes[Choice-1].profit * (float)DishOrderNumber;
        *T_Time += dishes[Choice-1].time * DishOrderNumber;
        TotalDish += DishOrderNumber;
    }
    printf("�ܷ���%d\n", TotalDish);
}
