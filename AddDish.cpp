#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions.h"

/* �������еĲ˵��������ӣ������Ĳ�Ʒ���������ͷ�� */
void AddDish(DishNode** head) {

    char newname[MAX_DISH_NAME];
    float newprice;
    float newcost;
    int newtime;
    while(true) {
        printf("��������ӵĲ�Ʒ��Ϣ����Q-�˳���\n");                             //����¼���²�Ʒ�ĸ�����Ϣ
        printf("��Ʒ���ƣ�\n");
        scanf_s("%s", newname, sizeof(newname) / sizeof(newname[0]));
        if (strcmp(newname, "Q") == 0|| strcmp(newname, "q") == 0) {
            break;
        }
        printf("��Ʒ�ۼۣ�\n");
        scanf_s(" %f",&newprice);
        printf("��Ʒ�ɱ���\n");
        scanf_s(" %f",&newcost);
        printf("��Ʒ���ʱ�䣺\n");
        scanf_s(" %d",&newtime);

        DishNode* newDish = (DishNode*)malloc(sizeof(DishNode));            // �½�һ������ڵ�
        strcpy(newDish->dish.name, newname);                                    // �Ը�����Ա������ֵ
        newDish->dish.price = newprice;                                         //
        newDish->dish.cost = newcost;                                           //
        newDish->dish.time = newtime;                                           //
        newDish->next = *head;                                                  // �½ڵ���뵽�����ͷ��
        *head = newDish;                                                        // ��������ͷ�ڵ�Ϊ��ǰ�����ڵ�
        SyncToDish(*head);                                                       // ÿ������ͬ���˵����˵�����
        SyncToDishcpy(*head);
    }
}
