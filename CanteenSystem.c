#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"

int main() {
    printf("餐厅管理系统V1.0\n");
    while (true) {
        printf("请选择模式（M-管理模式，C-用户点餐模式，Q-退出系统）\n");
        char system_mode;
        scanf_s(" %c",&system_mode);
        if (system_mode == 'M'|| system_mode == 'm') {
            ManagerMode ();
        }else if(system_mode == 'C'|| system_mode == 'c') {
            CustomerMode ();
        }else if(system_mode == 'Q'|| system_mode == 'q') {
            break;
        }else {
            perror("模式不存在，请重新选择");
        }
    }
    return 0;
}

