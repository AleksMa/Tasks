//
// Created by alexey on 13.03.18.
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
    bool mark, eq = true;
    int dest = -2;
    vector <int> incidence;
};

void BFS(vector <Vertex> *V, int w){
    for(int i = 0; i < V->size(); i++){
        if(i == w)
            continue;
        (*V)[i].mark = false;
    }
    (*V)[w].mark = true;
    (*V)[w].dest = 0;
    (*V)[w].eq = false;
    queue <int> Q;

    Q.push(w);
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        for(int j = 0; j < (*V)[v].incidence.size(); j++){
            int u = (*V)[v].incidence[j];
            if(!(*V)[u].mark) {
                (*V)[u].mark = true;
                (*V)[u].eq = (*V)[u].eq && ((*V)[u].dest == -2 || (*V)[u].dest == (*V)[v].dest + 1);
                (*V)[u].dest = (*V)[v].dest + 1;
                Q.push(u);
            }
        }
    }
    for(int i = 0; i < V->size(); i++) {
        if (!(*V)[i].mark)
            (*V)[i].eq = false;
    }
}

int main(){

    int N, M, K;
    cin >> N >> M;

    vector <Vertex> V(N);

    int u, v;
    for(int i = 0; i < M; i++){
        cin >> u >> v;
        V[u].incidence.push_back(v);
        if(u != v)
            V[v].incidence.push_back(u);
    }

    cin >> K;

    for(int i = 0; i < K; i++){
        cin >> u;
        //V[u].dest = 0;
        BFS(&V, u);
    }

    bool ans = false;

    for(int i = 0; i < N; i++){
        if(V[i].eq) {
            cout << i << " ";
            ans = true;
        }
    }
    if(!ans)
        cout << "-";

    return 0;
}

