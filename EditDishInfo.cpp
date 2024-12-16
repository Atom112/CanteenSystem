#include <stdio.h>
#include "Functions.h"
/*--用来修改某菜品的信息---*/
void EditDishInfo(DishNode** head) {
    while(true){
        DishNode* dishToModify = SearchDish(*head);
        if (dishToModify == NULL) {
            break;
        }

        float newprice;
        float newcost;
        int newtime;

        printf("新的菜品售价：\n");
        scanf_s(" %f",&newprice);
        printf("新的菜品成本：\n");
        scanf_s(" %f",&newcost);
        printf("新的菜品烹饪时间：\n");
        scanf_s(" %d",&newtime);
        dishToModify->dish.price = newprice; // 修改菜品的各项内容
        dishToModify->dish.cost = newcost;
        dishToModify->dish.time = newtime;
        SyncToDish(*head);                  // 修改后同步
        SyncToDishcpy(*head);
        printf("修改完成！\n");
    }
}