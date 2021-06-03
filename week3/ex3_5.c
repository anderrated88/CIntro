/* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>

int main()
{
int b,c,d;

    printf("Nhap so luot overnight \n");
    scanf("%d",&b );
    printf("Nhap so luot three-day \n");
    scanf("%d",&c );
    printf("Nhap so luot weekly \n");
    scanf("%d",&d );
    printf("So luot overnight la %d\n",b);
    printf("So luot three-day la %d\n",c);
    printf("So luot weekly la %d\n",d);
    printf("Tong gia tien la %d\n",7*b+5*b+3*c);

    return 0;
}
