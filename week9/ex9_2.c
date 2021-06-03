/* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>

int is_prime(int n)
    {   if (n<2) return 0;
            for(int j =2; j <= sqrt(n); j++){
                if(n % j == 0) return 0;}
            return 1;
    }
        int main(){
            int i,n;
            printf("Nhap n\n");
            scanf("%d",&n);
            for (i=2;i<=n;i++){
                if (is_prime(i)==1){
                printf("Prime number is: %d\n",i);}
            }

        }
