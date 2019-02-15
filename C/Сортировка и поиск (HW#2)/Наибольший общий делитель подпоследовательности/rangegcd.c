#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b)
{
    if (!a)
        return b;
    else if (!b)
        return a;
    else if (a == b)
        return a;
    else if (a == 1 || b == 1)
        return 1;
    else if (a % 2 == 0 && b % 2 == 0)
        return 2 * gcd(a >> 1, b >> 1);
    else if (a % 2 == 0)
        return gcd(a >> 1, b);
    else if (b % 2 == 0)
        return gcd(a, b >> 1);
    else if (b > a)
        return gcd(a, (b - a) >> 1);
    else
        return gcd((a - b) >> 1, b);
}

int Query(int** ST, int l, int r)
{
    int j = log2(r - l + 1);
    int J = 1 << j;
    return gcd(ST[l][j], ST[r - J + 1][j]);
}

int** Build(int* array, int n)
{
    int m = log2(n) + 1;
    int i = 0, j = 1;
    int** ST = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        ST[i] = (int*)malloc(m * sizeof(int));
    i = 0;
    while (i < n) {
        ST[i][0] = abs(array[i]);
        i++;
    }
    int J = 1;
    while (j < m) {
        i = 0;
        J = J << 1;
        while (i <= n - J) {
            int Json = J >> 1;
            ST[i][j] = gcd(ST[i][j - 1], ST[i + Json][j - 1]);
            i++;
        }
        j++;
    }
    return ST;
}

int main()
{
    int N = 0, M = 0;
    scanf("%d", &N);
    int* array = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &array[i]);
    int** ST = Build(array, N);

    scanf("%d", &M);
    for (int j = 0; j < M; j++) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", Query(ST, l, r));
    }
    for (int i = 0; i < N; i++)
        free(ST[i]);
    free(array);
    free(ST);
    return 0;
}

