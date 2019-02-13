#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** Delta(char* S, int size)
{
    int i = 0, j = 0, len = strlen(S);
    int** d = (int**)malloc(len * sizeof(int*));
    for (i = 0; i < len; i++)
        d[i] = (int*)malloc(size * sizeof(int));
    for (i = 0; i < len; i++)
        for (j = 0; j < size; j++)
            d[i][j] = len;
    i = j = 0;
    for (i = 0; i < len; i++) {
        d[i][S[i]] = len - i - 1;
        for (j = i; j < len; j++)
            d[j][S[i]] = len - i - 1;
    }
    return d;
}

int BME(char* S, char* T, int size)
{
    int lenS = strlen(S), lenT = strlen(T);
    int** d = Delta(S, size);
    int k = lenS - 1;
    while (k < lenT) {
        int i = lenS - 1;
        while (T[k] == S[i]) {
            if (i == 0) {
                for (int i = 0; i < lenS; i++)
                    free(d[i]);
                free(d);
                return k;
            }
            i--;
            k--;
        }
        k = k + d[i][T[k]];
    }
    for (int i = 0; i < lenS; i++)
        free(d[i]);
    free(d);
    return lenT;
}

int main(int argc, char** argv)
{
    int s = strlen(argv[1]), t = strlen(argv[2]);
    char *S = argv[1], *T = argv[2];
    printf("%d", BME(S, T, 128));
    return 0;
}

