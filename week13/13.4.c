#include <stdio.h>
int main()
{
    char name[30],s[30];
    int i=0,chot;
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    while(i<strlen(name)){
        if(name[i]==' '){
           chot=i;
           break;
        }
        else i++;
    }
    for(i=0;i<chot;i++){
        s[i]=name[i];
    }
    printf("First Name: ");
    puts(s);
}
