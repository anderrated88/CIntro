#include <stdio.h>
#include <stdlib.h>
typedef struct Objects
{
    int weight;
    int value;
    int quantity;
    char name;
} Object;
int TimMax(int a, int b);
int main()
{
    Object ObjectList[10];
    int N, W, j, KQ = 0;
    int i = 1;
    char line[100];
    FILE *fr = fopen("BAG2.INP", "r");
    fgets(line, 100, fr);
    sscanf(line, "%d %d", &N, &W);
    while (fgets(line, 100, fr)) //Doc du lieu tu file BAG.INP
    {
        sscanf(line, "%d %d %c", &ObjectList[i].weight, &ObjectList[i].value, &ObjectList[i].name);
        i++;
    }
    fclose(fr);
    int S[N + 1][W + 1];
    int X[N + 1][W + 1];
    for (i = 1; i <= N; i++)
    {
        S[i][0] = 0;
        X[i][0] = 0;
    }

    for (i = 1; i <= W; i++)
    {
        X[1][i] = i / ObjectList[1].weight;
        S[1][i] = X[1][i] * ObjectList[1].value;
    }
    for (i = 2; i <= N; i++)
    {
        int c;
        for (j = 1; j <= W; j++)
            for (c = 0; c <= (j / ObjectList[i].weight); c++)
            {
                S[i][j] = TimMax(S[i - 1][j], S[i - 1][j - c * ObjectList[i].weight] + c * ObjectList[i].value);
                X[i][j] = 0;
                if (S[i - 1][j] < S[i - 1][j - c * ObjectList[i].weight] + c * ObjectList[i].value)
                    X[i][j] = c;
            }
    }

    printf("Bang S\n");
    for (i = 1; i <= N; i++)
    {
        for (j = 0; j <= W; j++)
            printf("%5d", S[i][j]);
        printf("\n");
    }
    printf("Bang X\n");
    for (i = 1; i <= N; i++)
    {
        for (j = 0; j <= W; j++)
            printf("%5d", X[i][j]);
        printf("\n");
    }
    for (i = 1; i <= N; i++)
        for (j = 0; j <= W; j++)
            if (KQ < S[i][j])
                KQ = S[i][j];
    printf("KQ la:\n--------------------\n%d\n", KQ);
    int u = N, v = W, temp = 0;
    while ((S[u][v] = S[u - 1][v]) || (X[u][v] == 0))
        u -= 1;
    while (KQ != temp && v >= 0)
    {
        ObjectList[u].quantity = X[u][v];
        printf("%c %d\n", ObjectList[u].name, ObjectList[u].quantity);
        temp += ObjectList[u].quantity * ObjectList[u].value;
        v -= ObjectList[u].quantity * ObjectList[u].weight;
        if (X[u][v] != 0)
            printf("%c %d\n", ObjectList[u].name, ObjectList[u].quantity);
        v--;
    }
    return 0;
}
int TimMax(int a, int b)
{
    int max = a > b ? a : b;
    return max;
}