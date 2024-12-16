#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_DISH_NAME 50
#define MAX_LINE_LENGTH 100
#define MAX_DISHES 100
/*------用户，菜品，链表结构体定义，便于各个函数使用------*/
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
    Dish dish;
    struct DishNode* next;
} DishNode;

/*-----所有函数的声明------*/
int ReadMenu(DishNode **head);
void Order(DishNode *head, float *T_Profit, float *T_Cost, float *T_Price);
void TableFeedback (TC tc,float *TotalPrice);
void TakeoutFeedback (TKC tkc,float *TotalPrice);
void AddToSum (float *S_price,float *S_profit,float *S_cost,float *T_price,float *T_profit,float *T_cost);
void CustomerMode ();
void ManagerMode ();
void AddDish(DishNode** head);
void SyncToDishcpy(DishNode* head);
void PreReadMenu(DishNode **head);
DishNode* SearchDish(DishNode *head);
void DeleteDish(DishNode** head);
void EditDishInfo(DishNode** head);
void SyncToDish(DishNode* head);
void WriteDetailToBills (DishNode* current,int DishNumber) ;
void WriteDataToBills (float TotalPrice,float TotalCost,float TotalProfit);
void WriteSumToBills (float S_Price,float S_Cost,float S_Profit);
void BillDetail();
void ClearBill();
bool IdentityVerification();
void ResetPassword();
void TimeTransform(int* plushour,int* plusminute,int time);
int compare(const void* a, const void* b);
int calculate_min_cook_time(int* times, int num_dishes);
void LoadCookNumber(int * T_cook,int * M_cook, int* P_cook);
void ResetCookNumber();
void CookDetail();
void CheckCooks();
void SyncToCookscpy(int t,int m,int p);
void SyncToPasswdcpy(char n[],char p[]);
void CheckPassword();
#endif //FUNCTIONS_H