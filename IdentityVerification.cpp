#include <stdio.h>
#include <string.h>
#include "Functions.h"

void IdentityVerification() {
    FILE *file;
    char passwd[100];
    file = fopen("passwd.txt","r");
    if (file == NULL) {
        printf("ERROR\n");
        return;
    }
    fgets(passwd, 100, file);
    fclose(file);

    while (true) {
        char input[50];
        printf("请输入密码：\n");
        scanf("%s",input);
        if (strcmp(input, passwd) != 0) {
            printf("密码错误，请重试\n");
        }else {
            break;
        }
    }
}

void ResetPassword() {
    IdentityVerification();
    FILE *file;
    while (true) {
        char temppasswd1[50];
        char temppasswd2[50];
        printf("请输入新密码：\n");
        scanf("%s",temppasswd1);
        printf("请确认新密码：\n");
        scanf("%s",temppasswd2);

        if (strcmp(temppasswd1, temppasswd2) != 0) {
            printf("两次密码不一致，请重试\n");
        }else {
            file=fopen("passwd.txt","w");
            fprintf(file, "%s", temppasswd1);
            fclose(file);
            break;
        }
    }
}


