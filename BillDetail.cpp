#include <stdio.h>
#include "Functions.h"
/* 用于在“账单明细”功能中将记录的账单打印在控制台中 */
void BillDetail() {
    char list[100];
    FILE *file;
    file = fopen("Bills.dll","rb");
    if (file == NULL) {
        printf("打开账单失败\n");
    }
    while (fgets(list, sizeof(list), file) != NULL) {
        printf("%s", list);  // 打印读取的行
    }
    // 关闭文件
    fclose(file);
}
