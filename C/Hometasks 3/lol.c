#include <stdio.h>
#define LENGTH 100000
#include <math.h>

typedef struct Task{
    int low, high;
};

typedef struct Stack{
    struct Task * data;
    int cap, top;
};

void Push(struct Stack *S, struct Task x){
    S->data[S->top] = x;
    S->top++;
}

int StackEmpty(struct Stack *S){
    return S->top==0?1:0;
}

struct Task Pop(struct Stack *S){
    S->top--;
    return S->data[S->top];
}

void InitStack(struct Stack *S, int N)
{
    S->data = (struct Task*)malloc(N*sizeof(struct Task));
    S->cap = N;
    S->top = 0;
}

int compare(int i, int j, int *array)
{
        return array[i] - array[j];
}

void swap(int i, int j, int *array)
{
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
}

int Partition(int low, int high, int *array){
    int i = low, j = low;
    while(j<high){
        if(compare(j, high, array)<0){
            swap(i, j, array);
            i++;
        }
        j++;
    }
    swap(i, high, array);
    return i;
}

void QuickSort(int low, int high, int *array){
    struct Stack MainStack;
    struct Stack *S = &MainStack;
    InitStack(S, LENGTH);
    struct Task T;
    T.low = low;
    T.high = high;
    Push(S, T);

    while(!StackEmpty(S)){
        T = Pop(S);
        if(T.high<T.low)
            continue;
        int i = Partition(T.low, T.high, array);
        struct Task T1, T2;
        T1.low = T.low;
        T1.high = i-1;
        T2.low = i+1;
        T2.high = T.high;
        if (i - 1 > high - i){
            Push(S, T1);
            Push(S, T2);
        }
        else{
            Push(S, T2);
            Push(S, T1);
        }
    }

    free(S->data);
}




int main(){

    int N=0;
    scanf("%d", &N);
    int *array = malloc(N*sizeof(int));
    for(int i=0; i<N; i++)scanf("%d", &array[i]);
    QuickSort(0, N-1, array);
    for(int i=0; i<N; i++)printf("%d ", array[i]);
    free(array);
    return 0;
}

