#include <stdio.h>
#include "Functions.h"
int BillID = 0;
float sum_price = 0;          //ȫ�����������۶�
float sum_profit = 0;         //ȫ������������
float sum_cost = 0;           //ȫ�������ܳɱ�
float TotalCost = 0;
float TotalPrice = 0;
float TotalProfit = 0;
int main() {
    printf("��������ϵͳV1.0\n");
    while (true) {
        printf("��ѡ��ģʽ��M-����ģʽ��C-�û����ģʽ��R-�޸Ĺ���Ա���룬Q-�˳�ϵͳ��\n");
        char system_mode;
        scanf_s(" %c",&system_mode);
        if (system_mode == 'M'|| system_mode == 'm') {
            IdentityVerification();
            ManagerMode ();
        }else if(system_mode == 'C'|| system_mode == 'c') {
            CustomerMode ();
        }else if(system_mode == 'R'|| system_mode == 'r') {
            ResetPassword();
        }else if(system_mode == 'Q'|| system_mode == 'q') {
            break;
        }else {
            printf("ģʽ�����ڣ�������ѡ��\n");
        }
    }
    return 0;
}