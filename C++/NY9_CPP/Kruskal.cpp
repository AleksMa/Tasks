//
// Created by alexey on 16.03.18.
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

inline int sign(ll val) { return val > 0 ? 1 : val == 0 ? 0 : -1; }
inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
inline int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
inline int mul(int a, int b) { return int(a * 1ll * b % mod); }

struct Vertex{
    double x, y;
    //vector < pair <int, int> > incidence;
    Vertex *parent;
    int i, depth;
};

struct Rib{
    double length;
    Vertex *v, *u;
    int index;
};

struct PriorityQueue{
    Rib **heap;
    int cap, count;
};


void MakeSet(Vertex *t){
    t->parent = t;
}

Vertex *Find(Vertex *x){
    if(x->parent == x)
        return x;
    else
        return x->parent = Find(x->parent);
}

void Union(Vertex *x, Vertex *y){
    Vertex *rootX = Find(x), *rootY = Find(y);
    if(rootX->depth < rootY->depth)
        rootX->parent = rootY;
    else{
        rootY->parent = rootX;
        if(rootX->depth = rootY->depth && rootY != rootX)
            rootX->depth++;
    }
}

void swap(PriorityQueue *Q, int i, int j){
    Rib *t = Q->heap[i];
    Q->heap[i] = Q->heap[j];
    Q->heap[j] = t;
}

bool QueueEmpty(PriorityQueue *Q){
    return Q->count == 0;
}


int Insert(PriorityQueue *Q, Rib *X){
    int i = Q->count;
    Q->count=i+1;
    Q->heap[i] = X;
    while(i > 0 && (Q->heap[(i-1)/2]->length > Q->heap[i]->length)){
        swap(Q, (i-1)/2, i);
        i = (i-1)/2;
    }
}

void Heapify(int i, int n, PriorityQueue *Q){
    int j = i;
    while(1){
        int l = 2*i +1;
        int r = l+1;
        j = i;
        if(l<n && Q->heap[i]->length > Q->heap[l]->length) i = l;
        if(r<n && Q->heap[i]->length > Q->heap[r]->length) i = r;
        if(i==j)break;
        swap(Q, i, j);
    }
}


Rib *ExtractMin(PriorityQueue *Q){
    Rib *X = Q->heap[0];
    Q->count--;
    if(Q->count>0){
        Q->heap[0]=Q->heap[Q->count];
        Heapify(0, Q->count, Q);
    }
    return X;
}

void InitPriorityQueue(PriorityQueue *Q, int N)
{
    Q->heap = (Rib**)malloc(N*sizeof(Rib*));
    Q->cap = N;
    Q->count = 0;
}

double SpanningTree(vector <Vertex> *V, PriorityQueue *Q){
    int n = V->size();
    double acc = 0;
    int i = 0, k = 0;

    while(k < n - 1){
        Rib *e = ExtractMin(Q);
        if(Find(e->u)->i != Find(e->v)->i){
            k++;
            acc += e->length;
            Union(e->u, e->v);
        }
        i++;
        //free(e);
    }
    free(Q->heap);
    return acc;
}

double MST_Kruskal(vector <Vertex> *V, vector <Rib> *E){

    int n = V->size();
    PriorityQueue Q;

    InitPriorityQueue(&Q, n*(n-1)/2);
    for(int i = 0; i < E->size(); i++)
        Insert(&Q, &(*E)[i]);
    return SpanningTree(V, &Q);
}


int main(){

    int n;
    cin >> n;
    vector <Vertex> V(n);
    vector <Rib> E(n*(n-1)/2);

    double x, y;
    for(int i = 0; i < n; i++) {
        V[i].i = i;
        cin >> x >> y;
        V[i].x = x;
        V[i].y = y;
        MakeSet(&V[i]);
    }
    int k = 0;
    for(int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            E[k].length = sqrt((V[i].x - V[j].x) * (V[i].x - V[j].x) + (V[i].y - V[j].y) * (V[i].y - V[j].y));
            E[k].v = &V[i];
            E[k].u = &V[j];
            k++;
        }
    }

    cout << fixed << setprecision(2) << MST_Kruskal(&V, &E);

    return 0;
}