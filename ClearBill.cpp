#include <stdio.h>
#include "Functions.h"
void ClearBill() {
    FILE *file;

    // 以写模式打开文件，这将清空文件中的所有内容
    file = fopen("Bills.txt", "w");
    if (file == NULL) {
        // 检查文件是否成功打开
        perror("Error opening file");
        return ;
    }

    // 关闭文件
    fclose(file);
}
