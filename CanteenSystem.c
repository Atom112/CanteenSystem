#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"

int main() {
    printf("��������ϵͳV1.0\n");
    while (true) {
        printf("��ѡ��ģʽ��M-����ģʽ��C-�û����ģʽ��Q-�˳�ϵͳ��\n");
        char system_mode;
        scanf_s(" %c",&system_mode);
        if (system_mode == 'M'|| system_mode == 'm') {
            ManagerMode ();
        }else if(system_mode == 'C'|| system_mode == 'c') {
            CustomerMode ();
        }else if(system_mode == 'Q'|| system_mode == 'q') {
            break;
        }else {
            perror("ģʽ�����ڣ�������ѡ��");
        }
    }
    return 0;
}

