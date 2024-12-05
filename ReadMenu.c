#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
int ReadMenu(DishNode **head) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen("Dishes.csv", "r");

    if (file == NULL) {
        perror("打开菜单失败，请联系管理员");
        return EXIT_FAILURE; // 返回错误状态
    }

    *head = NULL;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        // 创建新节点
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            perror("内存分配失败");
            fclose(file);
            return EXIT_FAILURE;
        }

        strcpy(newNode->dish.name, strtok(line, ","));
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");
        newNode->dish.price = atof(price_str);
        newNode->dish.cost = atof(cost_str);
        newNode->dish.time = atoi(time_str);
        newNode->dish.profit = newNode->dish.price - newNode->dish.cost;
        newNode->dish.id = (*head == NULL) ? 1 : (*head)->dish.id + 1; // ID自增
        newNode->next = *head; // 新节点指向当前头
        *head = newNode; // 更新头部为新节点
    }
        fclose(file);
        // 显示菜单
        DishNode* current = *head;
        while (current != NULL) {
            printf("菜品序号：%d\n", current->dish.id);
            printf("菜名: %s\n", current->dish.name);
            printf("价格: %.1f 元\n", current->dish.price);
            printf("烹饪时间: %d min\n", current->dish.time);
            printf("\n");
            current = current->next;

    }
    return 1;
}