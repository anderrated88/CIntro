#include <stdio.h>
#include <string.h>

int main(){
    int i;
    char s[100],a,b;
    printf("\nNhap chuoi: ");
    fgets(s, sizeof s, stdin);
    scanf("%c%c",&a,&b);
    for(i=0;i<strlen(s) - 1;i++){
        if(s[i]==a) s[i]=b;
    }
    puts(s);
}
