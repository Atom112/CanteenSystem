#include <stdbool.h>
#include <stdio.h>
#include "Functions.h"
void ManagerMode () {
    while (true) {
        char mode;
        DishNode *dishes = NULL;
        printf("����ѡ��");
        printf("A-�༭�˵� B-��֧��ϸ Q-�˳�ϵͳ\n");
        scanf_s(" %c",&mode);
        if (mode == 'A'||mode == 'a') {
            ReadMenu(&dishes);
            while (true) {
                char commad;
                printf("�༭ģʽѡ��");
                printf("A-���Ӳ�Ʒ D-ɾ����Ʒ S-���Ҳ�Ʒ E-�༭��Ʒ��Ϣ Q-�˳��༭\n");
                scanf_s(" %c",&commad);
                if (commad == 'A'||commad == 'a') {
                    AddDish(&dishes);
                }else if (commad == 'D'||commad == 'd') {
                    DeleteDish(&dishes);
                }else if (commad == 'S'||commad == 's') {
                    char newname[MAX_DISH_NAME];
                    printf("������Ҫ���ҵĲ�Ʒ���ƣ�\n");
                    scanf_s(" %s",&newname);
                    SearchDish(dishes,newname);
                }else if (commad == 'E'||commad == 'e') {
                    char newname[MAX_DISH_NAME];
                    printf("������Ҫ���ĵĲ�Ʒ����\n");
                    scanf_s(" %s",&newname);
                    EditDishInfo(&dishes,newname);
                }else if (commad == 'Q'||commad == 'q') {
                    break;
                }else {
                    printf("���ܲ����ڣ�\n");
                }
            }

        }else if (mode == 'B'||mode == 'b') {

        }else if (mode == 'Q'||mode == 'q') {
            break;
        }
        else {
            printf("ģʽ�����ڣ�\n");
        }
    }
}