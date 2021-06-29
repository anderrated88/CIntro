#include <stdio.h>
typedef struct fractions
{
    int tu;
    int mau;
} fraction;
void input(fraction frac[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Nhap tu so va mau so cua so thu %d\n", i + 1);
        scanf("%d %d", &frac[i].tu, &frac[i].mau);
    }
}
void output(fraction frac[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Phan so thu %d la :", i + 1);
        printf("%d/%d\n", frac[i].tu, frac[i].mau);
    }
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void dao(fraction frac[], int n)
{
    for (int i = 0; i < n; i++)
    {
        swap(&frac[i].tu, &frac[i].mau);
    }
}
int main()
{
    int n;
    fraction frac[10];
    printf("Nhap n");
    scanf("%d", &n);
    input(frac, n);
    output(frac, n);
    dao(frac, n);
    output(frac, n);
    return 0;
}