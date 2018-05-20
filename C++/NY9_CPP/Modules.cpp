//
// Created by alexey on 17.04.18.
//

/*
 * mama-grammatica
 *

<program> ::= <function> <program-tail>.
<program-tail> ::= <function> <program-tail> | .
<function> ::= <ident> ( <formal-args-list> ) := <expr> ; .

<formal-args-list> ::= <ident-list> | .
<ident-list> ::= <ident> <ident-list-tail> .
<ident-list-tail> ::= , <ident-list> | .
<expr> ::=
    <comparison_expr> <expr_tail> .
<expr-tail> ::= ? <comparison_expr> : <expr> | .
<comparison_expr> ::=
    <arith_expr> <comp-tail>.
<comp-tail> ::= <comparison_op> <arith_expr> | .
<comparison_op> ::= = | <> | < | > | <= | >= .

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
    | <ident> <factor-tail>
    | ( <expr> )
    | - <factor>.
<factor-tail> ::= ( <actual_args_list> ) | .
<actual_args_list> ::= <expr-list> | .
<expr-list> ::= <expr> <expr-list-tail>.
<expr-list-tail> ::= , <expr-list> | .

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
    int index, k = -1;
    bool declared = false;
    VI incidence;
    VS args;
    int T1, T2, comp, low;
};

queue <string> lexems;
map <string, int> funcs;
vector<Vertex> V;
int I = 0;
int T = 1, K = 1;


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
        else if(src[i] == '<' && i+1 < src.length() && (src[i+1] == '>' || src[i+1] == '='))
            lexems.push(string{src[i++], src[i++]});
        else if(src[i] == '>' && i+1 < src.length() && src[i+1] == '=')
            lexems.push(string{src[i++], src[i++]});
        else if(src[i] == ':' && i+1 < src.length() && src[i+1] == '=')
            lexems.push(string{src[i++], src[i++]});
        else{
            lexems.push(string{src[i++]});
        }
    }
}

void program();
void program_tail();
void func();
void formal_args_list(string funcName);
void ident_list(string funcName);
void ident_list_tail(string funcName);
void expr(string funcName);
void expr_tail(string funcName);
void comp_expr(string funcName);
void comp_tail(string funcName);
void arith_expr(string funcName);
void add(string funcName);
void term(string funcName);
void mul(string funcName);
void factor(string funcName);
void factor_tail(string funcName, string ident);
void actual_args_list(string funcName, string mainFunc);
int expr_list(string funcName, string mainFunc);
int expr_list_tail(string funcName, string mainFunc);


void program(){
    func();
    program_tail();

    for(Vertex v : V)
        if(!v.declared){
            throw "undefined function";
        }

}

void program_tail(){
    if(!lexems.empty()){
        func();
        program_tail();
    }
}

void func(){
    string ident = lexems.front();
    if(!isalpha(ident[0])){
        throw "illegal ident";
    }
    //ЧТО_ТО СДЕЛАТЬ С ИДЕНT
    if(funcs.find(ident) == funcs.end()){
        funcs.insert(pair<string, int>(ident, I++));
        Vertex v;
        V.pb(v);
    }
    V[funcs[ident]].declared = true;

    lexems.pop();
    if(lexems.front() != "(")
        throw "expected \"(\"";
    lexems.pop();

    formal_args_list(ident);

    if(V[funcs[ident]].k != -1 && V[funcs[ident]].args.size() != V[funcs[ident]].k){
        throw "incorrect number of args";
    }

    if(lexems.front() != ")")
        throw "expected \")\"";
    lexems.pop();
    if(lexems.front() != ":=")
        throw "expected \":=\"";
    lexems.pop();
    expr(ident);
    if(lexems.front() != ";")
        throw "expected \";\"";
    lexems.pop();
}

void formal_args_list(string funcName){
    if(lexems.front() != ")")
        ident_list(funcName);
}

void ident_list(string funcName){
    string ident = lexems.front();
    if(!isalpha(ident[0])){
        throw "illegal ident";
    }
    lexems.pop();
    V[funcs[funcName]].args.push_back(ident);

    ident_list_tail(funcName);
}

void ident_list_tail(string funcName){
    if(lexems.front() != ")"){

        if(lexems.front() != ","){
            throw "expected \",\"";
        }

        lexems.pop();
        ident_list(funcName);
    }
}

void expr(string funcName){
    comp_expr(funcName);
    expr_tail(funcName);
}

void expr_tail(string funcName){
    if(lexems.front() == "?"){
        lexems.pop();
        comp_expr(funcName);
        if(lexems.front() != ":")
            throw "expected \":\"";
        lexems.pop();
        expr(funcName);
    }
}

void comp_expr(string funcName){
    arith_expr(funcName);
    comp_tail(funcName);
}

void comp_tail(string funcName){
    string t = lexems.front();
    if(t == "=" || t == "<>" || t == "<" || t == ">" || t == "<=" || t == ">="){
        lexems.pop();
        arith_expr(funcName);
    }
}

void arith_expr(string funcName){
    term(funcName);
    add(funcName);
}

void add(string funcName){
    if(lexems.front() == "+" || lexems.front() == "-"){
        lexems.pop();
        term(funcName);
        add(funcName);
    }
}

void term(string funcName){
    factor(funcName);
    mul(funcName);
}

void mul(string funcName){
    if(lexems.front() == "*" || lexems.front() == "/"){
        lexems.pop();
        factor(funcName);
        mul(funcName);
    }
}

void factor(string funcName){

    string t = lexems.front();
    lexems.pop();

    if(isalpha(t[0])){
        factor_tail(funcName, t);
    }
    else if(t == "("){
        expr(funcName);
        if(lexems.front() != ")")
            throw "expected \")\"";
        lexems.pop();
    }
    else if(t == "-")
        factor(funcName);
    else if(!isdigit(t[0]))
        throw "unexpected token";
}

void factor_tail(string funcName, string ident){

    if(lexems.empty())
        throw "expected smth";

    if(lexems.front() == "("){
        if(funcs.find(ident) == funcs.end()){
            funcs.insert(pair<string, int>(ident, I++));
            Vertex v;
            V.pb(v);
        }
        V[funcs[funcName]].incidence.pb(funcs[ident]);
        lexems.pop();
        actual_args_list(ident, funcName);
        if(lexems.front() != ")")
            throw "expected \")\"";
        lexems.pop();
    }
    else{
        bool var = false;
        for(string vs : V[funcs[funcName]].args){
            if(ident == vs) {
                var = true;
                break;
            }
        }
        if(!var){
            throw "unexpected token (variable)";
        }

    }
}

void actual_args_list(string funcName, string mainFunc){
    if(lexems.front() != ")"){
        int k = expr_list(funcName, mainFunc) + 1;
        if(V[funcs[funcName]].declared && k != V[funcs[funcName]].args.size()){
            throw "incorrect number of args";
        }
        else if(!V[funcs[funcName]].declared)
            V[funcs[funcName]].k = k;
    }
}

int expr_list(string funcName, string mainFunc){
    expr(mainFunc);
    return expr_list_tail(funcName, mainFunc);
}

int expr_list_tail(string funcName, string mainFunc){
    if(lexems.front() == ","){
        lexems.pop();
        return 1 + expr_list(funcName, mainFunc);
    }
    else return 0;
}

void VisitVertexTarjan(int i, stack <int> *S){
    V[i].T1 = V[i].low = T++;
    (*S).push(i);
    for(int u : V[i].incidence){
        if(V[u].T1 == 0)
            VisitVertexTarjan(u, S);
        if(V[u].comp == 0 && V[i].low > V[u].low)
            V[i].low = V[u].low;
    }
    int u;
    if(V[i].T1 == V[i].low) {
        do {
            u = (*S).top();
            (*S).pop();
            V[u].comp = K;
        } while (i != u);
        K++;
    }
}

void Tarjan(){

    for(int i = 0; i < V.size(); i++){
        V[i].comp = V[i].T1 = 0;
    }

    stack <int> S;

    for(int i = 0; i < V.size(); i++){
        if(!V[i].T1)
            VisitVertexTarjan(i, &S);
    }

}


int main(){

    string s = "", a = "";

    while(!cin.eof()){
        getline(cin, a);
        s += a + "\n";
    }

    tokenize(s);

    try{
        program();
        Tarjan();
        cout << K - 1;
    }
    catch(const char* msg){
        cout << "error";
    }
    return 0;
}