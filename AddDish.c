#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
void AddDish(DishNode** head) {

    char newname[MAX_DISH_NAME];
    float newprice;
    float newcost;
    int newtime;
    printf("��������ӵĲ�Ʒ��Ϣ\n");
    printf("��Ʒ���ƣ�\n");
    scanf_s(" %s",&newname);
    printf("��Ʒ�ۼۣ�\n");
    scanf_s(" %f",&newprice);
    printf("��Ʒ�ɱ���\n");
    scanf_s(" %f",&newcost);
    printf("��Ʒ���ʱ�䣺\n");
    scanf_s(" %d",&newtime);

    DishNode* newDish = (DishNode*)malloc(sizeof(DishNode));            //
    strcpy(newDish->dish.name, newname);                                    //
    newDish->dish.price = newprice;                                         //
    newDish->dish.cost = newcost;                                           //
    newDish->dish.time = newtime;                                           //
    newDish->next = *head;                                                  // �½ڵ���뵽�����ͷ��
    *head = newDish;
    SyncToCSV(*head); // ÿ������ͬ��
}
