//
// Created by alexey on 09.03.18.
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
    bool mark, red;
    vector <pair <int, bool>> incidence;
};

int main(){

    int nE, nV, i = 0, j = 0;
    int maxVert = 0, maxRib = 0;
    vector <int> maxVerts, subMaxVerts;

    cin >> nV >> nE;
    vector < Vertex > V(nV);
    int u, v;

    for(i = 0; i < nV; i++){
        V[i].mark = V[i].red = false;
        V[i].incidence = vector <pair <int, bool>> (0);
    }

    for(i = 0; i < nE; i++){
        cin >> u >> v;
        V[v].incidence.push_back(pair <int, bool> (u, false));
        if(u != v)
            V[u].incidence.push_back(pair <int, bool> (v, false));
    }

    queue <int> q;

    for(i = 0; i < nV; i++){
        if(V[i].mark)
            continue;
        int k = 0;
        subMaxVerts.clear();
        V[i].mark = true;
        q.push(i);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            k++;
            subMaxVerts.push_back(v);
            for(j = 0; j < V[v].incidence.size(); j++){
                int u = V[v].incidence[j].first;
                if(!V[u].mark){
                    V[u].mark = true;
                    q.push(u);
                }
            }
        }
        int e = 0;
        for(int v : subMaxVerts)
            e+=V[v].incidence.size();
        e/=2;
        //sort(subMaxVerts.begin(), subMaxVerts.end());
        if(k > maxVert){
            maxVert = k;
            maxRib = e;
            maxVerts = subMaxVerts;
        }
        else if(k == maxVert){
            if(e > maxRib){
                maxVert = k;
                maxRib = e;
                maxVerts = subMaxVerts;
            }
            else if(e == maxRib){
                sort(subMaxVerts.begin(), subMaxVerts.end());
                sort(maxVerts.begin(), maxVerts.end());
                if(subMaxVerts[0] < maxVerts[0]){
                    maxVert = k;
                    maxRib = e;
                    maxVerts = subMaxVerts;
                }
            }
        }
    }

    for(int v : maxVerts) {
        V[v].red = true;
        for(j = 0; j < V[v].incidence.size(); j++){
            V[v].incidence[j].second = true ;

            //V[j].incidence[v] = -1;
        }
    }

    cout << "graph {" << endl;
    for(i = 0; i < nV; i++){
        cout << "    " << i;
        if(V[i].red) cout << " [color = red]";
        cout << endl;
    }

    for(i = 0; i < nV; i++){

        for(j = 0; j < V[i].incidence.size(); j++){
            int u = V[i].incidence[j].first;
            if(u >= i){
                cout << "    " << i << " -- " << abs(u);
                if(V[i].incidence[j].second){
                    cout << " [color = red]";
                }
                cout << endl;
            }
        }
    }

    cout << "}" << endl;




    /*
    for(i = 0; i < nV; i++){
        for(j = 0; j < nV; j++){
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
     */

}