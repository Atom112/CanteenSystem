#include <stdio.h>
#include "Functions.h"

// ����Ʒ����ͬ����ָ�����ļ�"Dishes.dll"
void SyncToDish(DishNode* head) {
    // ���ļ�"Dishes.dll"����д�����������
    FILE* file = fopen("Dishes.dll", "wb");
    if (file == NULL) {
        printf("���ļ�ʧ��"); // ����ļ���ʧ�ܣ����������Ϣ
        return; // ���أ���������
    }

    DishNode* current = head; // ��ʼ����ǰ�ڵ�Ϊ����ͷ
    while (current != NULL) { // ��������
        // ����ǰ��Ʒ����Ϣд���ļ����Զ��ŷָ�
        fprintf(file, "%s,%f,%f,%d\n", current->dish.name, current->dish.price, current->dish.cost, current->dish.time);
        current = current->next; // �ƶ�����һ����Ʒ
    }

    fclose(file); // �ر��ļ�
}

// ����Ʒ����ͬ������һ�������ļ�"Dishescpy.dll"
void SyncToDishcpy(DishNode* head) {
    // ���ļ�"Dishescpy.dll"����д�����������
    FILE* file = fopen("Dishescpy.dll", "wb");
    if (file == NULL) {
        printf("���ļ�ʧ��"); // ����ļ���ʧ�ܣ����������Ϣ
        return; // ���أ���������
    }

    DishNode* current = head; // ��ʼ����ǰ�ڵ�Ϊ����ͷ
    while (current != NULL) { // ��������
        // ����ǰ��Ʒ����Ϣд���ļ����Զ��ŷָ�
        fprintf(file, "%s,%f,%f,%d\n", current->dish.name, current->dish.price, current->dish.cost, current->dish.time);
        current = current->next; // �ƶ�����һ����Ʒ
    }

    fclose(file); // �ر��ļ�
}

// ����ʦ��Ϣͬ�����ļ�"Cookscpy.dll"
// ������t - ��ʦ��ʱ�䣻m - ��ʦ��ĳ�����ԣ�p - ��ʦ����һ������
void SyncToCookscpy(int t, int m, int p) {
    // ���ļ�"Cookscpy.dll"����д�����������
    FILE* file = fopen("Cookscpy.dll", "wb");
    if (file == NULL) {
        printf("���ļ�ʧ��"); // ����ļ���ʧ�ܣ����������Ϣ
        return; // ���أ���������
    }
    // ����ʦ����Ϣд���ļ����Զ��ŷָ�
    fprintf(file, "%d,%d,%d", t, m, p);

    fclose(file); // �ر��ļ�
}

// ���û���������ͬ�����ļ�"passwdcpy.dll"
// ������n - �û�����p - ����
void SyncToPasswdcpy(char n[], char p[]) {
    // ���ļ�"passwdcpy.dll"����д�����������
    FILE* file = fopen("passwdcpy.dll", "wb");
    if (file == NULL) {
        printf("���ļ�ʧ��"); // ����ļ���ʧ�ܣ����������Ϣ
        return; // ���أ���������
    }
    // ���û���������д���ļ����Զ��ŷָ�
    fprintf(file, "%s,%s", n, p);

    fclose(file); // �ر��ļ�
}
