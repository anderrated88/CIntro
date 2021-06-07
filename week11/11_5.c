#include <stdio.h>

void swap(int x, int y, int z)
{
    int temp = *x;
    *x = *y;
    *y = *z;
    *z = temp;
}
int main()
{
    int x, y, z;
    int *p, *q, *r;
    printf("Enter x,y,z:");
    scanf("%d%d%d", &x, &y, &z);
    p = &x;
    q = &y, r = &z;
    printf("The values of x y z are %d %d %d\n", x, y, z);
    printf("The value of p q r are %p %p %p\n", p, q, r);
    printf("The value of *p *q *r are %d %d %d\n", *p, *q, *r);
    int temp;
    swap(p, q, r);
    printf("The values of x y z are %d %d %d\n", x, y, z);
    printf("The value of p q r are %p %p %p\n", p, q, r);
    printf("The value of *p *q *r are %d %d %d\n", *p, *q, *r);
    temp = p;
    p = q;
    q = r;
    r = temp;
    printf("The values of x y z are %d %d %d\n", x, y, z);
    printf("The value of p q r are %p %p %p\n", p, q, r);
    printf("The value of *p *q *r are %d %d %d\n", *p, *q, *r);
}
