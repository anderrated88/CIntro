 /* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>
int main()
{
int a,b,c;
printf("Nhap a\n");
scanf("%d",&a);
printf("Nhap b\n");
scanf("%d",&b);
printf("Nhap c\n");
scanf("%d",&c);
if (a<b && a<c)
printf("a is the smallest");
if (b<a && b<c)
printf("b is the smallest");
if (c<b && c<a)
printf("c is the smallest");
if (a==b && b==c)
printf("no smallest");
return 0;
}
