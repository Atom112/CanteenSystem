#include <stdio.h>
#include "Functions.h"
/*---��������˵���ϸ---*/
void ClearBill() {
    FILE *file;
    // ��дģʽ���ļ����⽫����ļ��е���������
    file = fopen("Bills.dll", "wb");
    if (file == NULL) {
        // ����ļ��Ƿ�ɹ���
        printf("Error opening file");
        return ;
    }

    // �ر��ļ�
    fclose(file);
}
