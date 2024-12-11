#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "print_table.h"

// ������Ľṹ
typedef struct _TABLE{
    char border[11];
    char *printStr;
    int strLen;
    int useLen;
    PTABLE_COL col;
} TABLE, *PTABLE;

// ��ʼ�����
int TableInit(TABLE_HANDLE *table, PTABLE_COL tableCol, const char *border){
    PTABLE pTable = (PTABLE)malloc(sizeof(TABLE) + sizeof(TABLE_COL) + sizeof(int) * tableCol->count);
    *table = pTable;

    pTable->useLen = 0;
    pTable->strLen = 10240;
    pTable->printStr = (char *)malloc(pTable->strLen);
    memset(pTable->printStr, 0, 10240);

    pTable->col = (PTABLE_COL)(pTable + 1);
    pTable->col->width = (int *)((char *)pTable + sizeof(TABLE) + sizeof(TABLE_COL));
    pTable->col->count = tableCol->count;
    for (int i = 0; i < pTable->col->count; i++){
        pTable->col->width[i] = tableCol->width[i];
    }

    memcpy(pTable->border, border, TABLE_BORDER_LENGTH);

    return 0;
}
// �����ַ�������
int calculateLength(const char *str) {
    int length = 0;
    while (*str) {
        if ((*str & 0x80) == 0) {
            // ASCII�ַ�
            length += 1;
        } else {
            // �����ַ�������ΪUTF-8���룬����ͨ��ռ��3���ֽڣ�
            length += 2;
            str += 2; // ���������ַ����������ֽ�
        }
        str++;
    }
    return length;
}

// ��ʽ���ַ���
int FormatStr(char *str, int len){
    //int strLen = strlen(str);
    int strLen = calculateLength(str);
    if (strLen < len){
        return len - strLen;
    }
    str[len] = 0;
    if (len == 2){
        str[len - 1] = '.';
    }
    else if (len == 3){
        str[len - 1] = '.';
        str[len - 2] = '.';
    }
    else if (len > 3){
        str[len - 1] = '.';
        str[len - 2] = '.';
        str[len - 3] = '.';
    }
    return 0;
}

// ��ӱ߿򵽱��
void AddFrame(PTABLE pTable, int mode){
    int isFirstCol = 0;
    if (pTable->useLen == 0){
        isFirstCol = 1;
    }

    if (isFirstCol){
        sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[0]);
    }
    else{
        if (mode){
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[3]);
        }
        else{
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[5]);
        }
    }
    pTable->useLen++;
    for (int i = 0; i < pTable->col->count; i++){
        for (int j = 0; j < pTable->col->width[i]; j++){
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[8]);
            pTable->useLen++;
        }
        if (i == pTable->col->count - 1){
            if (isFirstCol){
                sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[1]);
            }
            else{
                if (mode){
                    sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[3]);
                }
                else{
                    sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[6]);
                }
            }
            pTable->useLen++;
        }
        else{
            if (isFirstCol){
                sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[4]);
            }
            else{
                if (mode){
                    sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[7]);
                }
                else{
                    sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[10]);
                }
            }
        }
        pTable->useLen++;
    }
    pTable->printStr[pTable->useLen] = 0;
}

// ���������
int AddItem(PTABLE pTable, char *str, int len, int index, TABLE_MODE mode){
    int start = 0;
    int end = 0;
    int retLen = 0;
    sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[9]);
    pTable->useLen++;

    if (len){
        if (mode == TABLE_MODE_LEFT){
            end = len;
        }
        else if (mode == TABLE_MODE_MIDDLE){
            start = len / 2;
            end = len - start;
        }
        else if (mode == TABLE_MODE_RIGHT){
            start = len;
        }
    }

    for (int i = 0; i < start; i++){
        sprintf(pTable->printStr + pTable->useLen, " ");
        pTable->useLen++;
    }
    retLen = sprintf(pTable->printStr + pTable->useLen, "%s", str);
    pTable->useLen += retLen;
    for (int i = 0; i < end; i++){
        sprintf(pTable->printStr + pTable->useLen, " ");
        pTable->useLen++;
    }
    if (pTable->col->count == index + 1){
        sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[9]);
        pTable->useLen += 2;
    }
    return 0;
}

#define ARG_BUFF_SIZE 2048
// ���������
int TableAddCol(TABLE_HANDLE table, TABLE_MODE mode, char *format, ...){
    va_list args;
    int ret = 0;
    char buff[ARG_BUFF_SIZE] = {0};
    char *tmp = buff;
    PTABLE pTable = (PTABLE)table;
    int count = pTable->col->count;
    char *pStart = NULL;
    char *pTmp = NULL;
    char *pNext = NULL;

    va_start(args, format);
    int buffSize = ARG_BUFF_SIZE;
    ret = vsnprintf(tmp, buffSize - 1, format, args);
    if (ret > buffSize){
        tmp = (char *)malloc(ret + 1);
        if (tmp == NULL){
            return -1;
        }
    }
    vsprintf(tmp, format, args);
    pStart = tmp;

    AddFrame(pTable, 0);
    for (int i = 0; i < count; i++){
        pTmp = strstr(pStart, " ");
        if (pTmp){
            *pTmp = 0;
            pTmp++;
            ret = FormatStr(pStart, pTable->col->width[i]);
            AddItem(pTable, pStart, ret, i, mode);
            pStart = pTmp;
        }
        else{
            ret = FormatStr(pStart, pTable->col->width[i]);
            AddItem(pTable, pStart, ret, i, mode);
            break;
        }
    }
    return 0;
}

// ��ӡ�������
void TablePrint(TABLE_HANDLE table){
    PTABLE pTable = (PTABLE)table;
    AddFrame(pTable, 1);
    printf("%s\n", pTable->printStr);
}

// ��ձ������
void TableClean(TABLE_HANDLE table){
    PTABLE pTable = (PTABLE)table;
    memset(pTable->printStr, 0, pTable->strLen);
    pTable->useLen = 0;
}

// ���ٱ���ͷ��ڴ�
void TableDestroy(TABLE_HANDLE table){
    PTABLE pTable = (PTABLE)table;
    free(pTable->printStr);
    free(pTable);
}