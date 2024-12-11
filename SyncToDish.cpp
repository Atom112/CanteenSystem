#include <stdio.h>
#include "Functions.h"

void SyncToCSV(DishNode* head) {
    FILE* file = fopen("Dishes.csv", "w");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    DishNode* current = head;
    while (current != NULL) {
        fprintf(file, "%s,%f,%f,%d\n", current->dish.name, current->dish.price,current->dish.cost,current->dish.time);
        current = current->next;
    }

    fclose(file);
}

void SyncToCSVcpy(DishNode* head) {
    FILE* file = fopen("Dishescpy.csv", "w");
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }

    DishNode* current = head;
    while (current != NULL) {
        fprintf(file, "%s,%f,%f,%d\n", current->dish.name, current->dish.price,current->dish.cost,current->dish.time);
        current = current->next;
    }

    fclose(file);
}