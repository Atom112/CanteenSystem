#include <stdbool.h>
#include <stdio.h>
#include "Functions.h"

void Order(DishNode *head, float *T_Profit, float *T_Cost, float *T_Price, int *T_Time) {
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

        DishNode* current = head;
        while (current != NULL) {
            if (current->dish.id == Choice) {
                break; // �ҵ���Ʒ
            }
            current = current->next;
        }

        if (current == NULL) {
            perror("��Ʒ��Ų����ڣ�������ѡ��");
            continue;
        }

        printf("��Ʒ������");
        scanf("%d", &DishOrderNumber);

        *T_Cost += current->dish.cost * (float)DishOrderNumber;
        *T_Price += current->dish.price * (float)DishOrderNumber;
        *T_Profit += current->dish.profit * (float)DishOrderNumber;
        *T_Time += current->dish.time * DishOrderNumber;
        TotalDish += DishOrderNumber;
    }
    printf("�ܷ���%d\n", TotalDish);
}