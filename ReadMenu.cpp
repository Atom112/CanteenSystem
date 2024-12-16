#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#include "print_table.h"
/*���˵��Ƿ��𻵣����У����ø�������*/
// ���˵��ļ��Ƿ��𻵣��������𻵣����ø�������
void PreReadMenu(DishNode **head) {
    FILE *file;
    char line[MAX_LINE_LENGTH]; // �洢���ļ��ж�ȡ��ÿһ��
    file = fopen("Dishes.dll", "rb"); // �Զ�����ģʽ�򿪲˵��ļ�

    if (file == NULL) {
        printf("�򿪲˵�ʧ�ܣ�����ϵ����Ա\n");
    }

    *head = NULL; // ��ʼ������ͷΪ��

    // ���ж�ȡ�˵��ļ�
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // ȥ����ĩ�Ļ��з�

        // �����½ڵ�
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            printf("�ڴ����ʧ��");
            fclose(file); // �ر��ļ�
            return; // ���أ���������
        }

        // ����������
        char *name = strtok(line, ",");
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");

        // �½ڵ�ָ��ǰͷ������ͷ��Ϊ�½ڵ�
        newNode->next = *head;
        *head = newNode;

        // ����ֶ��Ƿ���ȱʧ
        // ���ȱʧ�ֶΣ����ø����ļ����ǵ�ǰ�ļ�
        if (name == NULL || price_str == NULL || cost_str == NULL || time_str == NULL) {
            fclose(file); // �رյ�ǰ�ļ�

            // ��Դ�ļ���Ŀ���ļ�
            FILE *source = fopen("Dishescpy.dll", "rb");
            FILE *target = fopen("Dishes.dll", "wb"); // ��дģʽ��Ŀ���ļ������ԭ�ļ�����

            if (source == NULL) {
                printf("�޷���Դ�ļ�\n");
                return; // ����
            }

            if (target == NULL) {
                printf("�޷���Ŀ���ļ�\n");
                fclose(source); // �ر�Դ�ļ�
                return; // ����
            }

            char buffer[1024]; // ���建����

            // ���ж�ȡԴ�ļ���д��Ŀ���ļ���ʵ�ָ���
            while (fgets(buffer, sizeof(buffer), source) != NULL) {
                fputs(buffer, target); // д��Ŀ���ļ�
            }

            // �ر��ļ�
            fclose(source);
            fclose(target);
            break; // �˳�ѭ��
        }
    }
    free(*head); // �ͷ������ڴ�
}

// ���ļ���ȡ�˵����ݲ���������
int ReadMenu(DishNode **head) {
    PreReadMenu(head); // ���˵�����Ҫʱ�ø�������

    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen("Dishes.dll", "rb"); // �Զ�����ģʽ�򿪲˵��ļ�

    if (file == NULL) {
        printf("�򿪲˵�ʧ�ܣ�����ϵ����Ա");
        return EXIT_FAILURE; // ���ش���״̬
    }

    *head = NULL; // ��ʼ������ͷΪ��

    // ���ж�ȡ�˵��ļ�
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // ȥ����ĩ�Ļ��з�

        // �����½ڵ�
        DishNode* newNode = (DishNode*)malloc(sizeof(DishNode));

        if (newNode == NULL) {
            printf("�ڴ����ʧ��");
            fclose(file); // �ر��ļ�
            return EXIT_FAILURE; // ���ش���״̬
        }

        // ���������ݲ���䵽�½ڵ�
        strcpy(newNode->dish.name, strtok(line, ",")); // ����
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");
        newNode->dish.price = atof(price_str); // ���۸��ַ���תΪ������
        newNode->dish.cost = atof(cost_str); // ���ɱ��ַ���תΪ������
        newNode->dish.time = atoi(time_str); // ��ʱ���ַ���תΪ����
        newNode->dish.profit = newNode->dish.price - newNode->dish.cost; // ��������
        newNode->dish.id = (*head == NULL) ? 1 : (*head)->dish.id + 1; // ID�������������Ϊ����IDΪ1
        newNode->next = *head; // �½ڵ�ָ��ǰͷ
        *head = newNode; // ����ͷ��Ϊ�½ڵ�
    }

    fclose(file); // �ر��ļ�

    // ��ʾ�˵�
    DishNode* dishArray[MAX_DISHES]; // �������ڱ�������ڵ�
    int idx = 0; // ��ǰ����
    DishNode* current = *head; // ��ǰ����ڵ�

    // ����������ת�浽������
    while (current != NULL && idx < MAX_DISHES) {
        dishArray[idx++] = current;
        current = current->next; // �ƶ�����һ���ڵ�
    }

    // ������������򣨰�ID����
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

    // ��ʼ�������ñ��
    TABLE_HANDLE handle; // �����
    TABLE_COL tableCol;  // ����нṹ��

    tableCol.count = 4; // ��������
    int width[] = { 16, 16, 16, 16}; // �����п�
    tableCol.width = width; // �����п�����нṹ

    TableInit(&handle, &tableCol, table_default_border); // ��ʼ�����

    // ����б���
    //TableAddCol(handle, TABLE_MODE_MIDDLE, "��Ʒ��� ���� �۸�/Ԫ  ���ʱ��/min");
    printf("|     ��Ʒ���     |   ����   |     �۸�/Ԫ     |   ���ʱ��/min   |\n");
    // ���������
    for (int i = 0; i < idx; i++) {
        TableAddCol(handle, TABLE_MODE_MIDDLE, "%d %s %.1f %d",
                    dishArray[i]->dish.id,
                    dishArray[i]->dish.name,
                    dishArray[i]->dish.price,
                    dishArray[i]->dish.time); // ���������
    }

    TablePrint(handle); // ��ӡ���
    TableDestroy(handle); // �ͷű����Դ

    return 1; // ���سɹ�
}


