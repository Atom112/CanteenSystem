#include <stdio.h>
#include "Functions.h"
void ClearBill() {
    FILE *file;

    // ��дģʽ���ļ����⽫����ļ��е���������
    file = fopen("Bills.txt", "w");
    if (file == NULL) {
        // ����ļ��Ƿ�ɹ���
        perror("Error opening file");
        return ;
    }

    // �ر��ļ�
    fclose(file);
}
