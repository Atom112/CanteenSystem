#include <stdio.h>
#include <string.h>
#include "Functions.h"
DishNode* SearchDish(DishNode *head) {
    DishNode* current = head;
    char newname[MAX_DISH_NAME];
    while(true) {
        printf("������Ҫ���ҵĲ�Ʒ���ƣ���Q-���أ�\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0]));
        if (strcmp(newname, "Q") == 0|| strcmp(newname, "q") == 0) {
            break;
        }
        while (current != NULL) {
            if (strstr(current->dish.name, newname) != NULL) {
                printf("��Ʒ���ƣ�%s\n", current->dish.name);
                printf("��Ʒ�ۼۣ�%.1fԪ\n", current->dish.price);
                printf("��Ʒ�ɱ���%.1fԪ\n", current->dish.cost);
                printf("���ʱ�䣺%d min\n", current->dish.time);
                return current;
                // �ҵ���Ӧ�Ĳ�Ʒ
            }
            current = current->next;
        }
        printf("δ�ҵ���Ʒ\n"); // û���ҵ�
    }return NULL;
}
