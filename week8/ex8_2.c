/* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>

int main(void)
{
  int c, lastc;


  while((c = getchar()) != EOF)
  {
    if(c == ' ')
    {
      if(lastc != ' ')
        putchar(c);
    }
    else
      putchar(c);
    lastc=c;
  }
  return 0;
}
