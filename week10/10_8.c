#include <stdio.h>
void sort(int a[], int n)
{
    int tmp;
    for (int i = 0; i < n / 2; i++)
    {
        tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = tmp;
    }
}
int main()
{
    int a[10], n;
    printf("So phan tu mang la");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("\na[%d]:", i);
        scanf("%d", &a[i]);
    }
    sort(a, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    return n;
}