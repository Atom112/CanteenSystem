#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
// 删除指定菜品的函数
void DeleteDish(DishNode** head) {
    // 指向当前节点的指针，初始化为链表头节点
    DishNode* current = *head;
    // 指向前一个节点的指针，初始化为 NULL
    DishNode* prev = NULL;
    // 存储用户输入的菜品名称
    char newname[MAX_DISH_NAME];

    while (true) {

        printf("请输入要删除的菜品名称：（Q-返回）\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0]));

        // 检查用户是否输入了退出指令
        if (strcmp(newname, "Q") == 0 || strcmp(newname, "q") == 0) {
            break;
        }

        // 迭代链表，查找匹配的菜品名称
        while (current != NULL && strcmp(current->dish.name, newname) != 0) {
            prev = current;  // 更新前一个节点为当前节点
            current = current->next; // 移动到下一个节点
        }

        // 如果到达链表末尾且未找到匹配的菜品，退出函数
        if (current == NULL) {
            printf("未找到菜品\n");
            continue; // 没有找到要删除的物品
        }

        // 如果要删除的是头节点
        if (prev == NULL) {
            *head = current->next; // 将头节点指针指向下一个节点
        } else {
            // 删除中间或尾部的节点
            prev->next = current->next; // 将前一个节点指向当前节点的下一个节点
        }

        // 释放当前节点的内存
        free(current);
        // 每次删除后同步到 Dish和Dishcpy 文件
        SyncToDish(*head);
        SyncToDishcpy(*head);
    }
}
