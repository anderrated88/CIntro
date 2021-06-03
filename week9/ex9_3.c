/* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>
#include <math.h>

int sum(int n)
{
    int sum=0;
    for (int i=1;i <=n; i++)
    {
        sum +=i*i*i;
    }
    return sum;
}
void submutiple(int n)
{
    for (int i=1;i <=n/2;i++)
    {
        if (n % i ==0)
        {
            printf("%d",i);

        }
    }
    printf("d",n);
}
void perfectsquare(int n)
{
    for (int i =1; i <=n;i++)
    {
        printf("%d ", i*i);
    }
}
int main(void)
{
    int n;
    printf("Enter n\n");
    scanf("%d",&n);
    printf("The sum of the cube of integers from 1 to %d : %d\n",n,sum(n));
    printf("All submutiple of the integer %d :",n);
    submutiple(n);
    printf("\n The %d first perfect square numbers : \n",n);
    perfectsquare(n);
}
