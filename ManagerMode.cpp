#include <stdio.h>
#include "Functions.h"
void ManagerMode () {
    while (true) {
        char mode;
        DishNode *dishes = NULL;
        printf("����ѡ��");
        printf("A-�༭�˵� B-��֧��ϸ S-���ó�ʦ�� R-���ù���Ա���Ƽ����� Q-�˳�ϵͳ\n");
        scanf_s(" %c",&mode);
        //�򵥵�ѡ����ʵ��
        if (mode == 'A'||mode == 'a') {
            ReadMenu(&dishes);  //��ִ�д�ӡ�˵�
            while (true) {
                char commad;
                printf("�༭ģʽѡ��");
                printf("A-���Ӳ�Ʒ D-ɾ����Ʒ S-���Ҳ�Ʒ E-�༭��Ʒ��Ϣ Q-�˳��༭\n");
                scanf_s(" %c",&commad);
                //�򵥵�ѡ����ʵ��
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
                    printf("���ܲ����ڣ�\n");
                }
            }

        }else if (mode == 'B'||mode == 'b') {
            BillDetail();
            char choice;
            printf("�Ƿ�����˵����ݣ���Y-�ǣ�������������-��\n");
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
            printf("ģʽ�����ڣ�\n");
        }
    }
}