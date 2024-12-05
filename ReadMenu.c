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
        DishNode* current = *head;
        while (current != NULL) {
            printf("��Ʒ��ţ�%d\n", current->dish.id);
            printf("����: %s\n", current->dish.name);
            printf("�۸�: %.1f Ԫ\n", current->dish.price);
            printf("���ʱ��: %d min\n", current->dish.time);
            printf("\n");
            current = current->next;

    }
    return 1;
}