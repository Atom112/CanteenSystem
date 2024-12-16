#include <stdio.h>
#include <string.h>
#include "Functions.h"
// ������������ָ�����ƵĲ�Ʒ
DishNode* SearchDish(DishNode *head) {
    DishNode* current = head; // ��ʼ����ǰ�ڵ�Ϊ����ͷ
    char newname[MAX_DISH_NAME]; // �洢�û�����Ĳ�Ʒ����

    while(true) { // ����ѭ����ֱ���û�ѡ���˳�
        printf("������Ҫ���ҵĲ�Ʒ���ƣ���Q-���أ�\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0])); // ��ȡ�û�����Ĳ�Ʒ����

        // ����û��Ƿ��������˳�ָ��
        if (strcmp(newname, "Q") == 0 || strcmp(newname, "q") == 0) {
            break; // �û�ѡ���˳����˳�ѭ��
        }

        // ���������е����в�Ʒ
        while (current != NULL) {
            // ��鵱ǰ��Ʒ�������Ƿ�����û����������
            if (strstr(current->dish.name, newname) != NULL) {
                // �ҵ�ƥ��Ĳ�Ʒ����ӡ�����Ϣ
                printf("��Ʒ���ƣ�%s\n", current->dish.name);
                printf("��Ʒ�ۼۣ�%.1fԪ\n", current->dish.price);
                printf("��Ʒ�ɱ���%.1fԪ\n", current->dish.cost);
                printf("���ʱ�䣺%d min\n", current->dish.time);
                return current; // �����ҵ��Ĳ�Ʒ�ڵ�
            }
            current = current->next; // �ƶ�����һ����Ʒ
        }

        printf("δ�ҵ���Ʒ\n"); // ���ѭ��������δ�ҵ�����ʾ�û�δ�ҵ��κβ�Ʒ
    }

    return NULL; // ����NULL����ʾδ�ҵ��κ�ƥ��Ĳ�Ʒ��Ϣ
}
