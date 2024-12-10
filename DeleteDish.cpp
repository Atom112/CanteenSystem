#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
void DeleteDish(DishNode** head) {
    DishNode* current = *head;
    DishNode* prev = NULL;
    char newname[MAX_DISH_NAME];
    printf("请输入要删除的菜品名称：\n");
    scanf_s(" %s",&newname);
    while (current != NULL && strcmp(current->dish.name, newname) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return; // 没有找到要删除的物品
    }

    if (prev == NULL) {
        *head = current->next; // 头节点被删除
    } else {
        prev->next = current->next; // 删除中间或尾部的节点
    }
    free(current);
    SyncToCSV(*head); // 每次删后同步
}
