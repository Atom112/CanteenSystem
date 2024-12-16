#include <stdio.h>
#include "Functions.h"
void ManagerMode () {
    while (true) {
        char mode;
        DishNode *dishes = NULL;
        printf("功能选择：");
        printf("A-编辑菜单 B-收支明细 S-设置厨师数 R-重置管理员名称及密码 Q-退出系统\n");
        scanf_s(" %c",&mode);
        //简单的选择功能实现
        if (mode == 'A'||mode == 'a') {
            ReadMenu(&dishes);  //先执行打印菜单
            while (true) {
                char commad;
                printf("编辑模式选择：");
                printf("A-增加菜品 D-删除菜品 S-查找菜品 E-编辑菜品信息 Q-退出编辑\n");
                scanf_s(" %c",&commad);
                //简单的选择功能实现
                if (commad == 'A'||commad == 'a') {
                    AddDish(&dishes);
                }else if (commad == 'D'||commad == 'd') {
                    DeleteDish(&dishes);
                }else if (commad == 'S'||commad == 's') {
                    SearchDish(dishes);
                }else if (commad == 'E'||commad == 'e') {
                    EditDishInfo(&dishes);
                }else if (commad == 'Q'||commad == 'q') {
                    break;
                }else {
                    printf("功能不存在！\n");
                }
            }

        }else if (mode == 'B'||mode == 'b') {
            BillDetail();
            char choice;
            printf("是否清除账单内容？（Y-是，其余任意输入-否）\n");
            scanf_s(" %c",&choice);
            if (choice == 'Y'||choice == 'y') {
                ClearBill();
            }
        }else if(mode == 'R'|| mode == 'r') {
            ResetPassword();
        }
        else if (mode == 'S'||mode == 's') {
            ResetCookNumber();
        }else if (mode == 'Q'||mode == 'q') {
            break;
        }
        else {
            printf("模式不存在！\n");
        }
    }
}