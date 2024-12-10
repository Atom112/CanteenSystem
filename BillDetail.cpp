#include <stdio.h>
#include "Functions.h"
void BillDetail() {
    char list[100];
    FILE *file;
    file = fopen("Bills.txt","r");
    if (file == NULL) {
        printf("打开账单失败\n");
    }
    while (fgets(list, sizeof(list), file) != NULL) {
        printf("%s", list);  // 打印读取的行
    }
    // 关闭文件
    fclose(file);
}
