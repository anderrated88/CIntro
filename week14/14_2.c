#include <stdio.h>
typedef struct Weathers
{
    int totalR;
    int highT;
    int lowT;
    int aveT;
} weather;
int main()
{
    int TongMua;
    weather Year[12];
    for (int i = 0; i < 12; i++)
    {
        printf("Nhap tong luong mua cua thang %d\n", i + 1);
        scanf("%d", &Year[i].totalR);
        do
        {
            printf("Nhap nhiet do cao nhat cua thang %d\n", i + 1);
            scanf("%d", &Year[i].highT);
        } while (Year[i].highT > 50 && Year[i].highT < -40);
        do
        {
            printf("Nhap nhiet do thap nhat cua thang %d\n", i + 1);
            scanf("%d", &Year[i].lowT);
        } while (Year[i].lowT > 50 && Year[i].lowT < -40);
        Year[i].aveT = (Year[i].highT + Year[i].lowT) / 2;
    }
    for (int i = 0; i < 12; i++)
    {
        TongMua += Year[i].totalR;
    }
    printf("Tong luong mua la %d\n", TongMua);
    printf("Luong mua TB la %f", (float)TongMua / 12);
    return 0;
}