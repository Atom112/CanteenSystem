#include <stdio.h>
#include <string.h>
#include "Functions.h"
DishNode* SearchDish(DishNode *head) {
    DishNode* current = head;
    char newname[MAX_DISH_NAME];
    while(true) {
        printf("请输入要查找的菜品名称：（Q-返回）\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0]));
        if (strcmp(newname, "Q") == 0|| strcmp(newname, "q") == 0) {
            break;
        }
        while (current != NULL) {
            if (strstr(current->dish.name, newname) != NULL) {
                printf("菜品名称：%s\n", current->dish.name);
                printf("菜品售价：%.1f元\n", current->dish.price);
                printf("菜品成本：%.1f元\n", current->dish.cost);
                printf("烹饪时间：%d min\n", current->dish.time);
                return current;
                // 找到对应的菜品
            }
            current = current->next;
        }
        printf("未找到菜品\n"); // 没有找到
    }return NULL;
}
