#include <stdio.h>
#include <stdbool.h>
#include "Functions.h"
float sum_price = 0;          //ȫ�����������۶�
float sum_profit = 0;         //ȫ������������
float sum_cost = 0;           //ȫ�������ܳɱ�
float TotalCost = 0;
float TotalPrice = 0;
float TotalProfit = 0;
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
            //printf("%f %f %f",sum_cost,sum_price,sum_profit );
        }else if(system_mode == 'Q'|| system_mode == 'q') {
            break;
        }else {
            perror("ģʽ�����ڣ�������ѡ��");
        }
    }
    return 0;
}