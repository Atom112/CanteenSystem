#include <stdio.h>
#include "Functions.h"
int BillID = 0;
float sum_price = 0;          //ȫ�����������۶�
float sum_profit = 0;         //ȫ������������
float sum_cost = 0;           //ȫ�������ܳɱ�
float TotalCost = 0;          //���ζ������ܳɱ�
float TotalPrice = 0;         //���ζ����������۶�
float TotalProfit = 0;        //���ζ�����������

int main() {
    printf("��������ϵͳV1.0\n");
    /*-----��ѭ�������ڱ���ϵͳ��������-----*/
    while (true) {
        printf("��ѡ��ģʽ��M-����ģʽ��C-�û����ģʽ��Q-�˳�ϵͳ��\n");
        char system_mode;
        scanf_s(" %c",&system_mode);
        //�򵥵Ĺ���ѡ��
        if (system_mode == 'M'|| system_mode == 'm') {
            bool is = IdentityVerification();           //�ڽ������Աģʽǰ��Ҫ���������֤
            if (is) {
                ManagerMode ();
            }
        }else if(system_mode == 'C'|| system_mode == 'c') {
            CustomerMode ();
        }else if(system_mode == 'Q'|| system_mode == 'q') {
            break;
        }else {
            printf("ģʽ�����ڣ�������ѡ��\n");
        }
    }
    return 0;
}