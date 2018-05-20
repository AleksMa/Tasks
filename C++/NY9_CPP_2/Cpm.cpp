
/*
 * mama-grammatica
 *

<program> ::= <sentence> <program-tail>.
<program-tail> ::= /n <sentence> <program-tail> | .
<sentence> ::= <work> <sentence-tail>
<sentence-tail> ::= < <work> <sentence-tail> | .

<work> ::= <ident> <ident-tail> .
<ident-tail> ::= ( <number> ) | .

 */

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
typedef vector<vector<string>> VVS;
typedef vector<string> VS;
typedef vector<int> VI;
typedef long double ld;
typedef unsigned uint;

const int inf = INT_MAX;
const ll linf = LLONG_MAX;
const int mod = 1000007;

struct Vertex{
    map <string, int> incidence;
    int dist;
    int w;
    int mark = 0;
    set <string> parents;
    bool in = false;
};

queue <string> lexems;
map <string, Vertex> V;
vector <string> W;
int k = -2, lastChanged = 0, iter = 0;

void tokenize(string src){
    int i = 0;

    while(i < src.length()){
        if(isdigit(src[i])){
            int k = i++;
            while(i < src.length() && isdigit(src[i]))
                i++;
            lexems.push(src.substr(k, i - k));
        }
        else if(isalpha(src[i])){
            int k = i++;
            while(i < src.length() && isalnum(src[i]))
                i++;

            lexems.push(src.substr(k, i - k));
        }
        else if(src[i] == ' ' || src[i] == '\n')
            i++;
        else{
            lexems.push(string{src[i++]});
        }
    }
}

void program();
void program_tail();
void sentence();
void sentenceTail(string vertex);
string work(string vertex);
void identTail(string ident);

void program(){
    sentence();
    program_tail();
}

void program_tail(){
    if(!lexems.empty()){
        lexems.pop();
        sentence();
        program_tail();
    }
}

void sentence(){

    string t = work("");
    sentenceTail(t);
}

void sentenceTail(string vertex){
    if(!lexems.empty() && lexems.front() == "<"){
        lexems.pop();
        string tt = work(vertex);
        sentenceTail(tt);
    }
}

string work(string vertex){
    string ident = lexems.front();
    lexems.pop();
    identTail(ident);
    if(vertex != ""){
        V[vertex].incidence.insert(PSI(ident, 0));
        V[ident].in = true;
    }

    return ident;
}

void identTail(string ident){
    if(!lexems.empty() && lexems.front() == "("){
        lexems.pop();
        int num = stoi(lexems.front());
        lexems.pop();
        Vertex v;
        v.w = -num;
        if(ident != "")
            V.insert(pair<string, Vertex>(ident, v));
        lexems.pop();
    }
}


void VisitBlueVertex(string v){

    V[v].mark = -1;
    for (PSI u : V[v].incidence)
    {
        V[v].incidence[u.first] = -1;
        if(V[u.first].mark >= 0)
            VisitBlueVertex(u.first);
    }
}

void VisitVertex(string v){
    V[v].mark = 1;
    for (PSI u : V[v].incidence)
    {
        if(!V[u.first].mark)
            VisitVertex(u.first);
        else if(V[u.first].mark == 1){
            V[u.first].mark = -1;
            for(PSI s : V[u.first].incidence)
                V[u.first].incidence[s.first] = -1;
        }
        else if(V[u.first].mark == -1)
            VisitBlueVertex(u.first);
    }
    if(V[v].mark > 0)
        V[v].mark = 2;
    W.pb(v);
}

void DFS(){
    for (auto it = V.begin(); it != V.end(); it++) {
        it->second.mark = 0;
    }
    for (auto it = V.begin(); it != V.end(); it++){
        if(!it->second.mark)
            VisitVertex(it->first);
    }
}

void Relax(string v, string u, int w);

void VisitVertex2(string v){
    V[v].mark = 1;
    for (PSI u : V[v].incidence)
    {
        if(!V[u.first].mark)
            VisitVertex(u.first);
        else if(V[u.first].mark == 1){
            V[u.first].mark = -1;
            for(PSI s : V[u.first].incidence)
                V[u.first].incidence[s.first] = -1;
        }
        else if(V[u.first].mark == -1)
            VisitBlueVertex(u.first);
    }
    if(V[v].mark > 0)
        V[v].mark = 2;
}

void DFS2(){
    for (auto it = V.begin(); it != V.end(); it++)
    {
        if(it->second.mark != -1)
            it->second.mark = 0;
    }
    for (auto it = V.begin(); it != V.end(); it++){
        if(!it->second.mark)
            VisitVertex2(it->first);
    }
}

int minn = inf;
set <string> points;

void Relax(string v, string u, int w){
    if(V[v].dist == inf || w == inf)
        return;

    if(V[v].dist + w < V[u].dist){
        V[u].parents.clear();
        V[u].dist = V[v].dist + w;
        V[u].parents.insert(v);
    }
    else if(V[v].dist + w == V[u].dist){
        V[u].parents.insert(v);
    }

    if(V[u].dist < minn){
        if(lastChanged != iter)
            k--;
        minn = V[u].dist;
        points.clear();
        points.insert(u);
        lastChanged = iter;
    }
    else if(V[u].dist == minn){
        points.insert(u);
    }
}

// Из Кормена :)
void DagShortestPath(string s) {
    for (auto it = V.begin(); it != V.end(); it++) {
        it->second.dist = inf;
        if (it->first == s)
            it->second.dist = it->second.w;
    }
    for (int i = W.size() - 1; i >= 0; i--) {
        string v = W[i];
        if (V[v].mark == -1)
            continue;
        for (PSI u : V[v].incidence) {
            if (V[u.first].mark == -1)
                continue;
            Relax(v, u.first, V[u.first].w);
        }
    }

    if (V[s].dist < minn) {
        if (lastChanged != iter)
            k--;
        minn = V[s].dist;
        points.clear();
        points.insert(s);
        lastChanged = iter;
    } else if (V[s].dist == minn) {
        points.insert(s);
    }
}


void Mark(string s){

    for(string st : V[s].parents){
        V[st].mark = k;
        V[st].incidence[s] = k;
        if(V[st].in){
            Mark(st);
        }
    }
}

int main(){

    string assoc[] = {"blue", "red"};

    string s = "", a = "";

    while(!cin.eof()){
        getline(cin, a);
        if(a != ""){
            s += a;
        }
    }

    tokenize(s);

    program();

    DFS();
    DFS2();

   for (auto it = V.begin(); it != V.end(); it++){
        if(!it->second.in && it->second.mark != -1){
            //cout << "kek" << endl;
            DagShortestPath(it->first);

            for(string s : points){
                V[s].mark = k;
                Mark(s);
            }
            points.clear();


        }
        iter++;
    }

    cout << "digraph { " << endl;

    for (auto it = V.begin(); it != V.end(); it++)
    {
        cout << "  " << it->first << " [label = \"" << it->first << "(" << -it->second.w << ")\"";
        if(it->second.mark == -1 || it->second.mark == k)
            cout << ", color = " << assoc[(it->second.mark == - 1 ? 0 : 1)];
        cout << "]" << endl;
    }

    for (auto it = V.begin(); it != V.end(); it++)
    {
        for (PSI s: it->second.incidence)
        {
            cout << "  " << it->first << " -> " << s.first;
            if(s.second == -1 || s.second == k)
                cout << " [color = " << assoc[(s.second == - 1 ? 0 : 1)] << "]";
            cout << endl;
        }
    }
    cout << "}";


    return 0;
}
