#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#include "print_table.h"
void PreReadMenu() {
    FILE *source = fopen("Dishescpy.csv", "r");
    FILE *target = fopen("Dishes.csv", "w"); // 以写模式打开目标文件，会清空原文件内容

    if (source == NULL) {
        perror("无法打开源文件\n");
        return;
    }

    if (target == NULL) {
        perror("无法打开目标文件\n");
        fclose(source);
        return;
    }

    char buffer[1024]; // 定义一个缓冲区

    // 逐行读取源文件并写入目标文件
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, target);
    }

    // 关闭文件
    fclose(source);
    fclose(target);
};

int ReadMenu(DishNode **head) {

while (true) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen("Dishes.csv", "r");

    if (file == NULL) {
        printf("打开菜单失败，请联系管理员\n");

    }

    *head = NULL;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        // 创建新节点
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            perror("内存分配失败");
            fclose(file);
            return false; // 返回false
        }

        char *name = strtok(line, ",");
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");

        // 检查字段是否有缺失
        if (name == NULL || price_str == NULL || cost_str == NULL || time_str == NULL) {
            PreReadMenu();
            break;
        }

    }
    fclose(file);
    free(*head);
    break;
}



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
    DishNode* dishArray[MAX_DISHES];
    int idx = 0;
    DishNode* current = *head;

    while (current != NULL && idx < MAX_DISHES) {
        dishArray[idx++] = current;
        current = current->next;
    }
    for (int i = 0; i < idx - 1; i++) {
        for (int j = 0; j < idx - i - 1; j++) {
            if (dishArray[j]->dish.id > dishArray[j + 1]->dish.id) {
                // 交换位置
                DishNode* temp = dishArray[j];
                dishArray[j] = dishArray[j + 1];
                dishArray[j + 1] = temp;
            }
        }
    }


    TABLE_HANDLE handle; // 表格句柄
    TABLE_COL tableCol;  // 表格列结构体

    tableCol.count = 4; // 设置列数
    int width[] = { 16, 16, 16, 16}; // 定义列宽
    tableCol.width = width; // 关联列宽到表格列结构体
    TableInit(&handle, &tableCol, table_default_border); // 初始化表格
    TableAddCol(handle, TABLE_MODE_MIDDLE, "菜品序号 菜名 价格/元  烹饪时间/min"); // 添加列标题
    for (int i = 0; i < idx; i++) {
        TableAddCol(handle, TABLE_MODE_MIDDLE, "%d %s %.1f %d", dishArray[i]->dish.id, dishArray[i]->dish.name, dishArray[i]->dish.price, dishArray[i]->dish.time); // 添加数据行
    }
    TablePrint(handle); // 打印表格
    TableDestroy(handle); // 释放表格资源

    return 1;
}