/* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>

int main()

{
    int c=1, n, fact = 1;
    printf("Nhap n\n");
    scanf("%d", &n);
        do {
            fact = fact * c;
            c++;
        } while (c <= n);
    printf("n! = %d\n", fact);
return 0;
}
