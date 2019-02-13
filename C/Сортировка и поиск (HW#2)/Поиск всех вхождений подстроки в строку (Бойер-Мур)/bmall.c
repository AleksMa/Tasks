#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* Suffix(char* S)
{
    int len = strlen(S);
    int* suf = (int*)malloc(len * sizeof(int));
    int t = len - 1, i = len - 2;
    suf[len - 1] = len - 1;
    while (i >= 0) {
        while (t < len - 1 && S[t] != S[i])
            t = suf[t + 1];
        if (S[t] == S[i])
            t--;
        suf[i] = t;
        i--;
    }
    return suf;
}

int* Delta1(char* S, int size)
{
    int* d1 = (int*)malloc(size * sizeof(int));
    int i = 0, j = 0, len = strlen(S);
    while (i < size) {
        d1[i] = len;
        i++;
    }
    while (j < len) {
        d1[S[j]] = len - j - 1;
        j++;
    }
    return d1;
}

int* Delta2(char* S)
{
    int i = 0, len = strlen(S);
    int* d2 = (int*)malloc(len * sizeof(int));
    int* suf = Suffix(S);
    int t = suf[0];
    while (i < len) {
        while (t < i)
            t = suf[t + 1];
        d2[i] = -i + t + len;
        i++;
    }
    i = 0;
    while (i < len - 1) {
        int t = i;
        while (t < len - 1) {
            t = suf[t + 1];
            if (S[i] != S[t])
                d2[t] = -i - 1 + len;
        }
        i++;
    }
    free(suf);
    return d2;
}

int* BMall(char* S, char* T, int size)
{
    int lenS = strlen(S), lenT = strlen(T);
    int* d1 = Delta1(S, size);
    int* d2 = Delta2(S);
    int k = lenS - 1;
    int* count = (int*)malloc(lenT * sizeof(int));
    int j = 0;
    for (int i = 1; i < lenT; i++)
        count[i] = 0;
    count[0] = lenT;
    while (k < lenT) {
        int i = lenS - 1;
        while (T[k] == S[i]) {
            if (i == 0) {
                count[j] = k;
                j++;
                break;
            }
            i--;
            k--;
        }
        k = k + (d1[T[k]] >= d2[i] ? d1[T[k]] : d2[i]);
    }
    free(d1);
    free(d2);
    return count;
}

int main(int argc, char** argv)
{
    int s = strlen(argv[1]), t = strlen(argv[2]);
    char *S = argv[1], *T = argv[2];
    int* count = BMall(S, T, 128);
    int i = 0;
    while (i == 0 || count[i] != 0) {
        printf("%d ", count[i]);
        i++;
    }
    free(count);
    return 0;
}

