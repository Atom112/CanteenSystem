#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "print_table.h"

// 定义表格的结构
typedef struct _TABLE{
    char border[11];
    char *printStr;
    int strLen;
    int useLen;
    PTABLE_COL col;
} TABLE, *PTABLE;

// 初始化表格
// 初始化表格
// 参数：table - 表格句柄(指向表格的指针)
//        tableCol - 表格列的描述信息
//        border - 表格的边框字符
int TableInit(TABLE_HANDLE *table, PTABLE_COL tableCol, const char *border) {
    // 为表格分配内存
    PTABLE pTable = (PTABLE)malloc(sizeof(TABLE) + sizeof(TABLE_COL) + sizeof(int) * tableCol->count);
    *table = pTable; // 将新表格的指针赋值给调用者

    // 初始化表格的参数
    pTable->useLen = 0; // 表示当前使用的长度
    pTable->strLen = 10240; // 分配的字符串长度
    pTable->printStr = (char *)malloc(pTable->strLen); // 为打印字符串分配内存
    memset(pTable->printStr, 0, 10240); // 清空字符串

    // 初始化列信息
    pTable->col = (PTABLE_COL)(pTable + 1); // 将列信息放置在表格之后
    pTable->col->width = (int *)((char *)pTable + sizeof(TABLE) + sizeof(TABLE_COL)); // 列宽存放在表格内存之后
    pTable->col->count = tableCol->count; // 设置列的数量

    // 复制列宽信息
    for (int i = 0; i < pTable->col->count; i++) {
        pTable->col->width[i] = tableCol->width[i];
    }

    // 复制边框字符信息
    memcpy(pTable->border, border, TABLE_BORDER_LENGTH);

    return 0; // 初始化成功
}

// 计算字符串长度
// 参数：str - 输入字符串
// 返回值：字符串的有效长度，按字符（假设中文字符为2个宽度）
int calculateLength(const char *str) {
    int length = 0; // 初始化长度
    while (*str) {
        // 检查字符类型（ASCII或中文）
        if ((*str & 0x80) == 0) {
            // ASCII字符
            length += 1; // 每个ASCII字符计为1
        } else {
            // 假设为UTF-8编码的中文字符
            length += 2; // 中文字符计为2
            str += 2; // 跳过中文字符的下两个字节
        }
        str++; // 移动到下一个字符
    }
    return length; // 返回计算得到的长度
}

// 格式化字符串，使其适应指定长度
// 参数：str - 待格式化字符串
//        len - 目标长度
// 返回值：剩余空间，如果字符串长度小于指定长度
int FormatStr(char *str, int len) {
    int strLen = calculateLength(str); // 计算字符串长度
    if (strLen < len) {
        return len - strLen; // 返回剩余可用空间
    }
    str[len] = 0; // 确保字符串的结束
    // 处理超出字符串长度的情况，插入省略号“.”
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
    return 0; // 返回格式化成功
}

// 向表格添加边框
// 参数：pTable - 指向表格的指针
//        mode - 边框模式（用于判断边框的样式）
void AddFrame(PTABLE pTable, int mode) {
    int isFirstCol = 0; // 用于检查是否为第一列
    if (pTable->useLen == 0) {
        isFirstCol = 1; // 表示第一列
    }

    // 根据是否为第一列选择边框字符
    if (isFirstCol) {
        sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[0]);
    } else {
        if (mode) {
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[3]);
        } else {
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[5]);
        }
    }
    pTable->useLen++; // 更新使用长度

    // 添加各列的宽度边框填充
    for (int i = 0; i < pTable->col->count; i++) {
        for (int j = 0; j < pTable->col->width[i]; j++) {
            sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[8]);
            pTable->useLen++; // 更新使用长度
        }
        // 处理行结束
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
            pTable->useLen++; // 更新使用长度
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
        pTable->useLen++; // 更新使用长度
    }

    // 确保字符串结束
    pTable->printStr[pTable->useLen] = 0;
}

