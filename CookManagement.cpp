#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
int T_cook = 0;
int M_cook = 0;
int P_cook = 0;
// 自定义比较函数用于排序
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a); // 降序排序
}

// 函数来计算最小烹饪时间
int calculate_min_cook_time(int* times, int num_dishes) {
    LoadCookNumber( &T_cook,&M_cook, &P_cook);
    // 排序烹饪时间数组
    int *cooking_time = (int *)calloc(T_cook + M_cook + P_cook, sizeof(int)); // 厨师的当前烹饪时间
    qsort(times, num_dishes, sizeof(int), compare); // 按时间降序排列菜品

    for (int i = 0; i < num_dishes; i++) {
        // 找到烹饪时间最短的厨师
        int min_index = 0;
        for (int j = 1; j < T_cook + M_cook + P_cook; j++) {
            if (cooking_time[j] < cooking_time[min_index]) {
                min_index = j;
            }
        }

        // 分配工作
        if (min_index < T_cook) {
            cooking_time[min_index] += times[i] * 0.7; // 高级厨师减少30%
        } else if (min_index < T_cook + M_cook) {
            cooking_time[min_index] += times[i] * 0.8; // 中级厨师减少20%
        } else {
            cooking_time[min_index] += times[i]; // 初级厨师不减少时间
        }
    }

    // 找到厨师中最大烹饪时间
    int total_cooking_time = 0;
    for (int i = 0; i < T_cook + M_cook + P_cook; i++) {
        if (cooking_time[i] > total_cooking_time) {
            total_cooking_time = cooking_time[i];
        }
    }

    free(cooking_time); // 释放内存
    return total_cooking_time;
}

void LoadCookNumber(int * T_cook,int * M_cook, int* P_cook) {
    FILE *file;
    file = fopen("Cooks.txt","r");
    if (file == NULL) {
        printf("设置失败\n");
    }
    fscanf(file, "%d,%d,%d", T_cook, M_cook, P_cook);
    fclose(file);
}

void ResetCookNumber() {
    FILE *file;
    file = fopen("Cooks.txt","w");
    if (file == NULL) {
        printf("设置失败\n");
    }
    int T_Cook ;
    int M_Cook ;
    int P_Cook ;
    printf("高级厨师数量：\n");
    scanf_s("%d", &T_Cook);
    printf("中级厨师数量：\n");
    scanf_s("%d", &M_Cook);
    printf("初级厨师数量：\n");
    scanf_s("%d", &P_Cook);
    fprintf(file,"%d,%d,%d",T_Cook,M_Cook,P_Cook);
    printf("设置成功！\n");
    fclose(file);
}

