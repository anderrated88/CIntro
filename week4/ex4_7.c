/* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>
int main()
{
int q;
float p;
char t[20];

    printf("Enter quantity\n");
    scanf("%d",&q);
    printf("Enter title\n");
    scanf("%s",t);
    printf("Enter price\n");
    scanf("%f",&p);
    printf("BK Bookseller\n\n");
    printf("Qty   Title          Price\n");
    printf("%d   %s          %f",q,t,p);
    printf("\nVAT 4%%");
    printf("\nYou pay: %f",p*q*0.96);
return 0;
}
