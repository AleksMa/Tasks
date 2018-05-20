//
// Created by alexey on 07.05.18.
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
typedef pair<string, int> PSI;
typedef pair<ull, ull> PULL;
typedef vector<string> VS;
typedef vector<int> VI;
typedef long double ld;
typedef unsigned uint;

const int inf = INT_MAX;
const ll linf = LLONG_MAX;
const int mod = 1000007;

struct Vertex{
    vector <Vertex*> incidence, coincidence, bucket;
    Vertex *parent, *ancestor, *label, *sdom, *idom;
    int mark, order, i;
};
typedef pair<int, Vertex> PIV;

map <int, Vertex> V;
vector <Vertex*> T(0);
int r, I = 0;


void VisitVertex(Vertex *v){
    v->mark = 1;
    for (Vertex* u : v->incidence)
    {
        if(!u->mark){
            u->order = I++;
            T.pb(u);
            u->parent = v;
            VisitVertex(u);
        }
    }
    v->mark = 2;
}

void DFS(){
    for (auto it = V.begin(); it != V.end(); it++) {
        it->second.mark = 0;
        it->second.parent = NULL;
    }
    V[r].order = -1;
    VisitVertex(&V[r]);
}

Vertex* FindMin(Vertex *v){
    if(v->ancestor == NULL)
        return v;
    else{
        stack <Vertex*> S;
        Vertex *u = v;
        while(u->ancestor->ancestor != NULL){
            S.push(u);
            u = u->ancestor;
        }
        while(!S.empty()){
            v = S.top();
            S.pop();
            if(v->ancestor->label->sdom->order < v->label->sdom->order)
                v->label = v->ancestor->label;
            v->ancestor = u->ancestor;
        }
        return v->label;
    }
}

void Dominators(){
    for (auto it = V.begin(); it != V.end(); it++) {
        Vertex *w = &it->second;
        w->sdom = w->label = w;
        w->idom = w;
        w->ancestor = NULL;
    }

    for(int j = T.size() - 1; j >= 0; j--){
        Vertex *w = T[j];
        for(Vertex* v : w->coincidence){
            if(!v->mark){
                continue;
            }
            Vertex* u = FindMin(v);
            if(u->sdom->order < w->sdom->order)
                w->sdom = u->sdom;
        }
        w->ancestor = w->parent;
        w->sdom->bucket.pb(w);
        for(Vertex *v : w->parent->bucket){
            Vertex *u = FindMin(v);
            v->idom = (u->sdom == v->sdom ? v->sdom : u);
        }
        w->parent->bucket.clear();
    }
    for(Vertex* w : T){
        if(w->idom != w->sdom){
            w->idom = w->idom->idom;
        }
    }
    V[r].idom = NULL;
};

int NaturalsWhereAreYou(){
    T.pb(&V[r]);
    int k = 0;
    for(Vertex *v : T){
        for(Vertex *u : v->coincidence){
            if(!u->mark){
                continue;
            }
            Vertex *w = u;
            while(w != v && w != NULL){
                w = w->idom;
            }
            if(w == v){
                k++;
                break;
            }
        }
    }
    return k;
}

int main(){

    int N;
    int a, b, prev = -1;
    string s;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> a >> s;
        if(i == 0)
            r = a;
        if(V.find(a) != V.end()){
            Vertex v;
            V.insert(PIV(a, v));
        }
        V[a].i = a;
        if(s == "BRANCH" || s == "JUMP"){
            cin >> b;
            if(V.find(b) == V.end()){
                Vertex u;
                V.insert(PIV(b, u));
            }

            V[a].incidence.pb(&V[b]);
            V[b].coincidence.pb(&V[a]);
        }

        if(prev != -1){
            V[prev].incidence.pb(&V[a]);
            V[a].coincidence.pb(&V[prev]);
        }
        if(s == "BRANCH" || s == "ACTION")
            prev = a;
        else
            prev = -1;
    }

    DFS();

    Dominators();

    cout << NaturalsWhereAreYou();

    return 0;
}
