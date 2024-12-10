#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
int T_cook = 0;
int M_cook = 0;
int P_cook = 0;
// �Զ���ȽϺ�����������
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a); // ��������
}

// ������������С���ʱ��
int calculate_min_cook_time(int* times, int num_dishes) {
    LoadCookNumber( &T_cook,&M_cook, &P_cook);
    // �������ʱ������
    int *cooking_time = (int *)calloc(T_cook + M_cook + P_cook, sizeof(int)); // ��ʦ�ĵ�ǰ���ʱ��
    qsort(times, num_dishes, sizeof(int), compare); // ��ʱ�併�����в�Ʒ

    for (int i = 0; i < num_dishes; i++) {
        // �ҵ����ʱ����̵ĳ�ʦ
        int min_index = 0;
        for (int j = 1; j < T_cook + M_cook + P_cook; j++) {
            if (cooking_time[j] < cooking_time[min_index]) {
                min_index = j;
            }
        }

        // ���乤��
        if (min_index < T_cook) {
            cooking_time[min_index] += times[i] * 0.7; // �߼���ʦ����30%
        } else if (min_index < T_cook + M_cook) {
            cooking_time[min_index] += times[i] * 0.8; // �м���ʦ����20%
        } else {
            cooking_time[min_index] += times[i]; // ������ʦ������ʱ��
        }
    }

    // �ҵ���ʦ��������ʱ��
    int total_cooking_time = 0;
    for (int i = 0; i < T_cook + M_cook + P_cook; i++) {
        if (cooking_time[i] > total_cooking_time) {
            total_cooking_time = cooking_time[i];
        }
    }

    free(cooking_time); // �ͷ��ڴ�
    return total_cooking_time;
}

void LoadCookNumber(int * T_cook,int * M_cook, int* P_cook) {
    FILE *file;
    file = fopen("Cooks.txt","r");
    if (file == NULL) {
        printf("����ʧ��\n");
    }
    fscanf(file, "%d,%d,%d", T_cook, M_cook, P_cook);
    fclose(file);
}

void ResetCookNumber() {
    FILE *file;
    file = fopen("Cooks.txt","w");
    if (file == NULL) {
        printf("����ʧ��\n");
    }
    int T_Cook ;
    int M_Cook ;
    int P_Cook ;
    printf("�߼���ʦ������\n");
    scanf_s("%d", &T_Cook);
    printf("�м���ʦ������\n");
    scanf_s("%d", &M_Cook);
    printf("������ʦ������\n");
    scanf_s("%d", &P_Cook);
    fprintf(file,"%d,%d,%d",T_Cook,M_Cook,P_Cook);
    printf("���óɹ���\n");
    fclose(file);
}

