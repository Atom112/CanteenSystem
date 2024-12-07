#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
int ReadMenu(DishNode **head) {
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

    // ��ӡ��Ŵ�С����Ĳ�Ʒ��Ϣ
    // for (int i = 0; i < idx; i++) {
    //     printf("��Ʒ��ţ�%d\n", dishArray[i]->dish.id);
    //     printf("����: %s\n", dishArray[i]->dish.name);
    //     printf("�۸�: %.1f Ԫ\n", dishArray[i]->dish.price);
    //     printf("���ʱ��: %d min\n", dishArray[i]->dish.time);
    //     printf("\n");
    // }

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