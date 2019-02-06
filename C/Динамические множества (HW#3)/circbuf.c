#include <stdio.h>
#include <stdlib.h>


struct Queue{
    int *data;
    int cap, count, head, tail;
};

int QueueEmpty(struct Queue *Q){
    return Q->count==0?1:0;
}

void Enqueue(struct Queue *Q, int X){
    if(Q->count==Q->cap){
        Q->cap*=2;
        Q->data=realloc(Q->data, Q->cap*sizeof(int));
        for(int j = 0; j<Q->tail; j++)
            Q->data[Q->cap/2+j]=Q->data[j];
        Q->tail+=Q->cap/2;
    }
    Q->data[Q->tail] = X;
    Q->tail++;
    if(Q->tail==Q->cap)
        Q->tail=0;
    Q->count++;
}

int Dequeue(struct Queue *Q){
    int X = Q->data[Q->head++];
    if(Q->head==Q->cap)
        Q->head=0;
    Q->count--;
    return X;
}

void InitQueue(struct Queue *Q,int N)
{
    Q->data = malloc(N*sizeof(int));
    Q->cap = N;
    Q->count = 0;
    Q->head = 0;
    Q->tail = 0;
}

int main(){
    struct Queue MainQueue;
    struct Queue *Q = &MainQueue;
    InitQueue(Q, 4);
    int K = 0;
    scanf("%d", &K);
    for(int i = 0; i<K; i++){
        char C[5];
        int X = 0;
        scanf("%s", C);
        switch(C[0]){
        case 'D':
            printf("%d\n", Dequeue(Q));
            break;
        case 'E':
            if(C[1]=='N'){
                scanf("%d", &X);
                Enqueue(Q, X);
            }
            else{
                printf("%s\n", QueueEmpty(Q)?"true":"false");
            }
        }
        for(int i=0; i<Q->cap; i++)
            printf("%d ", Q->data[i]);
        printf("\n");

    }

    free(Q->data);
    return 0;
}

