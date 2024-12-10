#include <stdio.h>
#include "Functions.h"
void EditDishInfo(DishNode** head, const char* name) {
    DishNode* dishToModify = SearchDish(*head, name);

    float newprice;
    float newcost;
    int newtime;

    printf("新的菜品售价：\n");
    scanf_s(" %f",&newprice);
    printf("新的菜品成本：\n");
    scanf_s(" %f",&newcost);
    printf("新的菜品烹饪时间：\n");
    scanf_s(" %d",&newtime);
    if (dishToModify != NULL) {
        dishToModify->dish.price = newprice; // 修改价格
        dishToModify->dish.cost = newcost;
        dishToModify->dish.time = newtime;
        SyncToCSV(*head); // 修改后同步
    }
}