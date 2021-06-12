#include <stdio.h>

int main()
{
    int a[7] = {3, -355, 235, 47, 67, 943, 1222};
    int i;
    int *ptr;
    ptr = a;
    for (i = 0; i < 5; i++)
        printf("%p\n", ptr[i]);
    return 0;
}