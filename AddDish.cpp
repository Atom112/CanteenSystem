#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"

/* 对链表中的菜单进行增加，新增的菜品添加在链表头部 */
void AddDish(DishNode** head) {

    char newname[MAX_DISH_NAME];
    float newprice;
    float newcost;
    int newtime;
    while(true) {
        printf("请输入添加的菜品信息：（Q-退出）\n");                             //键盘录入新菜品的各项信息
        printf("菜品名称：\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0]));
        if (strcmp(newname, "Q") == 0|| strcmp(newname, "q") == 0) {
            break;
        }
        printf("菜品售价：\n");
        scanf_s(" %f",&newprice);
        printf("菜品成本：\n");
        scanf_s(" %f",&newcost);
        printf("菜品烹饪时间：\n");
        scanf_s(" %d",&newtime);

        DishNode* newDish = (DishNode*)malloc(sizeof(DishNode));            // 新建一个链表节点
        strcpy(newDish->dish.name, newname);                                    // 对各个成员变量赋值
        newDish->dish.price = newprice;                                         //
        newDish->dish.cost = newcost;                                           //
        newDish->dish.time = newtime;                                           //
        newDish->next = *head;                                                  // 新节点插入到链表的头部
        *head = newDish;                                                        // 更新链表头节点为当前新增节点
        SyncToDish(*head);                                                       // 每次增后同步菜单及菜单副本
        SyncToDishcpy(*head);
    }
}
