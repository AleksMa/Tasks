//
// Created by alexey on 15.04.18.
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
    int index;
    VI incidence;
    int T1, T2, comp, low;
};

struct Cond{
    int min = inf;
    bool out = true;
};

int T = 1, K = 1;

void VisitVertexTarjan(vector <Vertex> *V, int i, stack <int> *S){
    (*V)[i].T1 = (*V)[i].low = T++;
    (*S).push(i);
    for(int u : (*V)[i].incidence){
        if((*V)[u].T1 == 0)
            VisitVertexTarjan(V, u, S);
        if((*V)[u].comp == 0 && (*V)[i].low > (*V)[u].low)
            (*V)[i].low = (*V)[u].low;
    }
    int u;
    if((*V)[i].T1 == (*V)[i].low) {
        do {
            u = (*S).top();
            (*S).pop();
            (*V)[u].comp = K;
        } while (i != u);
        K++;
    }
}

int Tarjan(vector <Vertex> *V){

    for(int i = 0; i < V->size(); i++){
        (*V)[i].comp = (*V)[i].T1 = 0;
    }

    stack <int> S;

    for(int i = 0; i < V->size(); i++){
        if(!(*V)[i].T1)
            VisitVertexTarjan(V, i, &S);
    }

}


int main(){

    int N, M, i, j;
    cin >> N >> M;
    vector <Vertex> V(N);
    vector <int> cond();

    int u, v;
    for(i = 0; i < M; i++){
        cin >> u >> v;
        V[u].incidence.pb(v);
    }
    Tarjan(&V);

    Cond C[K-1];

    for(int v = 0; v < N; v++){
        i = V[v].comp - 1;
        C[i].min = (C[i].min > v ? v : C[i].min);
        for(int u = 0; u < V[v].incidence.size(); u++){
            if(V[V[v].incidence[u]].comp != V[v].comp){
                C[V[V[v].incidence[u]].comp - 1].out = false;
            }
        }
    }

    for(j = 0; j < K - 1; j++){
        if(C[j].out)
            cout << C[j].min << " ";
    }

    return 0;
}