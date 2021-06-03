 /* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>
int main()
{

float n,du,chia;

    printf("Nhap n \n");
    scanf("%f",&n );
    chia=floor(n/7);
    du=n-chia*7;
    printf("the number of students in the smallest class is %.0f\n",chia);
    if (du!=0)
    printf("the number of students in the largest class is %.0f\n",chia+1);
    else printf("the number of students in the largest class is %0.f\n",chia);
    printf("the average number of students per class is %f \n",n/7);
    printf("the number of classes of above average size is %.0f\n",du);
    printf("the number of classes of above at most average size is %.0f\n",7-du);
    if (du!=0)
    printf("the number of students in class larger than average size is %.0f\n",chia+1);
    else printf("there is no class larger than average size\n");
    if (du!=0)
    printf("the number of classes of exactly average size is 0\n");
    else printf("the number of classes of exactly average size is %0.f\n",chia);
    return 0;
}
