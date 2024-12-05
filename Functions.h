//
// Created by 1 on 24-12-5.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_DISH_NAME 50
#define MAX_LINE_LENGTH 100
#define MAX_DISHES 100

typedef struct TableCustomer {
    int TableID;
    char name[30];
}TC;

typedef struct TakeoutCustomer {
    char address[100];
    char name[30];
}TKC;

typedef struct {
    int id;
    int number;
    int time;
    float price;
    float cost;
    float profit;
    char name[MAX_DISH_NAME];
}Dish;

typedef struct DishNode {
    Dish dish;                  // 菜品信息
    struct DishNode* next;      // 指向下一个节点的指针
} DishNode;


int ReadMenu(int *MenuDishNumber,Dish dishes[]);
void Order(int MDN,Dish dishes[],float *T_Profit,float *T_Cost,float *T_Price,int *T_Time);
void TableFeedback (TC tc,float *TotalPrice,int *TotalTime);
void TakeoutFeedback (TKC tkc,float *TotalPrice,int *TotalTime);
void AddToSum (float *S_price,float *S_profit,float *S_cost,float *T_price,float *T_profit,float *T_cost);
void CustomerMode ();
void ManagerMode ();
void ManagerMode ();
#endif //FUNCTIONS_H
