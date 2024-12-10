#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
void AddDish(DishNode** head) {

    char newname[MAX_DISH_NAME];
    float newprice;
    float newcost;
    int newtime;
    printf("请输入添加的菜品信息\n");
    printf("菜品名称：\n");
    scanf_s(" %s",&newname);
    printf("菜品售价：\n");
    scanf_s(" %f",&newprice);
    printf("菜品成本：\n");
    scanf_s(" %f",&newcost);
    printf("菜品烹饪时间：\n");
    scanf_s(" %d",&newtime);

    DishNode* newDish = (DishNode*)malloc(sizeof(DishNode));            //
    strcpy(newDish->dish.name, newname);                                    //
    newDish->dish.price = newprice;                                         //
    newDish->dish.cost = newcost;                                           //
    newDish->dish.time = newtime;                                           //
    newDish->next = *head;                                                  // 新节点插入到链表的头部
    *head = newDish;
    SyncToCSV(*head); // 每次增后同步
}
