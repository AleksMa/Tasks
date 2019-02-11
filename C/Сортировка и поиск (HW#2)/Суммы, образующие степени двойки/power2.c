#include <stdio.h>

int Power2(int x)
{
    if (!x)
        return 0;
    while ((x % 2 == 0 || x == 1) && x > 0)
        x /= 2;
    if (x)
        return 0;
    return 1;
}

void Diff(int* base, int i, int n)
{
    int k = 0;
    for (int j = 0; j < n - 1; j++) {
        if (i == j) {
            base[j] = base[++k];
        }
        else
            base[j] = base[k];
        k++;
    }
    base[n - 1] = 0;
}

int KolComb(int* base, int n)
{
    int kol = 0;
    for (int m = 1; m <= n; m++)
        kol += Comb(base, m, 0, n);
    return kol;
}

int Comb(int* base, int m, int sum, int n)
{
    int kol = 0;
    if (m == 0) {
        return Power2(sum);
    }
    if (n == m) {
        for (int j = 0; j < n; j++)
            sum += base[j];
        return Power2(sum);
    }
    int q[n];
    for (int j = 0; j < n; j++)
        q[j] = base[j];
    for (int i = 0; i < n; n--) {
        if (n < m)
            break;
        int t = q[0];
        Diff(q, 0, n);
        kol += Comb(q, m - 1, sum + t, n - 1);
    }
    return kol;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    printf("%d", KolComb(array, n));
}
