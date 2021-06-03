 /* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>
#include <math.h>
int main(){
    int i,j;
    for (i=2;i<=100;i++){
        int  count=0;
        for(int j = 2; j <=sqrt(i); j++){
            if(i % j == 0){
                count++;
            }
        }
    if(count == 0){
        printf("%d\n",i);
    }
    }
}
