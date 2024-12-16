#include <stdio.h>
#include <string.h>
#include "Functions.h"
// 从链表中搜索指定名称的菜品
DishNode* SearchDish(DishNode *head) {
    DishNode* current = head; // 初始化当前节点为链表头
    char newname[MAX_DISH_NAME]; // 存储用户输入的菜品名称

    while(true) { // 无限循环，直到用户选择退出
        printf("请输入要查找的菜品名称：（Q-返回）\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0])); // 获取用户输入的菜品名称

        // 检查用户是否输入了退出指令
        if (strcmp(newname, "Q") == 0 || strcmp(newname, "q") == 0) {
            break; // 用户选择退出，退出循环
        }

        // 遍历链表中的所有菜品
        while (current != NULL) {
            // 检查当前菜品名称中是否包含用户输入的名称
            if (strstr(current->dish.name, newname) != NULL) {
                // 找到匹配的菜品，打印相关信息
                printf("菜品名称：%s\n", current->dish.name);
                printf("菜品售价：%.1f元\n", current->dish.price);
                printf("菜品成本：%.1f元\n", current->dish.cost);
                printf("烹饪时间：%d min\n", current->dish.time);
                return current; // 返回找到的菜品节点
            }
            current = current->next; // 移动到下一个菜品
        }

        printf("未找到菜品\n"); // 如果循环结束还未找到，提示用户未找到任何菜品
    }

    return NULL; // 返回NULL，表示未找到任何匹配的菜品信息
}
