#include <stdio.h>
void incomeplus(int *luong, int nam)
{
    int i;
    if (nam < 4)
        printf("Luong ko doi");
    else
    {
        for (i = nam; i > 3; i--)
            *luong = *luong * 1.1;
        printf("Luong la %d", *luong);
    }
}
int main()
{
    int luong, nam;
    printf("Nhap so luong hien tai ");
    scanf("%d", &luong);
    printf("So nam da lam la: ");
    scanf("%d", &nam);
    incomeplus(&luong, nam);
    return 0;
}
