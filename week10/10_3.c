#include <stdio.h>
int check(int a[], int b[], int n, int m)
{
    int i;
    if (n != m)
        return 0;
    for (i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}
int nhapmang(int a[])
{
    int n;
    printf("So phan tu mang la");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("\na[%d]:", i);
        scanf("%d", &a[i]);
    }
    return n;
}

int main()
{
    int a[10], b[10];
    int n = nhapmang(a),
        m = nhapmang(b);
    if (check(a, b, n, m))
        printf("hai mang bang nhau");
    else
        printf("hai mang khong bang nhau");
    return 0;
}