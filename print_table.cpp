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
// ��ʼ�����
// ������table - �����(ָ�����ָ��)
//        tableCol - ����е�������Ϣ
//        border - ���ı߿��ַ�
int TableInit(TABLE_HANDLE *table, PTABLE_COL tableCol, const char *border) {
    // Ϊ�������ڴ�
    PTABLE pTable = (PTABLE)malloc(sizeof(TABLE) + sizeof(TABLE_COL) + sizeof(int) * tableCol->count);
    *table = pTable; // ���±���ָ�븳ֵ��������

    // ��ʼ�����Ĳ���
    pTable->useLen = 0; // ��ʾ��ǰʹ�õĳ���
    pTable->strLen = 10240; // ������ַ�������
    pTable->printStr = (char *)malloc(pTable->strLen); // Ϊ��ӡ�ַ��������ڴ�
    memset(pTable->printStr, 0, 10240); // ����ַ���

    // ��ʼ������Ϣ
    pTable->col = (PTABLE_COL)(pTable + 1); // ������Ϣ�����ڱ��֮��
    pTable->col->width = (int *)((char *)pTable + sizeof(TABLE) + sizeof(TABLE_COL)); // �п����ڱ���ڴ�֮��
    pTable->col->count = tableCol->count; // �����е�����

    // �����п���Ϣ
    for (int i = 0; i < pTable->col->count; i++) {
        pTable->col->width[i] = tableCol->width[i];
    }

    // ���Ʊ߿��ַ���Ϣ
    memcpy(pTable->border, border, TABLE_BORDER_LENGTH);

    return 0; // ��ʼ���ɹ�
}

// �����ַ�������
// ������str - �����ַ���
// ����ֵ���ַ�������Ч���ȣ����ַ������������ַ�Ϊ2����ȣ�
int calculateLength(const char *str) {
    int length = 0; // ��ʼ������
    while (*str) {
        // ����ַ����ͣ�ASCII�����ģ�
        if ((*str & 0x80) == 0) {
            // ASCII�ַ�
            length += 1; // ÿ��ASCII�ַ���Ϊ1
        } else {
            // ����ΪUTF-8����������ַ�
            length += 2; // �����ַ���Ϊ2
            str += 2; // ���������ַ����������ֽ�
        }
        str++; // �ƶ�����һ���ַ�
    }
    return length; // ���ؼ���õ��ĳ���
}

// ��ʽ���ַ�����ʹ����Ӧָ������
// ������str - ����ʽ���ַ���
//        len - Ŀ�곤��
// ����ֵ��ʣ��ռ䣬����ַ�������С��ָ������
int FormatStr(char *str, int len) {
    int strLen = calculateLength(str); // �����ַ�������
    if (strLen < len) {
        return len - strLen; // ����ʣ����ÿռ�
    }
    str[len] = 0; // ȷ���ַ����Ľ���
    // �������ַ������ȵ����������ʡ�Ժš�.��
    if (len == 2) {
        str[len - 1] = '.';
    } else if (len == 3) {
        str[len - 1] = '.';
        str[len - 2] = '.';
    } else if (len > 3) {
        str[len - 1] = '.';
        str[len - 2] = '.';
        str[len - 3] = '.';
    }
    return 0; // ���ظ�ʽ���ɹ�
}

// ������ӱ߿�
// ������pTable - ָ�����ָ��
//        mode - �߿�ģʽ�������жϱ߿����ʽ��
void AddFrame(PTABLE pTable, int mode) {
    int isFirstCol = 0; // ���ڼ���Ƿ�Ϊ��һ��
    if (pTable->useLen == 0) {
        isFirstCol = 1; // ��ʾ��һ��
    }

    // �����Ƿ�Ϊ��һ��ѡ��߿��ַ�
    if (isFirstCol) {
        sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[0]);
    } else {
        if (mode) {
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[3]);
        } else {
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[5]);
        }
    }
    pTable->useLen++; // ����ʹ�ó���

    // ��Ӹ��еĿ�ȱ߿����
    for (int i = 0; i < pTable->col->count; i++) {
        for (int j = 0; j < pTable->col->width[i]; j++) {
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[8]);
            pTable->useLen++; // ����ʹ�ó���
        }
        // �����н���
        if (i == pTable->col->count - 1) {
            if (isFirstCol) {
                sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[1]);
            } else {
                if (mode) {
                    sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[3]);
                } else {
                    sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[6]);
                }
            }
            pTable->useLen++; // ����ʹ�ó���
        } else {
            if (isFirstCol) {
                sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[4]);
            } else {
                if (mode) {
                    sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[7]);
                } else {
                    sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[10]);
                }
            }
        }
        pTable->useLen++; // ����ʹ�ó���
    }

    // ȷ���ַ�������
    pTable->printStr[pTable->useLen] = 0;
}

