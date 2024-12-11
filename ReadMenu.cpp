#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#include "print_table.h"
void PreReadMenu() {
    FILE *source = fopen("Dishescpy.csv", "r");
    FILE *target = fopen("Dishes.csv", "w"); // ��дģʽ��Ŀ���ļ��������ԭ�ļ�����

    if (source == NULL) {
        perror("�޷���Դ�ļ�\n");
        return;
    }

    if (target == NULL) {
        perror("�޷���Ŀ���ļ�\n");
        fclose(source);
        return;
    }

    char buffer[1024]; // ����һ��������

    // ���ж�ȡԴ�ļ���д��Ŀ���ļ�
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, target);
    }

    // �ر��ļ�
    fclose(source);
    fclose(target);
};

int ReadMenu(DishNode **head) {

while (true) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen("Dishes.csv", "r");

    if (file == NULL) {
        printf("�򿪲˵�ʧ�ܣ�����ϵ����Ա\n");

    }

    *head = NULL;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        // �����½ڵ�
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            perror("�ڴ����ʧ��");
            fclose(file);
            return false; // ����false
        }

        char *name = strtok(line, ",");
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");

        // ����ֶ��Ƿ���ȱʧ
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
        perror("�򿪲˵�ʧ�ܣ�����ϵ����Ա");
        return EXIT_FAILURE; // ���ش���״̬
    }

    *head = NULL;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        // �����½ڵ�
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            perror("�ڴ����ʧ��");
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
        newNode->dish.id = (*head == NULL) ? 1 : (*head)->dish.id + 1; // ID����
        newNode->next = *head; // �½ڵ�ָ��ǰͷ
        *head = newNode; // ����ͷ��Ϊ�½ڵ�
    }
        fclose(file);
        // ��ʾ�˵�
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
                // ����λ��
                DishNode* temp = dishArray[j];
                dishArray[j] = dishArray[j + 1];
                dishArray[j + 1] = temp;
            }
        }
    }


    TABLE_HANDLE handle; // �����
    TABLE_COL tableCol;  // ����нṹ��

    tableCol.count = 4; // ��������
    int width[] = { 16, 16, 16, 16}; // �����п�
    tableCol.width = width; // �����п�����нṹ��
    TableInit(&handle, &tableCol, table_default_border); // ��ʼ�����
    TableAddCol(handle, TABLE_MODE_MIDDLE, "��Ʒ��� ���� �۸�/Ԫ  ���ʱ��/min"); // ����б���
    for (int i = 0; i < idx; i++) {
        TableAddCol(handle, TABLE_MODE_MIDDLE, "%d %s %.1f %d", dishArray[i]->dish.id, dishArray[i]->dish.name, dishArray[i]->dish.price, dishArray[i]->dish.time); // ���������
    }
    TablePrint(handle); // ��ӡ���
    TableDestroy(handle); // �ͷű����Դ

    return 1;
}