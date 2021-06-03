/* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>

int main(void)
{
  int c, lastc;

 while((c = getchar()) != EOF)
  {
      if (c=='\t')
      {
        c='\\';
        putchar(c);putchar(c);
      }
      else putchar(c);
  }
  return 0;
}
