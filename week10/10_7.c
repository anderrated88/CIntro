#include <stdio.h>
int sort(int a[], int n)
{
    for (int i = 0; i < n / 2; i++)
        if (a[i] != a[n - i - 1])
            return 0;
    return 1;
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
    if (sort(a, n))
        printf("Ham doi xung");
    else
        printf("ham ko doi xung");
    return 0;
}