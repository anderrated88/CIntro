#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
void input(Student Studentlist[], int *n);
void writeBin(Student Studentlist[], int n);
void readBin(Student Studentlist[], int *n);
void output(Student Studentlist[], int n);
void search(Student Studentlist[], int n, char name[]);
int main()
{
    Student Studentlist[50];
    int n;
    int select;
    do
    {
        printf("Quan ly sinh vien :\n-----------------\n");
        printf("1: Xem danh sach sinh vien\n2: Nhap them sinh vien\n3: Tim sinh vien theo ten\n4: Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &select);
        fflush(stdin);
        switch (select)
        {
        case 1:
        {
            printf("1: Xem danh sach sinh vien\n");
            readBin(Studentlist, &n);
            output(Studentlist, n);
            break;
        }
        case 2:
        {
            printf("2: Nhap them sinh vien\n");
            input(Studentlist, &n);
            writeBin(Studentlist, n);
            printf("Luu thanh cong!\n");
            break;
        }
        case 3:
        {
            printf("Tim sinh vien theo ten\n");
            printf("Nhap ten can tim\n");
            char name[20];
            fflush(stdin);
            gets(name);
            search(Studentlist, n, name);
            break;
        }

        case 4:
            return 0;
        default:
            printf("Nhap sai!\n");
            break;
        }
    } while (select != 4);
    return 0;
}

void input(Student Studentlist[], int *n)
{
    int i;
    char s[50];
    printf("Nhap so sinh vien :  ");
    scanf("%d", n);
    gets(s);
    printf("\n");
    for (i = 0; i < (*n); i++)
    {
        printf("Nhap ten sinh vien thu %d : ", i + 1);
        gets(Studentlist[i].name);
        printf("Nhap diem cua sinh vien thu %d : ", i + 1);
        scanf("%d", &Studentlist[i].diem);
        gets(s);
    }
}
void writeBin(Student Studentlist[], int n)
{
    FILE *f = fopen("SV2021.dat", "ab");
    int i;
    if (f == NULL)
        printf("Error load file");
    else
        fwrite(Studentlist, sizeof(Student), n, f);
    fclose(f);
}
void readBin(Student Studentlist[], int *n)
{
    FILE *f = fopen("SV2021.dat", "rb");
    fseek(f, 0, SEEK_END);
    (*n) = (ftell(f) + 1) / sizeof(Student);
    fseek(f, 0, SEEK_SET);
    fread(Studentlist, sizeof(Student), (*n), f);
    fclose(f);
}
void output(Student Studentlist[], int n)
{
    int i;
    printf("%-10s %-20s %-15s \n", "STT", "Ten", "Diem");
    for (i = 0; i < n; i++)
        printf("%-10d %-20s %-15d \n", i + 1, Studentlist[i].name, Studentlist[i].diem);
}
void search(Student Studentlist[], int n, char name[])
{
    int i, check = 0;
    for (i = 0; i < n; i++)
    {
        if (strcmp(name, Studentlist[i].name) == 0)
        {
            check = 1;
            printf("%-10s %-20s %-15s \n", "STT", "Ten", "Diem");
            printf("%-10d %-20s %-15d \n", i + 1, Studentlist[i].name, Studentlist[i].diem);
            FILE *f = fopen("output.txt", "w");
            if (f == NULL)
                printf("Error load file");
            fprintf(f, "%-10s %-20s %-15s \n", "STT", "Ten", "Diem");
            fprintf(f, "%-10d %-20s %-15d \n", i + 1, Studentlist[i].name, Studentlist[i].diem);
            fclose(f);
            printf("Luu ra file thanh cong\n");
        }
        if (check == 0 && i == n - 1)
            printf("Khong co ai ten %s !\n", name);
    }
}
