//
// Created by alexey on 08.03.18.
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
    int comp, color; //WHITE = 0, GRAY = 1, BLACK = 2
    int parent;
};

int N = 0;

vector <int> compare (vector <int> team1, vector <int> team2){
    int k1 = team1.size(), k2 = team2.size();
    int comp = 0;
    if(k1 > N/2)
        return team2;
    else if(k2 > N/2)
        return team1;
    //?????????????????????
    if(k1 != k2){
        return (k1 > k2 ? team1 : team2);
    }

    sort(team1.begin(), team1.end());
    sort(team2.begin(), team2.end());

    for(int j = 0; j < min(k1, k2); j++){
        comp = team1[j] - team2[j];
        if(comp)
            break;
    }
    if(!comp){
        comp = k1 - k2;
    }

    return (comp < 0 ? team1 : team2);
}

vector <int> makeMyTeam(vector <int> team, vector <int> singleGraphs, vector <pair < vector <int>, vector <int> > > biGraphs, int i){
    if(i < biGraphs.size()){
        //cout << "LOL";
        //biGraphs[i].first
        vector <int> team1, team2;
        for(int j = 0; j < team.size(); j++) {
            team1.push_back(team[j]);
            team2.push_back(team[j]);
        }
        for(int j = 0; j < biGraphs[i].first.size(); j++) {
            team1.push_back(biGraphs[i].first[j]);
        }
        for(int j = 0; j < biGraphs[i].second.size(); j++) {
            team2.push_back(biGraphs[i].second[j]);
        }
        return compare(makeMyTeam(team1, singleGraphs, biGraphs, i+1),
                       makeMyTeam(team2, singleGraphs, biGraphs, i+1));
    }
    else{
        int j = 0;
        while(team.size() < N/2 && !singleGraphs.empty()){
            //cout << N << " ";
            team.push_back(singleGraphs[j++]);
        }
        return team;
    }
}

int main(){

    int n, i = 0, j = 0;
    char ch;
    cin >> n;
    N = n;
    bool E[n][n];
    vector <pair < vector <int>, vector <int> > > biGraphs(0);
    vector <int> singleGraphs (0);
    Vertex V[n];
    for(i = 0; i < n; i++){
        V[i].color = 0;
        for(j = 0; j < n; j++){
            cin >> ch;
            E[i][j] = (ch == '-' ? false : true);
        }
    }

    stack <int> s;
    for(i = 0; i < n; i++){
        if(V[i].color)
            continue;
        s.push(i);
        bool lonely = true;
        pair < vector <int>, vector <int> > biGraph;

        int k = -1;
        while(!s.empty()){
            int v = s.top();
            s.pop();
            if(!V[v].color){
                V[v].color = 1;
                k++;
                V[v].comp = (k%2 ? - (i + 1) : i + 1);
                s.push(v);
                for(int u = 0; u < n; u++){
                    if(!E[v][u])
                        continue;
                    lonely = false;
                    if(!V[u].color) {
                        s.push(u);
                    } else{
                        if(k % 2 == (V[u].comp > 0 ? 0 : 1)){
                            cout << "No solution";
                            return 0;
                        }
                    }
                }

                if(lonely) {
                    singleGraphs.push_back(v + 1);
                    break;
                }
                else{
                    if(k%2){
                        biGraph.second.push_back(v + 1);
                    } else{
                        biGraph.first.push_back(v + 1);
                    }
                }
            }
            else if(V[v].color == 1) {
                V[v].color = 2;
                k--;
            }
        }
        if(!lonely)
            biGraphs.push_back(biGraph);
    }

    vector <int> tmp(0);
    //string ans = "";
    vector <int> team = makeMyTeam(tmp, singleGraphs, biGraphs, 0);
    sort(team.begin(), team.end());

    for(int item : team){
        cout << item << " ";
    }




    /*

    for(int i = 0; i < biGraphs.size(); i++){
        for(int j = 0; j < biGraphs[i].first.size(); j++){
            cout << biGraphs[i].first[j] << " ";
        }
        cout << endl << "|||" << endl;
        for(int j = 0; j < biGraphs[i].second.size(); j++){
            cout << biGraphs[i].second[j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < singleGraphs.size(); i++){
        cout << singleGraphs[i] << " ";
    }


    cout << endl;

    */



    return 0;
}

