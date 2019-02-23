#include <stdio.h>

struct Stack {
    int* data;
    int cap;
    int top;
};

void Push(struct Stack* S, int x)
{
    S->data[S->top] = x;
    S->top++;
}

int Pop(struct Stack* S)
{
    S->top--;
    return S->data[S->top];
}

void InitStack(struct Stack* S, int N)
{
    S->data = malloc(N * sizeof(int));
    S->cap = N;
    S->top = 0;
}

int main()
{
    struct Stack MainStack;
    struct Stack* S = &MainStack;
    int K = 0;
    scanf("%d", &K);
    InitStack(S, K);
    for (int i = 0; i < K; i++) {
        char C[5];
        int X = 0, a = 0, b = 0;
        ;
        scanf("%s", C);
        switch (C[0]) {
        case 'C':
            scanf("%d", &X);
            break;
        case 'A':
            a = Pop(S);
            b = Pop(S);
            X = a + b;
            break;
        case 'S':
            if (C[1] == 'U') {
                a = Pop(S);
                b = Pop(S);
                X = a - b;
            }
            else {
                a = Pop(S);
                b = Pop(S);
                Push(S, a);
                Push(S, b);
                continue;
            }
            break;
        case 'M':
            if (C[1] == 'U') {
                a = Pop(S);
                b = Pop(S);
                X = a * b;
            }
            else if (C[1] == 'A') {
                a = Pop(S);
                b = Pop(S);
                X = a > b ? a : b;
            }
            else {
                a = Pop(S);
                b = Pop(S);
                X = a < b ? a : b;
            }
            break;
        case 'D':
            if (C[1] == 'I') {
                a = Pop(S);
                b = Pop(S);
                X = a / b;
            }
            else {
                X = Pop(S);
                Push(S, X);
            }
            break;
        case 'N':
            X = -1 * Pop(S);
        }
        Push(S, X);
    }
    printf("%d", Pop(S));

    free(S->data);
    return 0;
}
