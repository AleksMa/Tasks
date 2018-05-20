
/*
 * mama-grammatica
 *

<program> ::= <function> <program-tail>.
<program-tail> ::= /n <function> <program-tail> | .
<function> ::= <left-vars> = <arith_exprs> .

<left-vars> ::= <ident> <left-vars-tail> .
<left-vars-tail> ::= , <left-vars> | .

<arith_exprs> ::= <arith_expr> <arith_expr_tail> .
<arith_expr_tail> ::= , <arith_exprs> | .

<arith_expr> ::= <term> <add>.
<add> ::=
    + <term> <add>
    | - <term> <add>
    | .
<term> ::= <factor> <mul>.
<mul> ::=
    * <factor> <mul>
    | / <factor> <mul>
    | .
<factor> ::=
    <number>
    | <ident>
    | ( <expr> )
    | - <factor>.

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
map <string, int> args;
vector<Vertex> V;
string acc = "";
int I = 0;

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
void func();
void left_vars();
void left_vars_tail();

void arith_exprs();
void arith_exprs_tail();
void arith_expr();
void add();
void term();
void mul();
void factor();

void program(){
    func();
    program_tail();
}

void program_tail(){
    if(!lexems.empty()){
        if(lexems.front() != "\n")
            throw "syntax error";
        lexems.pop();
        func();
        program_tail();
    }
}

void func(){

    left_vars();

    if(lexems.empty() || lexems.front() != "="){
        throw "syntax error";
    }

    lexems.pop();
    arith_exprs();
    I++;
}

void left_vars(){
    if(lexems.empty())
        throw "syntax error";
    string ident  = lexems.front();
    if(!isalpha(ident[0]))
        throw "syntax error";
    lexems.pop();
    if(args.find(ident) == args.end()){
        args.insert(pair<string, int>(ident, I));
    } else
        throw "syntax error";
    V[I].args.pb(ident);
    V[I].k++;
    left_vars_tail();
}

void left_vars_tail(){
    if(!lexems.empty() && lexems.front() == ","){
        lexems.pop();
        left_vars();
    }
}

void arith_exprs(){
    arith_expr();
    V[I].l++;
    arith_exprs_tail();
}

void arith_exprs_tail(){
    if(!lexems.empty() && lexems.front() == ","){
        lexems.pop();
        arith_exprs();
    }
    else{
        if(V[I].k != V[I].l)
            throw "syntax error";
    }
}

void arith_expr(){
    term();
    add();
}

void add(){
    if(!lexems.empty() && (lexems.front() == "+" || lexems.front() == "-")){
        lexems.pop();
        term();
        add();
    }
}

void term(){
    factor();
    mul();
}

void mul(){
    if(!lexems.empty() && (lexems.front() == "*" || lexems.front() == "/")){
        lexems.pop();
        factor();
        mul();
    }
}

void factor(){
    if(lexems.empty())
        throw "syntax error";
    string t = lexems.front();
    lexems.pop();

    if(isalpha(t[0])){
        V[I].exprs.pb(t);
    }
    else if(t == "("){
        arith_expr();
        if(lexems.empty() || lexems.front() != ")")
            throw "syntax error";
        lexems.pop();
    }
    else if(t == "-")
        factor();
    else if(!isdigit(t[0]))
        throw "syntax error";
}

void VisitVertex(int v){
    V[v].mark = 1;
    for (auto it = V[v].incidence.begin(); it != V[v].incidence.end(); ++it)
    {
        int u = *it;
        if(!V[u].mark)
            VisitVertex(u);
        else if(V[u].mark == 1)
            throw "cycle";
    }
    V[v].mark = 2;
    acc += V[v].form + "\n";
}

void DFS(){
    for(int v = 0; v < V.size(); v++)
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

    try{
        program();
        for(int v = 0; v < V.size(); v++){
            for(string s : V[v].exprs){
                if(args.find(s) != args.end())
                    V[v].incidence.insert(args.find(s)->second);
                else
                    throw "syntax error";
            }
        }

        DFS();
        cout << acc;
    }
    catch(const char* msg){
        cout << msg;
    }

    return 0;
}