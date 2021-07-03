#include <stdio.h>
#include <string.h>

int main(){
    char s[1000];
    int i;
    printf("Nhap chuoi: ");
    fgets(s, sizeof s, stdin);
    for(i=0;i<strlen(s);i++){
        if(s[i]==','||s[i]=='.'||s[i]==';'||s[i]==':'||s[i]=='!'||s[i]=='?') s[i]=' ';
    }
    puts(s);
}

