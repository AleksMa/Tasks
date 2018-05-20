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
    int index, i;
    int key, value;
    vector < PII > incidence;
};

struct PriorityQueue{
    Vertex **heap;
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
    while(i > 0 && (Q->heap[(i-1)/2]->key > Q->heap[i]->key)){
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
        if(l<n && Q->heap[i]->key > Q->heap[l]->key) i = l;
        if(r<n && Q->heap[i]->key > Q->heap[r]->key) i = r;
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
    X->key = key;
    Q->heap[i]->key = key;
    while(i > 0 && Q->heap[(i - 1) / 2]->key > key){
        swap(Q, (i - 1) / 2, i);
        Q->heap[i]->index = i;
        i = (i - 1) / 2;
    }
    X->index = i;
}

void InitPriorityQueue(PriorityQueue *Q, int N)
{
    Q->heap = (Vertex**)malloc(N*sizeof(Vertex*));
    Q->cap = N;
    Q->count = 0;
}




int main(){

    int n = 0, m = 0, count = 0;
    cin >> n >> m;
    vector <Vertex> V(n);

    for(int i = 0; i < n; i++) {
        V[i].i = i;
        V[i].index = -1;
    }

    int a = 0, b = 0, c = 0;
    for(int i = 0; i < m; i++){
        cin >> a >> b >> c;
        V[a].incidence.pb(PII (b, c));
        if(a != b)
            V[b].incidence.pb(PII (a, c));
    }

    PriorityQueue Q;
    InitPriorityQueue(&Q, n);
    Vertex *v = &V[0];
    int j = 0;
    while(true){
        v->index = -2;
        for(int i = 0; i < v->incidence.size(); i++){
            Vertex *u = &V[v->incidence[i].fi];
            if(u->index == -1){
                u->key = v->incidence[i].se;
                u->value = v->i;
                Insert(&Q, u);
            }
            else if(u->index != -2 && v->incidence[i].se < u->key){
                u->value = v->i;
                IncreaseKey(&Q, u, v->incidence[i].se);
            }
        }
        if(QueueEmpty(&Q))
            break;
        v = ExtractMin(&Q);
        count += v->key;
    }

    cout << count;

    free(Q.heap);

    return 0;
}