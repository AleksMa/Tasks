#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Date {
    int Day, Month, Year;
};

int GetL(int dest, int L)
{
    int p = pow(10, L + 1);
    return (int)(((dest) % p) / pow(10, L));
}

int LetMyStructureGo(struct Date* base, int j, int L, int fl)
{
    int k = 0;
    if (fl == 0)
        return GetL(base[j].Day, L);
    else if (fl == 1)
        return GetL(base[j].Month, L);
    return GetL(base[j].Year, L);
}

void* DSort(int L, int M, struct Date* base, int N, int fl)
{
    int j = 0, i = 1;
    int count[M];
    for (int k = 0; k < M; k++)
        count[k] = 0;
    while (j < N) {
        int k = LetMyStructureGo(base, j, L, fl);
        count[k]++;
        j++;
    }
    while (i < M) {
        count[i] += count[i - 1];
        i++;
    }
    struct Date* D = (struct Date*)malloc(N * sizeof(struct Date));
    j = N - 1;
    while (j >= 0) {
        int k = LetMyStructureGo(base, j, L, fl);
        i = --count[k];
        D[i] = base[j];
        j--;
    }
    for (int i = 0; i < N; i++)
        base[i] = D[i];
    free(D);
    //return D;
}

void* RadixSort(int m, struct Date* base, int n)
{

    //struct Date *D = base;
    int i = 0;
    int q = 2;
    //Day
    while (i < q) {

        DSort(i, m, base, n, 0);
        i++;
    }
    //Month
    i = 0;
    while (i < q) {
        DSort(i, m, base, n, 1);
        i++;
    }
    //Year
    i = 0;
    while (i < 2 * q) {
        DSort(i, m, base, n, 2);
        i++;
    }
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    //struct Date *array = (struct Date*)malloc(N*sizeof(struct Date));
    struct Date array[N];
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &array[i].Year, &array[i].Month, &array[i].Day);
    }
    RadixSort(10, array, N);
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i].Year);
        printf("%d ", array[i].Month);
        printf("%d ", array[i].Day);
        printf("\n");
    }
    //free(array);
    //free(ans);
    return 0;
}

