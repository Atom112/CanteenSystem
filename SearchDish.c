#include <stdio.h>
#include <string.h>

#include "Functions.h"
DishNode* SearchDish(DishNode* head, const char* name) {
    DishNode* current = head;
    while (current != NULL) {
        if (strcmp(current->dish.name, name) == 0) {
            printf("菜品名称：%s\n", current->dish.name);
            printf("菜品售价%.1f元\n", current->dish.price);
            printf("菜品成本%.1f元\n", current->dish.cost);
            printf("烹饪时间%d min\n", current->dish.time);
            return current; // 找到对应的菜品
        }
        current = current->next;
    }
    return NULL; // 没有找到
}
