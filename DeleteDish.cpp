#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
// ɾ��ָ����Ʒ�ĺ���
void DeleteDish(DishNode** head) {
    // ָ��ǰ�ڵ��ָ�룬��ʼ��Ϊ����ͷ�ڵ�
    DishNode* current = *head;
    // ָ��ǰһ���ڵ��ָ�룬��ʼ��Ϊ NULL
    DishNode* prev = NULL;
    // �洢�û�����Ĳ�Ʒ����
    char newname[MAX_DISH_NAME];

    while (true) {

        printf("������Ҫɾ���Ĳ�Ʒ���ƣ���Q-���أ�\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0]));

        // ����û��Ƿ��������˳�ָ��
        if (strcmp(newname, "Q") == 0 || strcmp(newname, "q") == 0) {
            break;
        }

        // ������������ƥ��Ĳ�Ʒ����
        while (current != NULL && strcmp(current->dish.name, newname) != 0) {
            prev = current;  // ����ǰһ���ڵ�Ϊ��ǰ�ڵ�
            current = current->next; // �ƶ�����һ���ڵ�
        }

        // �����������ĩβ��δ�ҵ�ƥ��Ĳ�Ʒ���˳�����
        if (current == NULL) {
            printf("δ�ҵ���Ʒ\n");
            continue; // û���ҵ�Ҫɾ������Ʒ
        }

        // ���Ҫɾ������ͷ�ڵ�
        if (prev == NULL) {
            *head = current->next; // ��ͷ�ڵ�ָ��ָ����һ���ڵ�
        } else {
            // ɾ���м��β���Ľڵ�
            prev->next = current->next; // ��ǰһ���ڵ�ָ��ǰ�ڵ����һ���ڵ�
        }

        // �ͷŵ�ǰ�ڵ���ڴ�
        free(current);
        // ÿ��ɾ����ͬ���� Dish��Dishcpy �ļ�
        SyncToDish(*head);
        SyncToDishcpy(*head);
    }
}
