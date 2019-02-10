#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* Prefix(char* S)
{
    int len = strlen(S);
    int* pref = (int*)malloc(len * sizeof(int));
    int t = 0, i = 1;
    pref[0] = 0;
    while (i < len) {
        while (t > 0 && S[t] != S[i])
            t = pref[t - 1];
        if (S[t] == S[i])
            t++;
        pref[i] = t;
        i++;
    }
    return pref;
}

int AlmostKMP(char* S, char* T)
{
    int* pref = Prefix(S);
    int q = 0, k = 0;
    int lenT = strlen(T), lenS = strlen(S);
    int j = 0;
    while (k < lenT) {
        while (q > 0 && S[q] != T[k])
            q = pref[q - 1];
        if (S[q] == T[k])
            q++;
        k++;
    }
    free(pref);
    return q;
}

int SuperStrLength(char** S, int N)
{
    int count = 0;
    for (int i = 0; i < N; i++) {
        count += strlen(S[i]);
        if (i == N - 1)
            break;
        count -= AlmostKMP(S[i + 1], S[i]);
    }
    return count;
}

int main(int argc, char** argv)
{
    int N = 0, i = 0, j = 0;
    ;
    scanf("%d\n", &N);
    char** S = (int**)malloc(N * sizeof(char*));
    int Matrixx[N][N];
    for (i = 0; i < N; i++)
        S[i] = (char*)malloc(100 * sizeof(char));
    for (int i = 0; i < N; i++) {
        S[i][0] = 0;
        gets(S[i]);
    }
    int length = 0;
    for (i = 0; i < N; i++)
        length += strlen(S[i]);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j)
                Matrixx[i][j] = 0;
            else
                Matrixx[i][j] = AlmostKMP(S[j], S[i]);
        }
    }
    i = 0, j = 0;
    int mi = 0, mj = 0;
    int maxh, min, K;
    maxh = min = K = 0;
    int count[N];
    while (i < N) {
        while (1) {
            mj = 0;
            maxh = Matrixx[i][mj];
            for (j = 0; j < N; j++) {
                if (Matrixx[i][j] > maxh) {
                    maxh = Matrixx[i][j];
                    mj = j;
                }
            }
            if (maxh == 0) {
                count[i] = 0;
                i++;
                break;
            }
            for (int k = 0; k < N; k++) {
                if (Matrixx[k][mj] > maxh) {
                    Matrixx[i][mj] = 0;
                    break;
                }
            }
            if (maxh = Matrixx[i][mj]) {
                for (int k = 0; k < N; k++)
                    Matrixx[i][k] = Matrixx[k][mj] = 0;
                count[i] = maxh;
                i++;
                break;
            }
        }
    }
    min = count[0];
    for (i = 0; i < N; i++) {
        if (count[i] < min)
            min = count[i];
        K += count[i];
    }
    K -= min;
    printf("%d", length - K);
    for (int i = 0; i < N; i++)
        free(S[i]);
    free(S);
    return 0;
}
