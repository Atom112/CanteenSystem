#include <stdio.h>
#include <string.h>
#include "Functions.h"

bool IdentityVerification() {
    FILE *file;
    char passwd[100];
    int counter = 0;
    file = fopen("passwd.txt","r");
    if (file == NULL) {
        printf("ERROR\n");
    }
    fgets(passwd, 100, file);
    fclose(file);

    while (5-counter >0) {
        char input[50];
        printf("���������룺\n");
        scanf("%s",input);
        if (strcmp(input, passwd) != 0) {
            counter++;
            printf("������������ԣ�ʣ��%d�λ���\n",5-counter);
        }else {
            return true;
        }
    }
    printf("������������ǿ���˳�\n");
    return false;
}

void ResetPassword() {
    IdentityVerification();
    FILE *file;

    while (true) {
        char temppasswd1[50];
        char temppasswd2[50];
        printf("�����������룺\n");
        scanf("%s",temppasswd1);
        printf("��ȷ�������룺\n");
        scanf("%s",temppasswd2);

        if (strcmp(temppasswd1, temppasswd2) != 0) {

            printf("�������벻һ�£�������\n");
        }else {
            file=fopen("passwd.txt","w");
            fprintf(file, "%s", temppasswd1);
            fclose(file);
            break;
        }
    }

}


