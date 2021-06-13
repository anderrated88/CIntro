#include <stdio.h>

int localmax(int a[], int n)
{
    int sum = 0;
    for (int i = 1; i < n - 1; i++)
        if (a[i] > a[i - 1] && a[i] > a[i + 1])
            sum += a[i];
    return sum;
}
int main()
{
    int a[10];
    int n;
    printf("n =");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("\na[%d]:", i);
        scanf("%d", &a[i]);
    }
    printf("Ket qua la %d", localmax(a, n));
    return 0;
}