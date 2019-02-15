#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int imax(int a, int b)
{
    return a >= b ? a : b;
}

void BuildTree(int* array, int v, int a, int b, int* tree)
{
    if (a == b)
        tree[v] = array[a];
    else {
        int m = (a + b) / 2;
        BuildTree(array, v * 2, a, m, tree);
        BuildTree(array, v * 2 + 1, m + 1, b, tree);
        tree[v] = imax(tree[v * 2], tree[v * 2 + 1]);
    }
}

int Max(int* tree, int v, int l, int r, int a, int b)
{
    if (l == a && r == b)
        return tree[v];
    int m = (a + b) / 2;
    if (r <= m)
        return Max(tree, 2 * v, l, r, a, m);
    else if (l > m)
        return Max(tree, 2 * v + 1, l, r, m + 1, b);
    return imax(Max(tree, 2 * v, l, m, a, m), Max(tree, 2 * v + 1, m + 1, r, m + 1, b));
}

void Update(int* tree, int i, int v, int a, int b, int val)
{
    if (a == b)
        tree[v] = val;
    else {
        int m = (a + b) / 2;
        if (i <= m)
            Update(tree, i, v * 2, a, m, val);
        else
            Update(tree, i, v * 2 + 1, m + 1, b, val);
        tree[v] = imax(tree[v * 2], tree[v * 2 + 1]);
    }
}

int main()
{
    int N = 0, M = 0;
    scanf("%d", &N);
    int* array = (int*)malloc(N * sizeof(int));
    ;
    int* tree = (int*)malloc(4 * N * sizeof(int));
    ;
    int i = 0;
    for (; i < N; i++)
        scanf("%d", &array[i]);
    scanf("%d", &M);
    BuildTree(array, 1, 0, N - 1, tree);
    for (i = 0; i < M; i++) {
        char C[3];
        for (int j = 0; j < 3; j++)
            scanf(" %c", &C[j]);
        int arg1, arg2;
        scanf("%d%d", &arg1, &arg2);
        if (C[0] == 'M')
            printf("%d\n", Max(tree, 1, arg1, arg2, 0, N - 1));
        else
            Update(tree, arg1, 1, 0, N - 1, arg2);
    }
    free(array);
    free(tree);
    return 0;
}

