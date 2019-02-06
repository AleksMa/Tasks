#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue{
    int *heap;
    int cap, count;
};

struct Task{
    int t1, t2;
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


int ExtractMin(struct PriorityQueue *Q){
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
    int N = 0, i = 0, j=0, K=0;
    scanf("%d", &K);
    scanf("%d", &N);
    struct Task *Cluster = (struct Task*)malloc(N*sizeof(struct Task));
    InitPriorityQueue(Q, K);
    for(i = 0; i<K; i++){
        scanf("%d", &Cluster[i].t1);
        scanf("%d", &Cluster[i].t2);
        Insert(Q, Cluster[i].t1+Cluster[i].t2);
    }
    for(i = K; i<N; i++){
        scanf("%d", &Cluster[i].t1);
        scanf("%d", &Cluster[i].t2);
        int temp = ExtractMin(Q);
        if(temp<Cluster[i].t1)
            Insert(Q, Cluster[i].t1+Cluster[i].t2);
        else
            Insert(Q, temp+Cluster[i].t2);
    }
    int Max = 0;
    //Очевидно, что наибольшее значение в очереди с приоритетом - это последнее из наименьших
    for(int i = 0; i<K-1; i++){
        ExtractMin(Q);
    }
    printf("%d", ExtractMin(Q));
    free(Q->heap);
    free(Cluster);
}