// 向表格中添加一项数据
// 参数：pTable - 表格指针
//        str - 要添加的字符串
//        len - 字符串长度
//        index - 表格中的列索引
//        mode - 字符串对齐模式（左中右对齐）
int AddItem(PTABLE pTable, char *str, int len, int index, TABLE_MODE mode) {
    int start = 0; // 起始位置
    int end = 0; // 结束位置
    int retLen = 0; // 返回的长度

    // 添加边框字符
    sprintf(pTable->printStr + pTable->useLen, "%c", pTable->border[9]);
    pTable->useLen++; // 更新使用长度

    // 根据对齐模式设置起始和结束位置
    if (len) {
        // 左对齐
        if (mode == TABLE_MODE_LEFT) {
            end = len;
        }
        // 中间对齐
        else if (mode == TABLE_MODE_MIDDLE) {
            start = len / 2;
            end = len - start;
        }
        // 右对齐
        else if (mode == TABLE_MODE_RIGHT) {
            start = len;
        }
    }

    // 添加空格前缀
    for (int i = 0; i < start; i++) {
        sprintf(pTable->printStr + pTable->useLen, " ");
        pTable->useLen++; // 更新使用长度
    }

    // 添加字符串内容
    retLen = sprintf(pTable->printStr + pTable->useLen, "%s", str);
    pTable->useLen += retLen; // 更新使用长度

    // 添加空格后缀
    for (int i = 0; i < end; i++) {
        sprintf(pTable->printStr + pTable->useLen, " ");
        pTable->useLen++; // 更新使用长度
    }

    // 检查是否为最后一列
    if (pTable->col->count == index + 1) {
        sprintf(pTable->printStr + pTable->useLen, "%c\n", pTable->border[9]);
        pTable->useLen += 2; // 更新使用长度
    }
    return 0; // 添加成功
}

#define ARG_BUFF_SIZE 2048 // 定义缓冲区大小

// 向表格添加列
// 参数：table - 表格句柄
//        mode - 对齐模式
//        format - 格式化字符串
// 返回值：0表示成功，-1表示失败
int TableAddCol(TABLE_HANDLE table, TABLE_MODE mode, char *format, ...) {
    va_list args; // 可变参数列表
    int ret = 0; // 返回值
    char buff[ARG_BUFF_SIZE] = {0}; // 初始化缓冲区
    char *tmp = buff; // 临时指针
    PTABLE pTable = (PTABLE)table; // 获取表格指针
    int count = pTable->col->count; // 获取列数
    char *pStart = NULL; // 开始指针
    char *pTmp = NULL; // 临时指针
    char *pNext = NULL; // 下一个指针

    va_start(args, format); // 初始化可变参数
    int buffSize = ARG_BUFF_SIZE; // 缓冲区大小
    ret = vsnprintf(tmp, buffSize - 1, format, args); // 格式化字符串
    if (ret > buffSize) {
        // 如果缓冲区不够大，则重新分配内存
        tmp = (char *)malloc(ret + 1);
        if (tmp == NULL) {
            return -1; // 内存分配失败
        }
    }
    vsprintf(tmp, format, args); // 再次格式化字符串
    pStart = tmp; // 初始化开始指针

    AddFrame(pTable, 0); // 添加表格边框
    for (int i = 0; i < count; i++) {
        pTmp = strstr(pStart, " "); // 查找第一个空格
        if (pTmp) {
            *pTmp = 0; // 替换空格为字符串结尾
            pTmp++; // 移动指针
            ret = FormatStr(pStart, pTable->col->width[i]); // 格式化字符串
            AddItem(pTable, pStart, ret, i, mode); // 添加项至表格
            pStart = pTmp; // 更新开始指针
        } else {
            ret = FormatStr(pStart, pTable->col->width[i]); // 格式化字符串
            AddItem(pTable, pStart, ret, i, mode); // 添加项
            break; // 无空格情况，结束循环
        }
    }
    return 0; // 添加列成功
}

// 打印表格内容
// 参数：table - 表格句柄
void TablePrint(TABLE_HANDLE table) {
    PTABLE pTable = (PTABLE)table; // 获取表格指针
    AddFrame(pTable, 1); // 添加结束的边框
    printf("%s\n", pTable->printStr); // 打印表格字符串
}

// 清空表格内容
// 参数：table - 表格句柄
void TableClean(TABLE_HANDLE table) {
    PTABLE pTable = (PTABLE)table; // 获取表格指针
    memset(pTable->printStr, 0, pTable->strLen); // 清空打印字符串
    pTable->useLen = 0; // 重置使用长度
}

// 销毁表格并释放内存
// 参数：table - 表格句柄
void TableDestroy(TABLE_HANDLE table) {
    PTABLE pTable = (PTABLE)table; // 获取表格指针
    free(pTable->printStr); // 释放打印字符串
    free(pTable); // 释放表格本身的内存
}
