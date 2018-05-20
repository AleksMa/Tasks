//
// Created by alexey on 25.04.18.
//

#include <bits/stdc++.h>

#define fi first
#define se second
#define pb push_back
#define sqr(x) ((x) * (x))

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef pair<ull, ull> PULL;
typedef vector<int> VI;
typedef long double ld;
typedef unsigned uint;

const int inf = INT_MAX;
const ll linf = LLONG_MAX;
const int mod = 1000007;

struct Vertex{
    int index, i, j;
    int dist;
    int elem;
    bool used;
};

struct PriorityQueue{
    Vertex** heap;
    int cap, count;
};

void swap(PriorityQueue *Q, int i, int j){
    Vertex *t = Q->heap[i];
    Q->heap[i] = Q->heap[j];
    Q->heap[j] = t;
}

bool QueueEmpty(PriorityQueue *Q){
    return Q->count == 0;
}


int Insert(PriorityQueue *Q, Vertex *X){
    int i = Q->count;
    Q->count=i+1;
    Q->heap[i] = X;
    while(i > 0 && (Q->heap[(i-1)/2]->dist > Q->heap[i]->dist)){
        swap(Q, (i-1)/2, i);
        Q->heap[i]->index = i;
        i = (i-1)/2;
    }
    Q->heap[i]->index = i;
}

void Heapify(int i, int n, PriorityQueue *Q){
    int j = i;
    while(1){
        int l = 2*i +1;
        int r = l+1;
        j = i;
        if(l<n && Q->heap[i]->dist > Q->heap[l]->dist) i = l;
        if(r<n && Q->heap[i]->dist > Q->heap[r]->dist) i = r;
        if(i==j)break;
        swap(Q, i, j);
        Q->heap[i]->index = i;
        Q->heap[j]->index = j;
    }
}


Vertex *ExtractMin(PriorityQueue *Q){
    Vertex *X = Q->heap[0];
    Q->count--;
    if(Q->count>0){
        Q->heap[0]=Q->heap[Q->count];
        Q->heap[0]->index = 0;
        Heapify(0, Q->count, Q);
    }
    return X;
}

int IncreaseKey(PriorityQueue *Q, Vertex *X, int key){
    int i = X->index;
    X->dist = key;
    Q->heap[i]->dist = key;
    while(i > 0 && Q->heap[(i - 1) / 2]->dist > key){
        swap(Q, (i - 1) / 2, i);
        Q->heap[i]->index = i;
        i = (i - 1) / 2;
    }
    X->index = i;
}

void InitPriorityQueue(PriorityQueue *Q, int N)
{
    Q->heap = new Vertex*[N];
    Q->cap = N;
    Q->count = 0;
}

void DeleteQueue(PriorityQueue *Q){
    delete [] Q->heap;
}

bool Relax(Vertex *v, Vertex *u, int w){
    if(v->dist >= inf || w >= inf)
        return false;
    bool changed = v->dist + w < u->dist;
    if(changed){
        u->dist = v->dist + w;
    }
    return changed;
}

void Dijkstra(vector <Vertex*> &V, int s, int N){
    PriorityQueue Q;
    InitPriorityQueue(&Q, V.size());
    for(int v = 0; v < V.size(); v++){
        if(v == s)
            V[v]->dist = V[v]->elem;
        else
            V[v]->dist = inf;
        V[v]->used = false;
    }
    Insert(&Q, V[0]);
    V[0]->used = true;
    while(!QueueEmpty(&Q)){
        Vertex *v = ExtractMin(&Q);
        v->index = -1;

        if(v->i > 0){
            Vertex *u = V[v->j + N*(v->i - 1)];
            if(!u->used){
                Insert(&Q, u);
                u->used = true;
            }

            if(u->index != -1 && Relax(v, u, u->elem))
                IncreaseKey(&Q, u, u->dist);
        }
        if(v->j > 0){
            Vertex *u = V[v->j - 1 + N*v->i];
            if(!u->used){
                Insert(&Q, u);
                u->used = true;
            }
            if(u->index != -1 && Relax(v, u, u->elem))
                IncreaseKey(&Q, u, u->dist);
        }
        if(v->i < N - 1){
            Vertex *u = V[v->j + N*(v->i + 1)];
            if(!u->used){
                Insert(&Q, u);
                u->used = true;
            }
            if(u->index != -1 && Relax(v, u, u->elem))
                IncreaseKey(&Q, u, u->dist);
        }
        if(v->j < N - 1){
            Vertex *u = V[v->j + 1 + N*v->i];
            if(!u->used){
                Insert(&Q, u);
                u->used = true;
            }
            if(u->index != -1 && Relax(v, u, u->elem))
                IncreaseKey(&Q, u, u->dist);
        }
    }
    DeleteQueue(&Q);
}

int main(){

    int N;
    cin >> N;
    Vertex *V = new Vertex[N*N];
    vector <Vertex*> G(N*N);
    int a;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> a;
            V[j + N*i].elem = a;
            V[j + N*i].j = j;
            V[j + N*i].i = i;
            G[j + N*i] = &V[j + N*i];
        }
    }

    Dijkstra(G, 0, N);

    cout << V[N*N - 1].dist;
    delete [] V;
    return 0;

}