#include <stdio.h>
#include <math.h>

int tohop(int n, int k)
{
    int res = 1;
    int i = 1;
    int j = n;
    while (i < n - k + 1 && j > k)
    {
        res = res * j / i;
        i++;
        j--;
    }
    return res;
}
int main()
{
    int n, k;
    char line[100];
    FILE *fr = fopen("TOHOP.INP", "r");
    FILE *fw = fopen("TOHOP.OUT", "w");
    while (fgets(line, 100, fr))
    {
        sscanf(line, "%d %ld", &n, &k);

        fprintf(fw, "%d\n", tohop(n, k));
    }
    fclose(fw);
    fclose(fr);
    return 0;
}
