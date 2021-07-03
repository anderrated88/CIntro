#include <stdio.h>
#include <string.h>

int main(){
    char s[100];
    printf("Nhap chuoi: ");
    fgets(s, sizeof s, stdin);
    printf("length = %d", strlen(s) - 1);
}
