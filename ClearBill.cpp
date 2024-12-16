#include <stdio.h>
#include "Functions.h"
/*---用于清空账单明细---*/
void ClearBill() {
    FILE *file;
    // 以写模式打开文件，这将清空文件中的所有内容
    file = fopen("Bills.dll", "wb");
    if (file == NULL) {
        // 检查文件是否成功打开
        printf("Error opening file");
        return ;
    }

    // 关闭文件
    fclose(file);
}
