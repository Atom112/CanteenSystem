#include <stdio.h>
#include <string.h>

#include "Functions.h"
DishNode* SearchDish(DishNode* head, const char* name) {
    DishNode* current = head;
    while (current != NULL) {
        if (strcmp(current->dish.name, name) == 0) {
            printf("��Ʒ���ƣ�%s\n", current->dish.name);
            printf("��Ʒ�ۼ�%.1fԪ\n", current->dish.price);
            printf("��Ʒ�ɱ�%.1fԪ\n", current->dish.cost);
            printf("���ʱ��%d min\n", current->dish.time);
            return current; // �ҵ���Ӧ�Ĳ�Ʒ
        }
        current = current->next;
    }
    return NULL; // û���ҵ�
}
