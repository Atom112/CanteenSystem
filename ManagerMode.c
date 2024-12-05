#include <stdbool.h>
#include <stdio.h>
#include "Functions.h"
void ManagerMode () {
    while (true) {
        char mode;
        DishNode *dishes = NULL;
        printf("功能选择：");
        printf("A-编辑菜单 B-收支明细 Q-退出系统\n");
        scanf_s(" %c",&mode);
        if (mode == 'A'||mode == 'a') {
            ReadMenu(&dishes);
            while (true) {
                char commad;
                printf("编辑模式选择：");
                printf("A-增加菜品 D-删除菜品 S-查找菜品 E-编辑菜品信息 Q-退出编辑");
                scanf_s(" %c",&commad);
                if (commad == 'A'||commad == 'a') {
                    AddDish();
                }else if (commad == 'D'||commad == 'd') {
                    DeleteDish();
                }else if (commad == 'S'||commad == 's') {
                    SearchDish();
                }else if (commad == 'E'||commad == 'e') {
                    EditDishInfo();
                }else if (commad == 'Q'||commad == 'q') {
                    break;
                }else {
                    printf("功能不存在！\n");
                }
            }

        }else if (mode == 'B'||mode == 'b') {

        }else if (mode == 'Q'||mode == 'q') {
            break;
        }
        else {
            printf("模式不存在！\n");
        }
    }
}