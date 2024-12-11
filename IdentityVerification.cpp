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
        printf("请输入密码：\n");
        scanf("%s",input);
        if (strcmp(input, passwd) != 0) {
            counter++;
            printf("密码错误，请重试，剩余%d次机会\n",5-counter);
        }else {
            return true;
        }
    }
    printf("多次输入错误，已强制退出\n");
    return false;
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


