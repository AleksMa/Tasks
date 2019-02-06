#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int peak(int i, int *array, int n){
    if(i==0 && i==n-1)return 1;
    else if(i==0 && array[i]>=array[i+1])return 1;
    else if(i==n-1 && array[i]>=array[i-1])return 1;
    else if(i>0 && i<n-1 && array[i]>=array[i-1] && array[i]>=array[i+1])return 1;
    return 0;
}


void BuildTree(int *array, int n, int v, int a, int b, int *tree) {
	if (a == b)
		tree[v] = peak(a, array, n);
	else {
		int m = (a + b) / 2;
        BuildTree(array, n, v*2, a, m, tree);
		BuildTree(array, n, v*2+1, m+1, b, tree);
		tree[v] = tree[v*2] + tree[v*2+1];
	}
}

int Query(int *tree, int v, int l, int r, int a, int b) {
	if (l == a && r == b)
		return tree[v];
	int m = (a + b) / 2;
	if(r<=m)
        return Query(tree, 2*v, l, r, a, m);
    else if(l>m)
        return Query(tree, 2*v+1, l, r, m+1, b);
	return Query(tree, 2*v, l, m, a, m) + Query(tree, 2*v+1, m+1, r, m+1, b);
}

void MainUpdate(int *tree, int *array, int N, int i, int v, int a, int b, int val){
    array[i] = val;
    Update(tree, array, N, i, 1, 0, N-1);
    if(i>0) Update(tree, array, N, i-1, 1, 0, N-1);
    if(i<N-1) Update(tree, array, N, i+1, 1, 0, N-1);
}

void Update(int *tree, int *array, int n, int i, int v, int a, int b) {
	if (a == b){
		tree[v] = peak(i, array, n);
	}
	else {
		int m = (a + b) / 2;
		if (i <= m)
			Update(tree, array, n, i, v*2, a, m);
		else
			Update(tree, array, n, i, v*2+1, m+1, b);
		tree[v] = tree[v*2] + tree[v*2+1];
	}
}

int main(){
    int N = 0, M = 0;
    scanf("%d", &N);
    int *array = (int*)malloc(N*sizeof(int));;
    int *tree = (int*)malloc(4*N*sizeof(int));;
    int i = 0;
    for(; i<N; i++)scanf("%d", &array[i]);
    scanf("%d", &M);
    BuildTree(array, N, 1, 0, N-1, tree);
    for(i=0; i<M; i++){
        char C[4];
        for(int j = 0; j<4; j++){
            scanf(" %c", &C[j]);
            if(C[0]=='U' && j==2)break;
        }
        int arg1, arg2;
        scanf(" %d%d", &arg1, &arg2);
        if(C[0]=='P') printf("%d\n", Query(tree, 1, arg1, arg2, 0, N-1));
        else MainUpdate(tree, array, N, arg1, 1, 0, N-1, arg2);
    }
    free(array);
    free(tree);
    return 0;
}
