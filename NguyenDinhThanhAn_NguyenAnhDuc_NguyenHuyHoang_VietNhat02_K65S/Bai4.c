#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
void GiamDan(int a[], int n)
{
    int tg;
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (a[i] < a[j])
            {
                tg = a[i];
                a[i] = a[j];
                a[j] = tg;
            }
        }
    }
}
bool c[13][4] = {};
int main()
{
    srand(time(NULL));
    int s1[13], s2[13], s3[13], s4[13], t, n1 = 1, n2 = 1, n3 = 1, n4 = 1, dem = 1;
    int i1, i2, i3, i4, i, j, tq1, tq2, tq3, tq4;
    while (dem <= 52)
    {
        t = rand() % 52;
        j = t / 13;
        i = t % 13;
        if (c[i][j] == 0)
        {
            c[i][j] = 1;
            if (dem <= 13)
            {
                s1[n1] = t;
                n1++;
            }
            if (13 < dem && dem <= 26)
            {
                s2[n2] = t;
                n2++;
            }
            if (26 < dem && dem <= 39)
            {
                s3[n3] = t;
                n3++;
            }
            if (39 < dem && dem <= 52)
            {
                s4[n4] = t;
                n4++;
            }
            dem++;
        }
    }
    GiamDan(s1, n1);
    GiamDan(s2, n2);
    GiamDan(s3, n3);
    GiamDan(s4, n4);
    printf("bai cua nguoi choi thu nhat la:");
    for (int i = 1; i < n1; i++)
        printf("%d ", s1[i]);
    printf("\nbai cua nguoi choi thu hai la:");
    for (int i = 1; i < n2; i++)
        printf("%d ", s2[i]);
    printf("\nbai cua nguoi choi thu ba la:");
    for (int i = 1; i < n3; i++)
        printf("%d ", s3[i]);
    printf("\nbai cua nguoi choi thu tu la:");
    for (int i = 1; i < n4; i++)
        printf("%d ", s4[i]);
    tq1 = tq2 = tq3 = tq4 = 0;
    for (int i = 1; i < 13; i++)
    {
        i1 = i2 = i3 = i4 = 0;
        for (int j = i + 1; j <= 13; j++)
        {
            if ((s1[i] - s1[j]) % 13 == 0)
            {
                i1++;
                if (i1 == 4)
                {
                    tq1++;
                    continue;
                }
            }
            if ((s2[i] - s2[j]) % 13 == 0)
            {
                i2++;
                if (i2 == 4)
                {
                    tq2++;
                    continue;
                }
            }
            if ((s3[i] - s3[j]) % 13 == 0)
            {
                i3++;
                if (i3 == 4)
                {
                    tq3++;
                    continue;
                }
            }
            if ((s4[i] - s4[j]) % 13 == 0)
            {
                i4++;
                if (i4 == 4)
                {
                    tq4++;
                    continue;
                }
            }
        }
    }
    printf("\nSo tu quy cua nguoi choi 1 la %d", tq1);
    printf("\nSo tu quy cua nguoi choi 2 la %d", tq2);
    printf("\nSo tu quy cua nguoi choi 3 la %d", tq3);
    printf("\nSo tu quy cua nguoi choi 4 la %d", tq4);
}
