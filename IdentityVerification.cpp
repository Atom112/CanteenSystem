#include <stdio.h>
#include <string.h>
#include "Functions.h"
/* 进入管理模式时所需要的身份验证 */
bool IdentityVerification() {
    CheckPassword();

    FILE *file;
    char passwd[100];
    int counter = 0;            //记录密码输错的次数

    file = fopen("passwd.dll","rb");

    if (file == NULL) {
        printf("ERROR\n");
    }
    //读取用户名和密码
    fgets(passwd, 100, file);

    char *name = strtok(passwd, ",");
    char *password = strtok(NULL, ",");

    fclose(file);
    while(true) {
        char username[100];
        printf("请输入当前管理员名称：\n");
        scanf_s("%s",&username);
        if (strcmp(username, name) == 0) {
            break;
        }else {
            printf("管理员用户不存在，请重试\n");
        }
    }
    while (5-counter >0) {
        char input[50];
        printf("请输入密码：\n");
        scanf("%s",input);
        if (strcmp(input, password) != 0) {
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
    CheckPassword();

    FILE *file;
    while (true) {
        char newuser[50];
        char temppasswd1[50];
        char temppasswd2[50];
        printf("请输入新的管理员用户名：\n");
        scanf_s("%s",&newuser);
        printf("请输入新密码：\n");
        scanf("%s",temppasswd1);
        printf("请确认新密码：\n");
        scanf("%s",temppasswd2);

        if (strcmp(temppasswd1, temppasswd2) != 0) {

            printf("两次密码不一致，请重试\n");
        }else {
            file=fopen("passwd.dll","wb");
            fprintf(file, "%s,%s",newuser, temppasswd1);
            fclose(file);
            printf("设置成功！\n");
            SyncToPasswdcpy(newuser,temppasswd1);//同步至密码文件
            break;
        }
    }

}
/* 检查密码文件是否被损坏，若有，则用副本覆写 */
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
        printf("无法打开源文件\n");
        return;
    }

    if (target == NULL) {
        printf("无法打开目标文件\n");
        fclose(source);
        return;
    }
    fclose(target);

    if (Name == NULL||password == NULL) {
        FILE *target2 = fopen("passwd.dll","wb");

        char buffer[1024]; // 定义一个缓冲区

        // 逐行读取源文件并写入目标文件
        while (fgets(buffer, sizeof(buffer), source) != NULL) {
            fputs(buffer, target2);
        }

        // 关闭文件
        fclose(source);
        fclose(target2);
    }
}
