#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"
extern int BillID;
int mintime=0;    //��ʼ����Сʱ��
// ��ͺ��������ڴ����û��Ķ�����������¼��Ʒ�����ͼ����ܳɱ����۸������
void Order(DishNode *head, float *T_Profit, float *T_Cost, float *T_Price) {
    int TotalDish = 0;              // ��ǰ�����к��еĲ�Ʒ����
    int Choice = 0;                 // �û�ѡ��Ĳ�Ʒ���
    int DishOrderNumber = 0;        // ÿ�ֲ�Ʒ��͵ķ���
    int ListId = 0;                 // ��¼��Ʒʱ�����������
    int *DishTime= (int *)malloc(sizeof(int) * MAX_DISHES); // ���ڴ洢��Ͳ�Ʒ�����ʱ��

    // ���˵��ļ�����׷��ģʽ��
    FILE *file;
    file = fopen("Bills.dll", "a");
    if (file == NULL) {
        printf("�޷����˵��ļ���\n");
        return; // �ļ���ʧ�ܣ��˳�����
    }

    // д�뵱ǰ������ŵ��˵��ļ�
    fprintf(file, "������ţ�%d\n\n", BillID);
    fclose(file); // �ر��ļ�

    // ��ʾ�û������Ʒ��źͷ���
    printf("�������͵Ĳ�Ʒ��ż�������������������'-1'��\n");

    while (true) {
        printf("��Ʒ��ţ�");
        scanf("%d", &Choice); // ��ȡ�û�����Ĳ�Ʒ���

        // ����û��Ƿ������˽�����־
        if (Choice == -1) {
            break; // �˳�ѭ�������н���
        }

        // �ڲ�Ʒ�����в����û�ѡ��Ĳ�Ʒ
        DishNode* current = head; // ��ʼ����ǰ�ڵ�Ϊ����ͷ
        while (current != NULL) {
            if (current->dish.id == Choice) {
                break; // �ҵ���Ӧ�Ĳ�Ʒ������ѭ��
            }
            current = current->next; // �ƶ�����һ���ڵ�
        }

        // �����ǰ�ڵ�Ϊ NULL��˵��δ�ҵ��ò�Ʒ
        if (current == NULL) {
            printf("��Ʒ��Ų����ڣ�������ѡ��\n");
            continue; // ��ʾ�û���������
        }

        // ��ȡ�û�ϣ����Ĳ�Ʒ����
        printf("��Ʒ������");
        scanf("%d", &DishOrderNumber);
        // �������Ƿ������
        if (DishOrderNumber <= 0) {
            printf("��ͷ�����������㣡\n");
            continue; // ������һ��ѭ����Ҫ����������
        }

        TotalDish += DishOrderNumber; // �����ܲ�Ʒ��

        // ��¼ÿ�ݲ�Ʒ�����ʱ��
        while (ListId < TotalDish) {
            DishTime[ListId] = current->dish.time; // ����ǰ��Ʒ�����ʱ���¼��������
            ListId++;
        }

        // �����ܳɱ����ܼ۸��������
        *T_Cost += current->dish.cost * (float)DishOrderNumber; // �����ܳɱ�
        *T_Price += current->dish.price * (float)DishOrderNumber; // �����ܼ۸�
        *T_Profit += current->dish.profit * (float)DishOrderNumber; // ����������

        // д����ϸ���˵���Ϣ
        WriteDetailToBills(current, DishOrderNumber);
    }

    // ����ܲ�Ʒ����
    printf("�ܷ�����%d\n", TotalDish);

    // д���ܼ۸��ܳɱ����������˵�
    WriteDataToBills(*T_Price, *T_Cost, *T_Profit);

    // ������С���ʱ��
    mintime = calculate_min_cook_time(DishTime, TotalDish);

    // �ͷŷ�����ڴ�
    free(DishTime); // �ͷŴ洢���ʱ��������ڴ�
}
