#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
int ReadMenu(int *MenuDishNumber ,Dish dishes[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen("Dishes.csv", "r");

    if (file == NULL) {
        perror("打开菜单失败，请联系管理员");
        return EXIT_FAILURE; // 返回错误状态
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(dishes[*MenuDishNumber].name, strtok(line, ","));
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");
        dishes[*MenuDishNumber].price = atof(price_str);
        dishes[*MenuDishNumber].cost = atof(cost_str);
        dishes[*MenuDishNumber].time = atoi(time_str);
        dishes[*MenuDishNumber].profit = dishes[*MenuDishNumber].price - dishes[*MenuDishNumber].cost;
        dishes[*MenuDishNumber].id = *MenuDishNumber+1;
        (*MenuDishNumber)++;
    }

    fclose(file);

    for (int i = 0; i < *MenuDishNumber; i++) {
        printf("菜品序号：%d\n",dishes[i].id);
        printf("菜名: %s\n", dishes[i].name);
        printf("价格: %.1f 元\n", dishes[i].price);
        printf("时间: %d min\n", dishes[i].time);
        printf("\n");
    }
    return *MenuDishNumber;
}
