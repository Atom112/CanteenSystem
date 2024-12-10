#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
extern int BillID;
int mintime;
void Order(DishNode *head, float *T_Profit, float *T_Cost, float *T_Price) {
    extern int best;
    int TotalDish = 0;              //��ǰ�����к��еĲ���
    int Choice = 0;                 //ѡ��ģʽ
    int DishOrderNumber = 0;        //��͵ķ���
    int ListId = 0;
    int k =3;
    int *DishTime= (int *)malloc(sizeof(int)*MAX_DISHES);

    FILE *file;
    file = fopen("Bills.txt","a");
    fprintf(file,"������ţ�%d\n\n",BillID);
    fclose(file);

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
        if (DishOrderNumber <= 0) {
            printf("��ͷ�����������㣡");
            continue;
        }
        TotalDish += DishOrderNumber;

        while(ListId < TotalDish) {
            DishTime[ListId] = current->dish.time;
            ListId++;
        }

        *T_Cost += current->dish.cost * (float)DishOrderNumber;
        *T_Price += current->dish.price * (float)DishOrderNumber;
        *T_Profit += current->dish.profit * (float)DishOrderNumber;
        WriteDetailToBills(current,DishOrderNumber);
    }

    printf("�ܷ���%d\n", TotalDish);
    WriteDataToBills(*T_Price,*T_Cost,*T_Profit);
    mintime=calculate_min_cook_time(DishTime,TotalDish);

}