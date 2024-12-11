#ifndef __PRINT_TABLE_H__
#define __PRINT_TABLE_H__

#define TABLE_BORDER_LENGTH 11

typedef void* TABLE_HANDLE;

typedef struct _TABLE_COL {
    int count;   // ����
    int *width;  // ÿ�еĿ�ȣ��ַ���
} TABLE_COL, *PTABLE_COL;

typedef enum _TABLE_MODE {
    TABLE_MODE_LEFT = 0,
    TABLE_MODE_MIDDLE,
    TABLE_MODE_RIGHT
} TABLE_MODE;

// Ĭ�ϵı߿���ʾ
static const char table_default_border[TABLE_BORDER_LENGTH] = { '*', '*', '*', '*', '+', '+', '+', '+', '-', '|', '+' };

/*
��ʼ�������Ϣ
table       ��Ҫ����ʼ���ľ��
tableCol    �����е���Ϣ
border      �߽���ʾ��Ϣ
*/
int TableInit(TABLE_HANDLE *table, PTABLE_COL tableCol, const char *border);

/*
������һ��
table       �����
mode        ���������ʾλ��  ��0������ ��1������ ��2������
format      �����ʾ���� ����ע����Ҫʹ�ÿո�ֿ�������ֻ��һ���ո�
*/
int TableAddCol(TABLE_HANDLE table, TABLE_MODE mode, char * format, ...);
void TablePrint(TABLE_HANDLE table);
void TableClean(TABLE_HANDLE table);
void TableDestroy(TABLE_HANDLE table);
int calculateLength(const char *str);
#endif // __PRINT_TABLE_H__