#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
extern int BillID;
int mintime=0;    //初始化最小时间
// 点餐函数，用于处理用户的订单，包括记录菜品数量和计算总成本、价格和利润
void Order(DishNode *head, float *T_Profit, float *T_Cost, float *T_Price) {
    int TotalDish = 0;              // 当前订单中含有的菜品总数
    int Choice = 0;                 // 用户选择的餐品编号
    int DishOrderNumber = 0;        // 每种餐品点餐的份数
    int ListId = 0;                 // 记录菜品时间数组的索引
    int *DishTime= (int *)malloc(sizeof(int) * MAX_DISHES); // 用于存储点餐菜品的烹饪时间

    // 打开账单文件，以追加模式打开
    FILE *file;
    file = fopen("Bills.dll", "a");
    if (file == NULL) {
        printf("无法打开账单文件！\n");
        return; // 文件打开失败，退出函数
    }

    // 写入当前订单编号到账单文件
    fprintf(file, "订单编号：%d\n\n", BillID);
    fclose(file); // 关闭文件

    // 提示用户输入菜品编号和份数
    printf("请输入点餐的餐品编号及份数：（结算请输入'-1'）\n");

    while (true) {
        printf("餐品编号：");
        scanf("%d", &Choice); // 读取用户输入的餐品编号

        // 检查用户是否输入了结束标志
        if (Choice == -1) {
            break; // 退出循环，进行结算
        }

        // 在菜品链表中查找用户选择的菜品
        DishNode* current = head; // 初始化当前节点为链表头
        while (current != NULL) {
            if (current->dish.id == Choice) {
                break; // 找到对应的菜品，跳出循环
            }
            current = current->next; // 移动到下一个节点
        }

        // 如果当前节点为 NULL，说明未找到该菜品
        if (current == NULL) {
            printf("餐品编号不存在！请重新选择\n");
            continue; // 提示用户重新输入
        }

        // 读取用户希望点的菜品份数
        printf("餐品份数：");
        scanf("%d", &DishOrderNumber);
        // 检查份数是否大于零
        if (DishOrderNumber <= 0) {
            printf("点餐份数必须大于零！\n");
            continue; // 继续下一个循环，要求重新输入
        }

        TotalDish += DishOrderNumber; // 更新总菜品数

        // 记录每份菜品的烹饪时间
        while (ListId < TotalDish) {
            DishTime[ListId] = current->dish.time; // 将当前菜品的烹饪时间记录在数组中
            ListId++;
        }

        // 计算总成本、总价格和总利润
        *T_Cost += current->dish.cost * (float)DishOrderNumber; // 更新总成本
        *T_Price += current->dish.price * (float)DishOrderNumber; // 更新总价格
        *T_Profit += current->dish.profit * (float)DishOrderNumber; // 更新总利润

        // 写入详细的账单信息
        WriteDetailToBills(current, DishOrderNumber);
    }

    // 输出总菜品份数
    printf("总份数：%d\n", TotalDish);

    // 写入总价格、总成本和总利润到账单
    WriteDataToBills(*T_Price, *T_Cost, *T_Profit);

    // 计算最小烹饪时间
    mintime = calculate_min_cook_time(DishTime, TotalDish);

    // 释放分配的内存
    free(DishTime); // 释放存储烹饪时间的数组内存
}
