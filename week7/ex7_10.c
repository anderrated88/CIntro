/* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>

int main(  ) {
    int i,j,n;
    printf("Nhap n\n");
    scanf("%d",&n);
        if (n<6) printf("Khong co gia tri thoa man");
        for (i=6;i<n;i++){
            int temp=0;
            for (j=1;j<i;j++){
                if (i % j == 0)
                temp=temp+j;
            }
            if (temp==i) printf("PERFECT NUMBER IS: %d \n",temp);
        }
return 0;
}
