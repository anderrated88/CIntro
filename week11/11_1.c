#include <stdio.h>

int main()
{
    int a, b, c;
    int *ptr;
    printf("Nhap a b c\n");
    scanf("%d %d %d", &a, &b, &c);
    ptr = &a;
    printf("Gia tri pointer la %d\n", *ptr);
    ptr = &b;
    printf("Gia tri pointer la %d\n", *ptr);
    ptr = &c;
    printf("Gia tri pointer la %d", *ptr);
    return 0;
}
