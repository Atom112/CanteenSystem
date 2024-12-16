#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
int T_cook = 0;
int M_cook = 0;
int P_cook = 0;
/*
 * �㷨˵����ͨ���Դ���ĵ��β˵���ʱ�������������
 * ���ȷ���ʱ�䳤�Ĳ�Ʒ���߼���ʦ������������ʡ��ʱ����ࣩ
 * Ȼ����һ���˷������ǰ�ѷ���ʱ�����ٵĳ�ʦ
 * ����ʵ�ֵ��ζ��������ʱ����̵ľֲ����Ž�
 */

// �ȽϺ�����������
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a); // �˵������ʱ��Ľ�������
}

// ������������С���ʱ��
int calculate_min_cook_time(int* times, int num_dishes) {
    //���ص�ǰ������ʦ����
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

        // ���乤�������ʱ����̵ĳ�ʦ
        if (min_index < T_cook) {
            cooking_time[min_index] += times[i] * 0.7; // �߼���ʦ����30%
        } else if (min_index < T_cook + M_cook) {
            cooking_time[min_index] += times[i] * 0.8; // �м���ʦ����20%
        } else {
            cooking_time[min_index] += times[i]; // ������ʦ������ʱ��
        }
    }

    // ���������в�Ʒ���ҵ���ʦ�е�������ʱ�䣬��ʱ�伴Ϊ�ܵ����ʱ��
    int total_cooking_time = 0;
    for (int i = 0; i < T_cook + M_cook + P_cook; i++) {
        if (cooking_time[i] > total_cooking_time) {
            total_cooking_time = cooking_time[i];
        }
    }

    free(cooking_time); // �ͷ��ڴ�
    return total_cooking_time;
}
/*----���ڶ�ȡ��ǰ������ʦ������----*/
void LoadCookNumber(int * T_cook,int * M_cook, int* P_cook) {
    FILE *file;
    file = fopen("Cooks.dll","rb");
    if (file == NULL) {
        printf("����ʧ��\n");
    }
    fscanf(file, "%d,%d,%d", T_cook, M_cook, P_cook);//Ϊ���ֳ�ʦ������ֵ������Ӧ���ڲ�Ʒ����
    fclose(file);
}

void ResetCookNumber() {
    CookDetail();               //��ʾ��ǰ���ֳ�ʦ����
    FILE *file;
    file = fopen("Cooks.dll","wb");
    if (file == NULL) {
        printf("����ʧ��\n");
    }
    int T_Cook ;
    int M_Cook ;
    int P_Cook ;
    printf("�µĸ߼���ʦ������\n");
    scanf_s("%d", &T_Cook);
    printf("�µ��м���ʦ������\n");
    scanf_s("%d", &M_Cook);
    printf("�µĳ�����ʦ������\n");
    scanf_s("%d", &P_Cook);
    fprintf(file,"%d,%d,%d",T_Cook,M_Cook,P_Cook);
    fclose(file);
    printf("���óɹ���\n");
    SyncToCookscpy(T_Cook,M_Cook,P_Cook);    //ͬ��������
}
/*��ʾ��ǰ���ֳ�ʦ������*/
void CookDetail() {
    CheckCooks();                   //��鴢���ʦ�������ļ��Ƿ��𻵣�������𻵣��򽫸������ݸ�����ԭ�ļ�
    FILE *file;
    file = fopen("Cooks.dll","rb");

    if (file == NULL) {
        printf("����ʧ��\n");
    }
    char cook[100];
    fgets(cook, sizeof(cook), file);
    char *T_Cook = strtok(cook, ",");
    char *M_Cook = strtok(NULL, ",");
    char *P_Cook = strtok(NULL, ",");
    printf("��ǰ�߼���ʦ������%s\n",T_Cook);
    printf("��ǰ�м���ʦ������%s\n",M_Cook);
    printf("��ǰ������ʦ������%s\n",P_Cook);
    fclose(file);
}

/*���ڼ�鴢���ʦ�������ļ��Ƿ��𻵣��������ø������ݸ�д*/
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
        printf("�޷���Դ�ļ�\n");
        return;
    }

    if (target == NULL) {
        printf("�޷���Ŀ���ļ�\n");
        fclose(source);
        return;
    }
fclose(target);

if (T_Cook == NULL||M_Cook == NULL||P_Cook == NULL) {
    FILE *target2 = fopen("Cooks.dll","wb");

    char buffer[1024]; // ����һ��������

    // ���ж�ȡԴ�ļ���д��Ŀ���ļ�ʵ�ָ�д
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, target2);
    }

    // �ر��ļ�
    fclose(source);
    fclose(target2);
}
}