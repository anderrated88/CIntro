#include <stdio.h>
typedef struct Objects
{
    int weight;
    int value;
    int quantity;
    char name;
    float DonGia;
} Object;
void TinhDonGia(Object ObjectList[], int n);
void SapXep(Object ObjectList[], int n);
void swap(Object *a, Object *b);
void Greedy(Object ObjectList[], int n, int W);
void output(Object ObjectList[], int n);
int main()
{
    Object ObjectList[10];
    int N, W;
    int i = 1, max = 0;
    char line[100];
    FILE *fr = fopen("BAG.INP", "r");
    fgets(line, 100, fr);
    sscanf(line, "%d %d", &N, &W);
    while (fgets(line, 100, fr)) //Doc du lieu tu file BAG.INP
    {
        sscanf(line, "%d %d %c", &ObjectList[i].weight, &ObjectList[i].value, &ObjectList[i].name);
        i++;
    }
    TinhDonGia(ObjectList, N);
    SapXep(ObjectList, N);
    Greedy(ObjectList, N, W);
    for (int i = 1; i <= N; i++) //Tinh gia tri lon nhat
        max += ObjectList[i].quantity * ObjectList[i].value;
    printf("%d\n", max);
    output(ObjectList, N);
    fclose(fr);
    return 0;
}
void TinhDonGia(Object ObjectList[], int n)
{
    for (int i = 1; i <= n; i++)
        ObjectList[i].DonGia = (float)ObjectList[i].value / (float)ObjectList[i].weight;
}
void swap(Object *a, Object *b)
{
    Object temp = *a;
    *a = *b;
    *b = temp;
}
void SapXep(Object ObjectList[], int n)
{
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++)
            if (ObjectList[i].DonGia < ObjectList[j].DonGia)
                swap(&ObjectList[i], &ObjectList[j]);
}
void Greedy(Object ObjectList[], int n, int W)
{
    for (int i = 1; i <= n; i++)
    {
        ObjectList[i].quantity = W / ObjectList[i].weight;
        W -= ObjectList[i].quantity * ObjectList[i].weight;
    }
}
void output(Object ObjectList[], int n)
{
    for (int i = 1; i <= n; i++)
        if (ObjectList[i].quantity != 0)
            printf("%c %d\n", ObjectList[i].name, ObjectList[i].quantity);
}