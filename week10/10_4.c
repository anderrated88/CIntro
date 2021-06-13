#include <stdio.h>
void sort(int a[], int n)
{
    int tmp;
    for (int i = 0; i < n - 1; i++)

        for (int j = i + 1; j < n; j++)

            if (a[i] < a[j])
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
}
void sortodd(int a[], int n)
{
    int tmp;
    for (int i = 0; i < n - 1; i++)

        for (int j = i + 1; j < n; j++)

            if (a[i] < a[j] && a[i] % 2 && a[j] % 2)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
}
int main()
{
    int a[5], i;
    for (i = 0; i < 5; i++)
    {
        printf("\na[%d]: ", i);
        scanf("%d", &a[i]);
    }
    sort(a, 5);
    for (i = 0; i < 5; i++)
        printf("%3d", a[i]);
    sortodd(a, 5);
    printf("\n");
    for (i = 0; i < 5; i++)
        printf("%3d", a[i]);
    return 0;
}
