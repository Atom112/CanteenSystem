#ifndef __PRINT_TABLE_H__
#define __PRINT_TABLE_H__

#define TABLE_BORDER_LENGTH 11

typedef void* TABLE_HANDLE;

typedef struct _TABLE_COL {
    int count;   // 列数
    int *width;  // 每列的宽度（字符）
} TABLE_COL, *PTABLE_COL;

typedef enum _TABLE_MODE {
    TABLE_MODE_LEFT = 0,
    TABLE_MODE_MIDDLE,
    TABLE_MODE_RIGHT
} TABLE_MODE;

// 默认的边框显示
static const char table_default_border[TABLE_BORDER_LENGTH] = { '*', '*', '*', '*', '+', '+', '+', '+', '-', '|', '+' };

/*
初始化表格信息
table       需要被初始化的句柄
tableCol    表格的行的信息
border      边界显示信息
*/
int TableInit(TABLE_HANDLE *table, PTABLE_COL tableCol, const char *border);

/*
表格添加一行
table       表格句柄
mode        表格内容显示位置  【0】靠左 【1】居中 【2】靠右
format      表格显示内容 【备注】需要使用空格分开，有且只有一个空格
*/
int TableAddCol(TABLE_HANDLE table, TABLE_MODE mode, char * format, ...);
void TablePrint(TABLE_HANDLE table);
void TableClean(TABLE_HANDLE table);
void TableDestroy(TABLE_HANDLE table);

#endif // __PRINT_TABLE_H__