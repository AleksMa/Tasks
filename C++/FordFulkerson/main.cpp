#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <limits>

using namespace std;

struct Vertex{
    int num, d, color; //WHITE = 0, GRAY = 1, BLACK = 2
    int parent;
};

struct Rib{
    int c, f, gf;
};

struct Queue{
    int *data;
    int cap, countt, head, tail;
};

int QueueEmpty(struct Queue *Q){
    return Q->countt==0?1:0;
}

void Enqueue(struct Queue *Q, int X){
    Q->data[Q->tail] = X;
    Q->tail++;
    if(Q->tail==Q->cap)
        Q->tail=0;
    Q->countt++;
}

int Dequeue(struct Queue *Q){
    int X = Q->data[Q->head++];
    if(Q->head==Q->cap)
        Q->head=0;
    Q->countt--;
    return X;
}

void InitQueue(struct Queue *Q,int N)
{
    Q->data = (int*)malloc(N*sizeof(int));
    Q->cap = N;
    Q->countt = 0;
    Q->head = 0;
    Q->tail = 0;
}

int Cf(struct Rib **E, int u, int v){
    if(E[u][v].c){
        return E[u][v].c - E[u][v].f;
    }
    else if(E[v][u].c){
        return E[u][v].f;
    }
    else return 0;
}

int BFS(struct Rib **E, int n){
    int MinCap = 101;
    int u = 0;
    struct Vertex *V = (struct Vertex*)malloc(n*sizeof(struct Vertex));
    for(int i = 1; i<n; i++){
        V[i].color = 0;
        V[i].d = 100;
        V[i].parent = -1;
    }
    V[0].color = 1;
    V[0].d = 0;
    V[0].parent  = -1;
    struct Queue MainQueue;
    struct Queue *Q = &MainQueue;
    InitQueue(Q, n);
    Enqueue(Q, 0);
    while(!QueueEmpty(Q)){
        u = Dequeue(Q);
        if(u == n-1){
            break;
        }
        for(int v = 0; v<n; v++){
            //if(E[u][v].c==0)continue;
            if(V[v].color==0 && Cf(E, u, v)){
                //(E[u][v].c-E[u][v].f || -E[v][u].f)){
                V[v].color = 1;
                V[v].d = V[u].d + 1;
                V[v].parent = u;
                Enqueue(Q, v);
            }
        }
        V[u].color = 2;
    }
    if(u!=n-1)
        return 0;
    int i = n-1;
    while(i!=0){
        int cf = Cf(E, V[i].parent, i);
        MinCap=(MinCap>cf?cf:MinCap);
        i = V[i].parent;
    }
    i = n-1;
    while(i!=0){
        if(E[V[i].parent][i].c)E[V[i].parent][i].f+=MinCap;
        else E[i][V[i].parent].f-=MinCap;
        i = V[i].parent;
    }
    return MinCap;
}

int FordFulkerson(struct Rib **E, int n){
    int Cf = 101, F = 0;
    while(Cf = BFS(E, n)){
        F+=Cf;
    }
    return F;
}

int main(){

    int n, m, i = 0, j = 0;
    int a, b, c;
    cin >> n >> m;
    struct Rib **E = (struct Rib **)malloc(n*sizeof(struct Rib*));
    for(i = 0; i<n; i++){
        E[i] = (struct Rib *)malloc(n*sizeof(struct Rib));
    }
    for(i = 0; i<n; i++){
        for(j = 0; j<n; j++){
            E[i][j].c=E[i][j].f=0;
        }
    }
    for(i = 0; i<m; i++){
        cin >> a >> b >> c;
        E[--a][--b].c=c;
    }

    cout << FordFulkerson(E, n);
    /*cout << endl;
    //DEBUG
    for(i = 0; i<n; i++){
        for(j = 0; j<n; j++){
            cout << E[i][j].f << " ";
        }
        cout << endl;
    }*/



    return 0;
}