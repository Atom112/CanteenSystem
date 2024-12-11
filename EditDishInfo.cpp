#include <stdio.h>
#include "Functions.h"
void EditDishInfo(DishNode** head) {
    while(true){
        DishNode* dishToModify = SearchDish(*head);
        if (dishToModify == NULL) {
            break;
        }

        float newprice;
        float newcost;
        int newtime;

        printf("�µĲ�Ʒ�ۼۣ�\n");
        scanf_s(" %f",&newprice);
        printf("�µĲ�Ʒ�ɱ���\n");
        scanf_s(" %f",&newcost);
        printf("�µĲ�Ʒ���ʱ�䣺\n");
        scanf_s(" %d",&newtime);
        dishToModify->dish.price = newprice; // �޸ļ۸�
        dishToModify->dish.cost = newcost;
        dishToModify->dish.time = newtime;
        SyncToCSV(*head); // �޸ĺ�ͬ��
        SyncToCSVcpy(*head);
        printf("�޸���ɣ�\n");
    }
}