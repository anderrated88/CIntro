/* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>

int main()

{

 int c, n, fact = 1;

 printf("Nhap n\n");

 scanf("%d", &n);

 for (c = 1; c <= n; c++)

   fact = fact * c;

 printf("n! = %d\n", fact);

 return 0;

}
