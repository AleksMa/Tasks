#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 1000001

void Fenwick_Build(char* array, int* tree, int N)
{
    int r = 1;
    while (r < N)
        r = r << 1;
    Build(array, tree, N, 0, r - 1);
}

int Build(char* array, int* tree, int N, int l, int r)
{
    int elem = 0;
    int bound = r < N ? r : N;
    while (l < bound) {
        int M = (l + r) >> 1;
        elem ^= Build(array, tree, N, l, M);
        l = M + 1;
    }
    if (r < N) {
        elem ^= (1 << (array[r] - 'a'));
        tree[r] = elem;
    }
    return elem;
}

int Fenwick_Query(int* tree, int l, int r)
{
    return Query(tree, r) ^ Query(tree, l - 1);
}

int Query(int* tree, int i)
{
    int v = 0;
    while (i >= 0) {
        v ^= tree[i];
        i = (i & (i + 1)) - 1;
    }
    return v;
}

void Fenwik_Update(int* tree, int N, int i, int d)
{
    while (i < N) {
        tree[i] ^= d;
        i |= (i + 1);
    }
}

int main()
{
    char* str = (char*)malloc(LENGTH * sizeof(char));
    scanf("%s", str);
    //gets(str);
    int N = strlen(str);
    int* tree = (int*)malloc(N * sizeof(int));
    int i = 0;
    Fenwick_Build(str, tree, N);
    int M = 0;
    scanf("%d", &M);
    for (i = 0; i < M; i++) {
        char C[3];
        for (int j = 0; j < 3; j++) {
            scanf(" %c", &C[j]);
            if (C[0] == 'H' && j == 1)
                break;
        }
        int arg1, arg2;
        if (C[0] == 'H') {
            scanf("%d%d", &arg1, &arg2);
            int query = Fenwick_Query(tree, arg1, arg2);
            printf("%s\n", !(query & (query - 1)) ? "YES" : "NO");
        }
        else {
            scanf("%d ", &arg1);
            char c = getchar();
            int k = 0;
            while (!isspace(c)) {
                Fenwik_Update(tree, N, arg1 + k, (1 << c - 'a') ^ (1 << str[arg1 + k] - 'a'));
                str[arg1 + k] = c;
                k++;
                c = getchar();
            }
        }
    }
    free(str);
    free(tree);
    return 0;
}
