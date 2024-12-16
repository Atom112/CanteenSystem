#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
int T_cook = 0;
int M_cook = 0;
int P_cook = 0;
/*
 * 算法说明：通过对传入的单次菜单的时间数组进行排序
 * 优先分配时间长的菜品到高级厨师进行制作（节省的时间最多）
 * 然后将下一道菜分配给当前已分配时间最少的厨师
 * 进而实现单次订单烹饪总时间最短的局部最优解
 */

// 比较函数用于排序
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a); // 菜单中烹饪时间的降序排序
}

// 函数来计算最小烹饪时间
int calculate_min_cook_time(int* times, int num_dishes) {
    //加载当前各个厨师数量
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

        // 分配工作到烹饪时间最短的厨师
        if (min_index < T_cook) {
            cooking_time[min_index] += times[i] * 0.7; // 高级厨师减少30%
        } else if (min_index < T_cook + M_cook) {
            cooking_time[min_index] += times[i] * 0.8; // 中级厨师减少20%
        } else {
            cooking_time[min_index] += times[i]; // 初级厨师不减少时间
        }
    }

    // 分配完所有餐品后，找到厨师中的最大烹饪时间，该时间即为总的烹饪时间
    int total_cooking_time = 0;
    for (int i = 0; i < T_cook + M_cook + P_cook; i++) {
        if (cooking_time[i] > total_cooking_time) {
            total_cooking_time = cooking_time[i];
        }
    }

    free(cooking_time); // 释放内存
    return total_cooking_time;
}
/*----用于读取当前各个厨师的数量----*/
void LoadCookNumber(int * T_cook,int * M_cook, int* P_cook) {
    FILE *file;
    file = fopen("Cooks.dll","rb");
    if (file == NULL) {
        printf("设置失败\n");
    }
    fscanf(file, "%d,%d,%d", T_cook, M_cook, P_cook);//为三种厨师个数赋值，将其应用于菜品分配
    fclose(file);
}

void ResetCookNumber() {
    CookDetail();               //显示当前各种厨师数量
    FILE *file;
    file = fopen("Cooks.dll","wb");
    if (file == NULL) {
        printf("设置失败\n");
    }
    int T_Cook ;
    int M_Cook ;
    int P_Cook ;
    printf("新的高级厨师数量：\n");
    scanf_s("%d", &T_Cook);
    printf("新的中级厨师数量：\n");
    scanf_s("%d", &M_Cook);
    printf("新的初级厨师数量：\n");
    scanf_s("%d", &P_Cook);
    fprintf(file,"%d,%d,%d",T_Cook,M_Cook,P_Cook);
    fclose(file);
    printf("设置成功！\n");
    SyncToCookscpy(T_Cook,M_Cook,P_Cook);    //同步至副本
}
/*显示当前各种厨师的数量*/
void CookDetail() {
    CheckCooks();                   //检查储存厨师数量的文件是否被损坏，如果被损坏，则将副本备份覆盖于原文件
    FILE *file;
    file = fopen("Cooks.dll","rb");

    if (file == NULL) {
        printf("设置失败\n");
    }
    char cook[100];
    fgets(cook, sizeof(cook), file);
    char *T_Cook = strtok(cook, ",");
    char *M_Cook = strtok(NULL, ",");
    char *P_Cook = strtok(NULL, ",");
    printf("当前高级厨师数量：%s\n",T_Cook);
    printf("当前中级厨师数量：%s\n",M_Cook);
    printf("当前初级厨师数量：%s\n",P_Cook);
    fclose(file);
}

/*用于检查储存厨师数量的文件是否被损坏，若损坏则用副本备份覆写*/
void CheckCooks() {
    FILE *source;
    FILE *target;
    source = fopen("Cookscpy.dll","rb");
    target = fopen("Cooks.dll","rb");

    char cook[100];
    fgets(cook, sizeof(cook), target);
    char *T_Cook = strtok(cook, ",");
    char *M_Cook = strtok(NULL, ",");
    char *P_Cook = strtok(NULL, ",");

    if (source == NULL) {
        printf("无法打开源文件\n");
        return;
    }

    if (target == NULL) {
        printf("无法打开目标文件\n");
        fclose(source);
        return;
    }
fclose(target);

if (T_Cook == NULL||M_Cook == NULL||P_Cook == NULL) {
    FILE *target2 = fopen("Cooks.dll","wb");

    char buffer[1024]; // 定义一个缓冲区

    // 逐行读取源文件并写入目标文件实现覆写
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, target2);
    }

    // 关闭文件
    fclose(source);
    fclose(target2);
}
}