// ���������һ������
// ������pTable - ���ָ��
//        str - Ҫ��ӵ��ַ���
//        len - �ַ�������
//        index - ����е�������
//        mode - �ַ�������ģʽ�������Ҷ��룩
int AddItem(PTABLE pTable, char *str, int len, int index, TABLE_MODE mode) {
    int start = 0; // ��ʼλ��
    int end = 0; // ����λ��
    int retLen = 0; // ���صĳ���

    // ��ӱ߿��ַ�
    sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[9]);
    pTable->useLen++; // ����ʹ�ó���

    // ���ݶ���ģʽ������ʼ�ͽ���λ��
    if (len) {
        // �����
        if (mode == TABLE_MODE_LEFT) {
            end = len;
        }
        // �м����
        else if (mode == TABLE_MODE_MIDDLE) {
            start = len / 2;
            end = len - start;
        }
        // �Ҷ���
        else if (mode == TABLE_MODE_RIGHT) {
            start = len;
        }
    }

    // ��ӿո�ǰ׺
    for (int i = 0; i < start; i++) {
        sprintf(pTable->printStr + pTable->useLen, " ");
        pTable->useLen++; // ����ʹ�ó���
    }

    // ����ַ�������
    retLen = sprintf(pTable->printStr + pTable->useLen, "%s", str);
    pTable->useLen += retLen; // ����ʹ�ó���

    // ��ӿո��׺
    for (int i = 0; i < end; i++) {
        sprintf(pTable->printStr + pTable->useLen, " ");
        pTable->useLen++; // ����ʹ�ó���
    }

    // ����Ƿ�Ϊ���һ��
    if (pTable->col->count == index + 1) {
        sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[9]);
        pTable->useLen += 2; // ����ʹ�ó���
    }
    return 0; // ��ӳɹ�
}

#define ARG_BUFF_SIZE 2048 // ���建������С

// ���������
// ������table - �����
//        mode - ����ģʽ
//        format - ��ʽ���ַ���
// ����ֵ��0��ʾ�ɹ���-1��ʾʧ��
int TableAddCol(TABLE_HANDLE table, TABLE_MODE mode, char *format, ...) {
    va_list args; // �ɱ�����б�
    int ret = 0; // ����ֵ
    char buff[ARG_BUFF_SIZE] = {0}; // ��ʼ��������
    char *tmp = buff; // ��ʱָ��
    PTABLE pTable = (PTABLE)table; // ��ȡ���ָ��
    int count = pTable->col->count; // ��ȡ����
    char *pStart = NULL; // ��ʼָ��
    char *pTmp = NULL; // ��ʱָ��
    char *pNext = NULL; // ��һ��ָ��

    va_start(args, format); // ��ʼ���ɱ����
    int buffSize = ARG_BUFF_SIZE; // ��������С
    ret = vsnprintf(tmp, buffSize - 1, format, args); // ��ʽ���ַ���
    if (ret > buffSize) {
        // ��������������������·����ڴ�
        tmp = (char *)malloc(ret + 1);
        if (tmp == NULL) {
            return -1; // �ڴ����ʧ��
        }
    }
    vsprintf(tmp, format, args); // �ٴθ�ʽ���ַ���
    pStart = tmp; // ��ʼ����ʼָ��

    AddFrame(pTable, 0); // ��ӱ��߿�
    for (int i = 0; i < count; i++) {
        pTmp = strstr(pStart, " "); // ���ҵ�һ���ո�
        if (pTmp) {
            *pTmp = 0; // �滻�ո�Ϊ�ַ�����β
            pTmp++; // �ƶ�ָ��
            ret = FormatStr(pStart, pTable->col->width[i]); // ��ʽ���ַ���
            AddItem(pTable, pStart, ret, i, mode); // ����������
            pStart = pTmp; // ���¿�ʼָ��
        } else {
            ret = FormatStr(pStart, pTable->col->width[i]); // ��ʽ���ַ���
            AddItem(pTable, pStart, ret, i, mode); // �����
            break; // �޿ո����������ѭ��
        }
    }
    return 0; // ����гɹ�
}

// ��ӡ�������
// ������table - �����
void TablePrint(TABLE_HANDLE table) {
    PTABLE pTable = (PTABLE)table; // ��ȡ���ָ��
    AddFrame(pTable, 1); // ��ӽ����ı߿�
    printf("%s\n", pTable->printStr); // ��ӡ����ַ���
}

// ��ձ������
// ������table - �����
void TableClean(TABLE_HANDLE table) {
    PTABLE pTable = (PTABLE)table; // ��ȡ���ָ��
    memset(pTable->printStr, 0, pTable->strLen); // ��մ�ӡ�ַ���
    pTable->useLen = 0; // ����ʹ�ó���
}

// ���ٱ���ͷ��ڴ�
// ������table - �����
void TableDestroy(TABLE_HANDLE table) {
    PTABLE pTable = (PTABLE)table; // ��ȡ���ָ��
    free(pTable->printStr); // �ͷŴ�ӡ�ַ���
    free(pTable); // �ͷű������ڴ�
}
