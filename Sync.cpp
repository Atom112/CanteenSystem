#include <stdio.h>
#include "Functions.h"

// 将菜品链表同步到指定的文件"Dishes.dll"
void SyncToDish(DishNode* head) {
    // 打开文件"Dishes.dll"用于写入二进制数据
    FILE* file = fopen("Dishes.dll", "wb");
    if (file == NULL) {
        printf("打开文件失败"); // 如果文件打开失败，输出错误信息
        return; // 返回，结束函数
    }

    DishNode* current = head; // 初始化当前节点为链表头
    while (current != NULL) { // 遍历链表
        // 将当前菜品的信息写入文件，以逗号分隔
        fprintf(file, "%s,%f,%f,%d\n", current->dish.name, current->dish.price, current->dish.cost, current->dish.time);
        current = current->next; // 移动到下一个菜品
    }

    fclose(file); // 关闭文件
}

// 将菜品链表同步到另一个副本文件"Dishescpy.dll"
void SyncToDishcpy(DishNode* head) {
    // 打开文件"Dishescpy.dll"用于写入二进制数据
    FILE* file = fopen("Dishescpy.dll", "wb");
    if (file == NULL) {
        printf("打开文件失败"); // 如果文件打开失败，输出错误信息
        return; // 返回，结束函数
    }

    DishNode* current = head; // 初始化当前节点为链表头
    while (current != NULL) { // 遍历链表
        // 将当前菜品的信息写入文件，以逗号分隔
        fprintf(file, "%s,%f,%f,%d\n", current->dish.name, current->dish.price, current->dish.cost, current->dish.time);
        current = current->next; // 移动到下一个菜品
    }

    fclose(file); // 关闭文件
}

// 将厨师信息同步到文件"Cookscpy.dll"
// 参数：t - 厨师的时间；m - 厨师的某个属性；p - 厨师的另一个属性
void SyncToCookscpy(int t, int m, int p) {
    // 打开文件"Cookscpy.dll"用于写入二进制数据
    FILE* file = fopen("Cookscpy.dll", "wb");
    if (file == NULL) {
        printf("打开文件失败"); // 如果文件打开失败，输出错误信息
        return; // 返回，结束函数
    }
    // 将厨师的信息写入文件，以逗号分隔
    fprintf(file, "%d,%d,%d", t, m, p);

    fclose(file); // 关闭文件
}

// 将用户名和密码同步到文件"passwdcpy.dll"
// 参数：n - 用户名；p - 密码
void SyncToPasswdcpy(char n[], char p[]) {
    // 打开文件"passwdcpy.dll"用于写入二进制数据
    FILE* file = fopen("passwdcpy.dll", "wb");
    if (file == NULL) {
        printf("打开文件失败"); // 如果文件打开失败，输出错误信息
        return; // 返回，结束函数
    }
    // 将用户名和密码写入文件，以逗号分隔
    fprintf(file, "%s,%s", n, p);

    fclose(file); // 关闭文件
}
