#include <stdio.h>

struct Stack {
    int *data;
    int cap;
    int top;
};

int StackEmpty(struct Stack *S){
    return S->top==0?1:0;
}

void Push(struct Stack *S, int x){
    S->data[S->top] = x;
    //printf("%d ", S->top);
    S->top++;
}

int Pop(struct Stack *S){
    S->top--;
    return S->data[S->top];
}

void InitStack(struct Stack *S,int N)
{
    S->data = malloc(N*sizeof(int));
    S->cap = N;
    S->top = 0;
}

void LetMyStackGo(struct Stack *S)
{
    free(S->data);
}

int main(){
    struct Stack MainStack;
    struct Stack *S = &MainStack;
    InitStack(S, 10);
    for(int i = 0; i<10; i++)
        Push(S, i);

    for(int i = 0; i<10; i++)
        printf("%d", S->data[i]);
    //printf("\n");
    for(int i = 0; i<10; i++)
        printf("%d", Pop(S));
    //for()
    free(S->data);
    return 0;
}
