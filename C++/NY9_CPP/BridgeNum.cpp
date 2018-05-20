//
// Created by alexey on 12.03.18.
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

using namespace std;

struct Vertex{
    int mark, parent, comp;
    vector <int> incidence;
    vector <int> orientRib;
};

void VisitVertex1(vector <Vertex> *V, int v, queue <int> *Q){

    (*V)[v].mark = 1;
    Q->push(v);
    for(int i = 0; i < (*V)[v].incidence.size(); i++){
        int u = (*V)[v].incidence[i];
        //(*V)[v].incidence.erase((*V)[v].incidence.begin()+i);
        if(!(*V)[u].mark){
            (*V)[u].parent = v;
            VisitVertex1(V, u, Q);
        }
    }
    (*V)[v].mark = 2;
}

int DFS1(vector <Vertex> *V, queue <int> *Q){
    int L = 0;
    for(int i = 0; i < V->size(); i++){
        (*V)[i].mark = 0;
    }

    for(int i = 0; i < V->size(); i++){
        if((*V)[i].mark)
            continue;
        (*V)[i].parent = -1;
        VisitVertex1(V, i, Q);
        L++;
    }
    return L;
}

void VisitVertex2(vector <Vertex> *V, int v, int component){

    (*V)[v].comp = component;
    for(int i = 0; i < (*V)[v].incidence.size(); i++){
        int u = (*V)[v].incidence[i];
        //(*V)[v].incidence.erase((*V)[v].incidence.begin()+i);
        if((*V)[u].comp == -1 && (*V)[u].parent != v){
            VisitVertex2(V, u, component);
        }
    }
    (*V)[v].mark = 2;
}

int DFS2(vector <Vertex> *V, queue <int> *Q){

    for(int i = 0; i < V->size(); i++){
        (*V)[i].comp = -1;
    }

    int component = 0;

    while(!(*Q).empty()){
        int v = (*Q).front();
        (*Q).pop();
        if((*V)[v].comp == -1){
            VisitVertex2(V, v, component);
            component++;
        }
    }
    return component;
}


int main(){
    int N, M, i = 0, j = 0;
    cin >> N >> M;
    vector <Vertex> V(N);

    int u, v;
    for(i = 0; i < M; i++){
        cin >> u >> v;
        V[u].incidence.push_back(v);
        if(u != v)
            V[v].incidence.push_back(u);
    }


    queue <int> Q;

    int L = DFS1(&V, &Q); // Количество компонент связности
    int K = DFS2(&V, &Q); // Количество компонент двусвязности
    cout << K - L;

    return 0;
}