#include <stdio.h>
#include "Functions.h"
/* �����ڡ��˵���ϸ�������н���¼���˵���ӡ�ڿ���̨�� */
void BillDetail() {
    char list[100];
    FILE *file;
    file = fopen("Bills.dll","rb");
    if (file == NULL) {
        printf("���˵�ʧ��\n");
    }
    while (fgets(list, sizeof(list), file) != NULL) {
        printf("%s", list);  // ��ӡ��ȡ����
    }
    // �ر��ļ�
    fclose(file);
}
