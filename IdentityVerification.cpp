#include <stdio.h>
#include <string.h>
#include "Functions.h"
/* �������ģʽʱ����Ҫ�������֤ */
bool IdentityVerification() {
    CheckPassword();

    FILE *file;
    char passwd[100];
    int counter = 0;            //��¼�������Ĵ���

    file = fopen("passwd.dll","rb");

    if (file == NULL) {
        printf("ERROR\n");
    }
    //��ȡ�û���������
    fgets(passwd, 100, file);

    char *name = strtok(passwd, ",");
    char *password = strtok(NULL, ",");

    fclose(file);
    while(true) {
        char username[100];
        printf("�����뵱ǰ����Ա���ƣ�\n");
        scanf_s("%s",&username);
        if (strcmp(username, name) == 0) {
            break;
        }else {
            printf("����Ա�û������ڣ�������\n");
        }
    }
    while (5-counter >0) {
        char input[50];
        printf("���������룺\n");
        scanf("%s",input);
        if (strcmp(input, password) != 0) {
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
    CheckPassword();

    FILE *file;
    while (true) {
        char newuser[50];
        char temppasswd1[50];
        char temppasswd2[50];
        printf("�������µĹ���Ա�û�����\n");
        scanf_s("%s",&newuser);
        printf("�����������룺\n");
        scanf("%s",temppasswd1);
        printf("��ȷ�������룺\n");
        scanf("%s",temppasswd2);

        if (strcmp(temppasswd1, temppasswd2) != 0) {

            printf("�������벻һ�£�������\n");
        }else {
            file=fopen("passwd.dll","wb");
            fprintf(file, "%s,%s",newuser, temppasswd1);
            fclose(file);
            printf("���óɹ���\n");
            SyncToPasswdcpy(newuser,temppasswd1);//ͬ���������ļ�
            break;
        }
    }

}
/* ��������ļ��Ƿ��𻵣����У����ø�����д */
void CheckPassword() {
    FILE *source;
    FILE *target;
    source = fopen("passwdcpy.dll","rb");
    target = fopen("passwd.dll","rb");

    char cook[100];
    fgets(cook, sizeof(cook), target);
    char *Name = strtok(cook, ",");
    char *password = strtok(NULL, ",");


    if (source == NULL) {
        printf("�޷���Դ�ļ�\n");
        return;
    }

    if (target == NULL) {
        printf("�޷���Ŀ���ļ�\n");
        fclose(source);
        return;
    }
    fclose(target);

    if (Name == NULL||password == NULL) {
        FILE *target2 = fopen("passwd.dll","wb");

        char buffer[1024]; // ����һ��������

        // ���ж�ȡԴ�ļ���д��Ŀ���ļ�
        while (fgets(buffer, sizeof(buffer), source) != NULL) {
            fputs(buffer, target2);
        }

        // �ر��ļ�
        fclose(source);
        fclose(target2);
    }
}
