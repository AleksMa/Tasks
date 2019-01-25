#include <stdio.h>

struct Elem{
    int Num, Max;
};

struct DoubleStack {
    struct Elem *data;
    int cap;
    int top1, top2;
};

int max(int X, int Y){
    return X>Y?X:Y;
}

void InitDoubleStack(struct DoubleStack *S,int N)
{
    S->data = (struct Elem*)malloc(N*sizeof(struct Elem));
    S->cap = N;
    S->top1 = 0;
    S->top2 = N-1;
}

int StackEmpty1(struct DoubleStack *S){
    return S->top1==0?1:0;
}

int StackEmpty2(struct DoubleStack *S){
    return S->top2==S->cap-1?1:0;
}

int QueueEmpty(struct DoubleStack *S){
    return StackEmpty1(S)*StackEmpty2(S);
}

void Push1(struct DoubleStack *S, int x){
    S->data[S->top1].Num = x;
    S->data[S->top1].Max = StackEmpty1(S)?x:max(x, S->data[S->top1-1].Max);
    S->top1++;
}

void Push2(struct DoubleStack *S, int x){
    S->data[S->top2].Num = x;
    S->data[S->top2].Max = StackEmpty2(S)?x:max(x, S->data[S->top2+1].Max);
    S->top2--;
}

int Pop1(struct DoubleStack *S){
    S->top1--;
    return S->data[S->top1].Num;
}

int Pop2(struct DoubleStack *S){
    S->top2++;
    return S->data[S->top2].Num;
}



void Enqueue(struct DoubleStack *S, int X){
    Push1(S, X);
}

int Dequeue(struct DoubleStack *S){
    if(StackEmpty2(S)){
        while(!StackEmpty1(S))
            Push2(S, Pop1(S));
    }
    return Pop2(S);
}

int MaxQueue(struct DoubleStack *S){
    if(StackEmpty1(S))
        return S->data[S->top2+1].Max;
    else if (StackEmpty2(S))
        return S->data[S->top1-1].Max;
    else return max(S->data[S->top2+1].Max, S->data[S->top1-1].Max);
}

int main(){
    struct DoubleStack MainQueue;
    struct DoubleStack *Q = &MainQueue;
    int K = 0;
    scanf("%d", &K);
    InitDoubleStack(Q, 2*K);
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
            break;
        case 'M':
            printf("%d\n", MaxQueue(Q));
        }
        for(int i=0; i<Q->cap; i++)
            printf("%d ", Q->data[i].Num);
        printf("\n");
        for(int i=0; i<Q->cap; i++)
            printf("%d ", Q->data[i].Max);
        printf("\n%d %d", Q->top1, Q->top2);
        printf("\n");

    }

    free(Q->data);
    return 0;
}





