
/*
 * mama-grammatica
 *

<program> ::= <sentence> <program-tail>.
<program-tail> ::= /n <sentence> <program-tail> | .
<sentence> ::= <work> < <work> <sentence-tail>
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
typedef pair<ull, ull> PULL;
typedef vector <string> VS;
typedef vector<int> VI;
typedef long double ld;
typedef unsigned uint;

const int inf = INT_MAX;
const ll linf = LLONG_MAX;
const int mod = 1000007;

struct Vertex{
    int index, k = 0, l = 0;
    bool declared = false;
    set <int> incidence;
    VS args;
    VS exprs;
    int T1, T2, comp, low;
    string form;
    int mark;
};

queue <string> lexems;
map <string, Vertex> V;
//vector<Vertex> V;
//string acc = "";
//int I = 0;

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
        else if(src[i] == ' ')
            i++;
        else{
            lexems.push(string{src[i++]});
        }
    }
}

void program();
void program_tail();
void sentence();
void sentenceTail();
string work();
void identTail(string ident);

void program(){
    sentence();
    program_tail();
}

void program_tail(){
    if(!lexems.empty()){
        /*
        if(lexems.front() != "\n")
            throw "syntax error";
            */
        lexems.pop();
        sentence();
        program_tail();
    }
}

void sentence(){

    string t = work();

    lexems.pop();

    string tt = work(t);
    sentenceTail();
}

void sentenceTail(){
    if(lexems.front() == "<"){
        lexems.pop();
        work();
        sentenceTail();
    }
}

string work(string vertex){
    string ident = lexems.front();
    identTail(ident);
    V[ident]->second.incidence.pb(vertex);
    return ident;
}

void identTail(string ident){
    if(lexems.front == "("){
        lexems.pop();
        int num = lexems.front;
        lexems.pop();
        lexems.pop();
    }
}

VisitBlueVertex(int v){

}

void VisitVertex(int v){
    V[v].mark = 1;
    for (auto it = V[v].incidence.begin(); it != V[v].incidence.end(); ++it)
    {
        int u = *it;
        if(!V[u].mark)
            VisitVertex(u);
        else if(V[u].mark == 1)
            V[u].mark = -1;
    }
    V[v].mark = 2;
    acc += V[v].form + "\n";
}

void DFS(){
    for(int v = 0; v < V.size(); v++)
        if(V[v].mark != -1)
            V[v].mark = 0;
    for(int v = 0; v < V.size(); v++){
        if(!V[v].mark)
            VisitVertex(v);
    }
}

int main(){

    string s = "", a = "";
    getline(cin, s);
    Vertex v;
    v.form = s;
    V.pb(v);

    while(!cin.eof()){
        getline(cin, a);
        if(a != ""){
            Vertex v;
            v.form = a;
            V.pb(v);
            s += "\n" + a;
        }
    }

    tokenize(s);


    program();
    DFS();
    cout << acc;

    return 0;
}