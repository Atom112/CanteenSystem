#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"
int ReadMenu(int *MenuDishNumber ,Dish dishes[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen("Dishes.csv", "r");

    if (file == NULL) {
        perror("�򿪲˵�ʧ�ܣ�����ϵ����Ա");
        return EXIT_FAILURE; // ���ش���״̬
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(dishes[*MenuDishNumber].name, strtok(line, ","));
        char *price_str = strtok(NULL, ",");
        char *cost_str = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");
        dishes[*MenuDishNumber].price = atof(price_str);
        dishes[*MenuDishNumber].cost = atof(cost_str);
        dishes[*MenuDishNumber].time = atoi(time_str);
        dishes[*MenuDishNumber].profit = dishes[*MenuDishNumber].price - dishes[*MenuDishNumber].cost;
        dishes[*MenuDishNumber].id = *MenuDishNumber+1;
        (*MenuDishNumber)++;
    }

    fclose(file);

    for (int i = 0; i < *MenuDishNumber; i++) {
        printf("��Ʒ��ţ�%d\n",dishes[i].id);
        printf("����: %s\n", dishes[i].name);
        printf("�۸�: %.1f Ԫ\n", dishes[i].price);
        printf("ʱ��: %d min\n", dishes[i].time);
        printf("\n");
    }
    return *MenuDishNumber;
}
