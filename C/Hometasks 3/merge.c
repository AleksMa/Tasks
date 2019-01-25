#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue{
    int *heap;
    int cap, count;
};

void swap(struct PriorityQueue *Q, int i, int j)
{
    int t = Q->heap[i];
    Q->heap[i] = Q->heap[j];
    Q->heap[j] = t;
}

int QueueEmpty(struct PriorityQueue *Q){
    return Q->count==0?1:0;
}

void Insert(struct PriorityQueue *Q, int X){
    int i = Q->count;
    Q->count=i+1;
    Q->heap[i] = X;
    while(i>0 && (Q->heap[(i-1)/2]) > Q->heap[i]){
        swap(Q, (i-1)/2, i);
        i = (i-1)/2;
    }
}

void Heapify(int i, int n, struct PriorityQueue *Q){
    int j = i;
    int k = 0;
    while(1){
        int l = 2*i +1;
        int r = l+1;
        j = i;
        if(l<n && Q->heap[i]>Q->heap[l]) i = l;
        if(r<n && Q->heap[i]>Q->heap[r]) i = r;
        if(i==j)break;
        swap(Q, i, j);
    }
}

int ExtractMax(struct PriorityQueue *Q){
    int X = Q->heap[0];
    Q->count--;
    if(Q->count>0){
        Q->heap[0]=Q->heap[Q->count];
        Heapify(0, Q->count, Q);
    }
    return X;
}

void InitPriorityQueue(struct PriorityQueue *Q,int N)
{
    Q->heap = malloc(N*sizeof(int));
    Q->cap = N;
    Q->count = 0;
}

int main(){
    struct PriorityQueue MainQueue;
    struct PriorityQueue *Q = &MainQueue;
    int N = 0, i = 0, j=0, M=0;
    scanf("%d", &N);
    int *count = (int*)malloc(N*sizeof(int));
    for(i = 0; i<N; i++){
        scanf("%d", &count[i]);
        M+=count[i];
    }
    InitPriorityQueue(Q, M);
    int **Matrixx = (int**)malloc(N*sizeof(int*));
    for(i = 0; i<N; i++){
        Matrixx[i]=(int*)malloc(count[i]*sizeof(char));
        for(j = 0; j<count[i]; j++){
            scanf("%d", &Matrixx[i][j]);
            Insert(Q, Matrixx[i][j]);
        }
    }

    for(i = 0; i<M; i++){
        printf("%d ", Q->heap[i]);
        //printf("%d ", ExtractMax(Q));

    }


    /*
    for(i = 0; i<N; i++){
        for(j = 0; j<count[i]; j++){
            printf("%d ", Matrixx[i][j]);
        }
        printf("\n");
    }*/
    free(Q->heap);
    for(i = 0; i<N; i++){
        free(Matrixx[i]);
    }
    free(Matrixx);
    free(count);
}
















