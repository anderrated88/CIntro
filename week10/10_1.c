#include <stdio.h>
int main()
{
    int ary[100];
    int sum = 0, min, n, i;
    printf("Nhap n\n");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nary[%d]=", i);
        scanf("%d", &ary[i]);
        if (ary[i] % 2 != 0)
            sum = sum + ary[i];
        min = ary[0];
        if (ary[i] < min)
            min = ary[i];
    }
    printf("Tong cac so le la %d", sum);
    printf("\nMin la %d", min);
    return 0;
}