#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
void DeleteDish(DishNode** head) {
    DishNode* current = *head;
    DishNode* prev = NULL;
    char newname[MAX_DISH_NAME];
    while (true) {

    printf("������Ҫɾ���Ĳ�Ʒ���ƣ���Q-���أ�\n");
    scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0]));
        if (strcmp(newname, "Q") == 0|| strcmp(newname, "q") == 0) {
            break;
        }

        while (current != NULL && strcmp(current->dish.name, newname) != 0) {
            prev = current;
            current = current->next;
        }

        if (current == NULL) {
            return; // û���ҵ�Ҫɾ������Ʒ
        }

        if (prev == NULL) {
            *head = current->next; // ͷ�ڵ㱻ɾ��
        } else {
            prev->next = current->next; // ɾ���м��β���Ľڵ�
        }
        free(current);
        SyncToCSV(*head); // ÿ��ɾ��ͬ��
        SyncToCSVcpy(*head);
    }
}
