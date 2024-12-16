#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#include "print_table.h"
/*检查菜单是否损坏，若有，则用副本覆盖*/
// 检查菜单文件是否损坏，若发现损坏，则用副本覆盖
void PreReadMenu(DishNode **head) {
    FILE *file;
    char line[MAX_LINE_LENGTH]; // 存储从文件中读取的每一行
    file = fopen("Dishes.dll", "rb"); // 以二进制模式打开菜单文件

    if (file == NULL) {
        printf("打开菜单失败，请联系管理员\n");
    }

    *head = NULL; // 初始化链表头为空

    // 逐行读取菜单文件
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // 去掉行末的换行符

        // 创建新节点
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            printf("内存分配失败");
            fclose(file); // 关闭文件
            return; // 返回，结束函数
        }

        // 解析行内容
        char *name = strtok(line, ",");
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");

        // 新节点指向当前头，更新头部为新节点
        newNode->next = *head;
        *head = newNode;

        // 检查字段是否有缺失
        // 如果缺失字段，则用副本文件覆盖当前文件
        if (name == NULL || price_str == NULL || cost_str == NULL || time_str == NULL) {
            fclose(file); // 关闭当前文件

            // 打开源文件和目标文件
            FILE *source = fopen("Dishescpy.dll", "rb");
            FILE *target = fopen("Dishes.dll", "wb"); // 以写模式打开目标文件，清空原文件内容

            if (source == NULL) {
                printf("无法打开源文件\n");
                return; // 返回
            }

            if (target == NULL) {
                printf("无法打开目标文件\n");
                fclose(source); // 关闭源文件
                return; // 返回
            }

            char buffer[1024]; // 定义缓冲区

            // 逐行读取源文件并写入目标文件，实现覆盖
            while (fgets(buffer, sizeof(buffer), source) != NULL) {
                fputs(buffer, target); // 写入目标文件
            }

            // 关闭文件
            fclose(source);
            fclose(target);
            break; // 退出循环
        }
    }
    free(*head); // 释放链表内存
}

// 从文件读取菜单内容并生成链表
int ReadMenu(DishNode **head) {
    PreReadMenu(head); // 检查菜单并必要时用副本覆盖

    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen("Dishes.dll", "rb"); // 以二进制模式打开菜单文件

    if (file == NULL) {
        printf("打开菜单失败，请联系管理员");
        return EXIT_FAILURE; // 返回错误状态
    }

    *head = NULL; // 初始化链表头为空

    // 逐行读取菜单文件
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // 去掉行末的换行符

        // 创建新节点
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            printf("内存分配失败");
            fclose(file); // 关闭文件
            return EXIT_FAILURE; // 返回错误状态
        }

        // 解析行内容并填充到新节点
        strcpy(newNode->dish.name, strtok(line, ",")); // 菜名
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");
        newNode->dish.price = atof(price_str); // 将价格字符串转为浮点数
        newNode->dish.cost = atof(cost_str); // 将成本字符串转为浮点数
        newNode->dish.time = atoi(time_str); // 将时间字符串转为整数
        newNode->dish.profit = newNode->dish.price - newNode->dish.cost; // 计算利润
        newNode->dish.id = (*head == NULL) ? 1 : (*head)->dish.id + 1; // ID自增，如果链表为空则ID为1
        newNode->next = *head; // 新节点指向当前头
        *head = newNode; // 更新头部为新节点
    }

    fclose(file); // 关闭文件

    // 显示菜单
    DishNode* dishArray[MAX_DISHES]; // 数组用于保存链表节点
    int idx = 0; // 当前索引
    DishNode* current = *head; // 当前链表节点

    // 将链表内容转存到数组中
    while (current != NULL && idx < MAX_DISHES) {
        dishArray[idx++] = current;
        current = current->next; // 移动到下一个节点
    }

    // 对数组进行排序（按ID排序）
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

    // 初始化和配置表格
    TABLE_HANDLE handle; // 表格句柄
    TABLE_COL tableCol;  // 表格列结构体

    tableCol.count = 4; // 设置列数
    int width[] = { 16, 16, 16, 16}; // 定义列宽
    tableCol.width = width; // 关联列宽到表格列结构

    TableInit(&handle, &tableCol, table_default_border); // 初始化表格

    // 添加列标题
    //TableAddCol(handle, TABLE_MODE_MIDDLE, "菜品序号 菜名 价格/元  烹饪时间/min");
    printf("|     菜品序号     |   菜名   |     价格/元     |   烹饪时间/min   |\n");
    // 添加数据行
    for (int i = 0; i < idx; i++) {
        TableAddCol(handle, TABLE_MODE_MIDDLE, "%d %s %.1f %d",
                    dishArray[i]->dish.id,
                    dishArray[i]->dish.name,
                    dishArray[i]->dish.price,
                    dishArray[i]->dish.time); // 添加数据行
    }

    TablePrint(handle); // 打印表格
    TableDestroy(handle); // 释放表格资源

    return 1; // 返回成功
}


