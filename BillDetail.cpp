#include <stdio.h>
#include "Functions.h"
void BillDetail() {
    char list[100];
    FILE *file;
    file = fopen("Bills.txt","r");
    if (file == NULL) {
        printf("���˵�ʧ��\n");
    }
    while (fgets(list, sizeof(list), file) != NULL) {
        printf("%s", list);  // ��ӡ��ȡ����
    }
    // �ر��ļ�
    fclose(file);
}
