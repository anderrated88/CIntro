/* Nguyen Dinh Thanh An – 122105 */
#include<stdio.h>
float kineticEnergy(float M, float V)
{

    float KineticEnergy;

    KineticEnergy = 0.5 * M * V * V;

    return KineticEnergy;
}
int main(void)
{
float v,m;
printf("Nhap m va v\n");
scanf("%f%f",&m,&v);
printf("Answer is %f",kineticEnergy(m,v));
return 0;
}
