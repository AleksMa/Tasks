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
    printf("%d ", S->top);
    S->top++;
}

int Pop(struct Stack *S){
    S->top--;
    return S->data[S->top];
}

struct Stack *InitStack(int n){
    struct Stack *S, MainStack;
    S = &MainStack;
    S->data = (int*)malloc(n*sizeof(int));
    //for(int i = 0; i<10; i++)S->data[i]=i;
    S->cap = n;
    S->top = 0;
    return S;
}

void LetMyStackGo(){}

int main(){
    //struct Stack MainStack;
    struct Stack *S = InitStack(10);
    for(int i = 0; i<10; i++)
        Push(S, i);

    //for(int i = 0; i<10; i++)
    //    printf("%d", S->data[8]);
    //printf("\n");
    for(int i = 0; i<10; i++)
        printf("%d", Pop(S));
    //for()
    free(S->data);
    return 0;
}
