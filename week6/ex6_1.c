 /* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>

int main () {
   char string[10];
   char temp;
   int i, j;
   printf("Enter your string \n");
    scanf("%s",string);
    int size = strlen(string);
   for (i = 0; i < size-1; i++) {
      for (j = i+1; j < size; j++) {
         if (string[i] < string[j])
            temp = string[i];
            else temp = string[j];}}
   printf("%c\n",temp);
   return 0;
}
