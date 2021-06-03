#include <stdio.h>


void printnchars(char ch, int n)
{
    for (int i =1; i<=n;i++)
    {
        printf("%c",ch);
    }
    printf("\n");
}

void main()
{   int n;
    char ch='*';
    printf("Enter n:");
    scanf("%d",&n);
    printnchars(ch,n);
}
