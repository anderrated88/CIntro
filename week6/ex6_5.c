 rand() /* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>
#include <stdlib.h>

int main () {
   int i,n;
   time_t t;
   srand((unsigned) time(&t));
    i= rand() % 50;
    printf("Enter your guess");
    scanf("%d",&n);
    if (n=i)
    printf("Your guess is correct!");
        else
        if (n<i)
        printf("Your guess is too low.")
        else
        printf("Your guess is too high.")
        printf("The correct answer is %d",i);
   return(0);
}
