#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct SinhVien
{
    float diem;
    char name[20];
    char classment[1];
} SV;
void swap(SV *a, SV *b)
{
    SV temp = *a;
    *a = *b;
    *b = temp;
}
void SapXep(SV svien[], int n)
{
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++)
            if (svien[i].diem < svien[j].diem)
                swap(&svien[i], &svien[j]);
}

int main()
{
    int i, n;
    char s[50];
    SV svien[10];
    printf("Nhap so sinh vien :  ");
    scanf("%d", &n);
    gets(s);
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("Nhap ten sinh vien thu %d : ", i + 1);
        gets(svien[i].name);
        printf("Nhap diem cua sinh vien thu %d : ", i + 1);
        scanf("%f", &svien[i].diem);
        printf("Nhap classment sinh vien thu %d : ", i + 1);
        gets(svien[i].classment);
        gets(s);
    }
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++)
            if (svien[i].diem < svien[j].diem)
            {
                SV temp = svien[i];
                svien[i] = svien[j];
                svien[j] = temp;
            }
    printf("%-10s %-10s %-10s \n", "Name", "Grade", "Classment");
    for (i = 0; i < n; i++)
        printf("%-10s %-10.2f %-10s \n", svien[i].name, svien[i].diem, svien[i].classment);
    return 0;
}