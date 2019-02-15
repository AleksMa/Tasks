#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* LnKad(double* array, int n)
{
    int l = 0, r = 0, start = 0, i = 0;
    double max = array[0], sum = 0;
    while (i < n) {
        sum += array[i];
        if (sum - max > 0.0000001) {
            max = sum;
            l = start;
            r = i;
        }
        i++;
        if (sum < 0) {
            sum = 0;
            start = i;
        }
    }
    int* lr = (int*)malloc(2 * sizeof(int));
    lr[0] = l;
    lr[1] = r;
    return lr;
}

int main()
{
    int N;
    scanf("%d", &N);
    double* array = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        int m, n;
        scanf("%d/%d", &m, &n);
        array[i] = log(m) - log(n);
    }
    int* lr = LnKad(array, N);
    printf("%d %d", lr[0], lr[1]);
    free(lr);
    free(array);
    return 0;
}
