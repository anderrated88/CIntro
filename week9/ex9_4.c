/* Nguyen Dinh Thanh An – 122105 */
#include <stdio.h>
#include <math.h>
double totalsalary(int ot, int t)
{
    if (t>40)
    {
        ot=t-40;
    }
    return ot*22500+ t*15000;
}
int main()
{
    double s=0;
    int t=0;
    int ot=0;
    printf("enter t\n");
    scanf("%d",&t);
    s = totalsalary(ot,t);
    printf("total salary = %.0lf",s);
    return 0;
}
