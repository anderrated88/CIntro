#include <stdio.h>

float add(float a)
{
  float *ptr;
  ptr = &a;
  *ptr += 100;
  return *ptr;
}
int main()
{
  float a, b, c;
  printf("Nhap a b c\n");
  scanf("%f %f %f", &a, &b, &c);
  printf("%.3f\n", add(a));
  printf("%.3f\n", add(b));
  printf("%.3f", add(c));
  return 0;
}
