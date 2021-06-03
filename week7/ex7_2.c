 /* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>
int main()
{
    int i,n,j;
    printf("Nhap do cao\n");
    scanf("%d",&n);
for (i=0;i<n;i++){
    for (j=1;j<=i+1;j++){
    printf("*");
    }
printf("\n");
}
}
