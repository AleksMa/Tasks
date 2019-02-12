#include <stdio.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

void DistributionSort(int m, union Int32* base, int n, int index)
{
    int j = 0, i = 1;
    int count[m];
    for (int k = 0; k < m; k++)
        count[k] = 0;
    while (j < n) {
        int k = base[j].bytes[index];
        if (index < 3)
            count[k]++;
        else
            count[(k + 128) % 256]++;
        j++;
    }
    while (i < m) {
        count[i] += count[i - 1];
        i++;
    }
    union Int32 D[n];
    j = n - 1;
    while (j >= 0) {
        int k = base[j].bytes[index];
        if (index < 3)
            i = --count[k];
        else
            i = --count[(k + 128) % 256];
        D[i] = base[j];
        j--;
    }
    for (int i = 0; i < n; i++)
        base[i] = D[i];
}

void RadixSort(int m, union Int32* base, int n)
{

    int i = 0;
    int q = 4;
    while (i < q) {
        DistributionSort(m, base, n, i);
        i++;
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    union Int32 array[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i].x);
    RadixSort(256, array, n);
    for (int i = 0; i < n; i++)
        printf("%d ", array[i].x);
}

