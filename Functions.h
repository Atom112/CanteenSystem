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

int ReadMenu(DishNode **head);
void Order(DishNode *head, float *T_Profit, float *T_Cost, float *T_Price, int *T_Time);
void TableFeedback (TC tc,float *TotalPrice,int *TotalTime);
void TakeoutFeedback (TKC tkc,float *TotalPrice,int *TotalTime);
void AddToSum (float *S_price,float *S_profit,float *S_cost,float *T_price,float *T_profit,float *T_cost);
void CustomerMode ();
void ManagerMode ();
void AddDish(DishNode** head);
DishNode* SearchDish(DishNode* head, const char* name);
void DeleteDish(DishNode** head);
void EditDishInfo(DishNode** head, const char* name);
void SyncToCSV(DishNode* head);
void WriteDetailToBills (DishNode* current,int DishNumber) ;
void WriteDataToBills (float TotalPrice,float TotalCost,float TotalProfit);
void WriteSumToBills (float S_Price,float S_Cost,float S_Profit);
#endif //FUNCTIONS_H