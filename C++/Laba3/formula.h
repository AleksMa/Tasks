//
// Created by alexey on 11.05.18.
//

#ifndef LABA3_FORMULA_H
#define LABA3_FORMULA_H



#include <bits/stdc++.h>
using namespace std;


template <typename N, typename T>
class F{
private:
    class Lexem{
    public:
        string type;
        Lexem(T val){
            value = val;
            type = "value";
        }
        Lexem(N id){
            ident = id;
            type = "ident";
        }


        Lexem(string s){
            op = s;
            type = s;
        }

        friend ostream& operator<< (ostream& os, const Lexem &l){
            if(l.type == "value")
                cout << l.value;
            else if(l.type == "ident")
                cout << l.ident;
            else
                cout << l.op;
        }

        N ident;
        T value;
        string op;
    };

    vector <Lexem> V;
    map <N, T> assoc;
    int iter = 0;

    vector <Lexem> buff;
    Lexem temp;
    bool lt = false, att = false;
    string op;
    bool min = false;

public:
    F(T val){
        V.push_back(Lexem(val));
    }

    F(N ident){
        V.push_back(Lexem(ident));
    }


    void addMap(pair<N, T> p){
        assoc.insert(p);
    }

    F& operator+= (const F &other){
        this->V.push_back(Lexem("+"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator+ (const F &other) const{
        return F(*this) += other;
    }

    F& operator-= (const F &other){
        this->V.push_back(Lexem("-"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator- (const F &other) const{
        return F(*this) -= other;
    }

    F& operator*= (const F &other){
        this->V.push_back(Lexem("*"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator* (const F &other) const{
        return F(*this) *= other;
    }

    F& operator/= (const F &other){
        this->V.push_back(Lexem("/"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator/ (const F &other) const{
        return F(*this) /= other;
    }



    F& operator()(){
        iter = 0;
        for(int i = 0; i < V.size(); i++){
            if(V[i].type == "ident"){
                if(assoc.find(V[i].ident) != assoc.end()){
                    V[i].type = "value";
                    V[i].value = assoc[V[i].ident];
                }
            }
        }
        T parse = arith_expr();
        if(att){
            if(buff.size())
                buff.push_back(Lexem(op));
            buff.push_back(parse);
        }
        V = buff;
        buff.clear();

        return *this;
    }


    friend ostream& operator<< (ostream& os, const F &f){
        for(int i = 0 ; i < f.V.size(); i++) {
            cout << f.V[i];
        }
        //return os;
    }

    T arith_expr(){
        T acc = term();
        return add(acc);
    }

    T add(T acc){
        if(iter >= V.size())
            return acc;
        if(V[iter].type == "+"){
            iter++;
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("+"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return add(0);
            }
            att = true;
            op = "+";
            return add(acc + term());
        }
        else if(V[iter].type == "-"){
            iter++;
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("-"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return add(0);
            }
            att = true;
            op = "-";
            return add(acc - term());
        }
    }

    T term(){
        T acc = factor(false);
        return (lt ? mul(1) : mul(acc));
    }

    T mul(T acc){
        if(iter >= V.size())
            return acc;
        if(V[iter].type == "*"){
            iter++;
            T tm = term();
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("*"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return mul(1);
            }
            att = true;
            op = "*";
            return mul(acc * tm);
        }
        else if(V[iter].type == "/"){
            iter++;
            T tm = term();
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("/"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return mul(1);
            }
            att = true;
            op = "/";
            return mul(acc / term());
        } else {
            return acc;
        }
    }

    T factor(bool minus){

        if(iter >= V.size())
            return 0;

        if(V[iter].type == "ident"){
            if(minus){
                //iter++;
                //buff.push_back(Lexem("-"));
                temp = V[iter++];
                min = true;
                return 0;
            }
            else
                temp = V[iter++];
            lt = true;
            return 0;
        }
        else if (V[iter].type == "value"){
            if(minus)
                return -1 * V[iter++].value;
            return V[iter++].value;
        }
        else if(V[iter].type == "("){
            iter++;
            T acc = factor(minus);
            iter++;
            return acc;
        }
        else if(V[iter].type == "-"){
            iter++;
            return factor(true);
        }
    }


};

//------------------------------------------------------------------

template <typename T>
class F <string, T>{
private:
    class Lexem{
    public:
        string type;
        Lexem(T val){
            value = val;
            type = "value";
        }
        Lexem(){
            type = "";
        }
        Lexem(string id){
            if(id == "+" || id == "-" || id == "*" || id == "/" || id == "(" || id == ")"){
                type = op = id;
            }
            else{
                ident = id;
                type = "ident";
            }
        }

        friend ostream& operator<< (ostream& os, const Lexem &l){
            if(l.type == "value")
                cout << l.value;
            else if(l.type == "ident")
                cout << l.ident;
            else
                cout << l.op;
        }

        string ident;
        T value;
        string op;
    };


    map <string, T> assoc;
    int iter = 0;

    vector <Lexem> buff;
    Lexem temp;
    bool lt = false, att = false;
    string op;
    bool min = false;

public:
    vector <Lexem> V;

    F(T val){
        V.push_back(Lexem(val));
    }

    F(string ident){
        V.push_back(Lexem(ident));
    }

    void addMap(pair<string, T> p){
        assoc.insert(p);
    }

    F& operator+= (const F &other){
        this->V.push_back(Lexem("+"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator+ (const F &other) const{
        return F(*this) += other;
    }

    F& operator-= (const F &other){
        this->V.push_back(Lexem("-"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator- (const F &other) const{
        return F(*this) -= other;
    }

    F& operator*= (const F &other){
        this->V.push_back(Lexem("*"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator* (const F &other) const{
        return F(*this) *= other;
    }

    F& operator/= (const F &other){
        this->V.push_back(Lexem("/"));
        for(int i = 0; i < other.V.size(); i++)
            this->V.push_back(other.V[i]);
        return *this;
    }

    const F operator/ (const F &other) const{
        return F(*this) /= other;
    }

    /*

    F operator- (){
        F t = *this;
        vector <Lexem> v;
        if(V[0].type == "-"){
            for(int i = 2; i < V.size() - 1; i++)
                v.push_back(V[i]);
        } else {
            v.push_back(Lexem("-"));
            v.push_back(Lexem("("));
            for(int i = 0; i < V.size(); i++)
                v.push_back(V[i]);
            v.push_back(Lexem(")"));
        }
        t.V = v;
        return t;
    }

     */



    F operator- (){
        F t = *this;
        vector <Lexem> v;
        int i = 0;
        if(t.V[i].type == "-")
            i++;
        else
            v.push_back(Lexem("-"));

        for(; i < V.size(); i++){
            bool fl = false;
            Lexem temp, next;
            if(V[i].type != "ident" && V[i].type != "value"){
                if(V[i].type == "-")
                    temp.type = temp.op = "+";
                else if(V[i].type == "+")
                    temp.type = temp.op = "-";
                else{
                    temp = V[i];
                    //next = V[i+1];
                    fl = true;
                }
            }
            else
                temp = V[i];
            v.push_back(temp);
            if(fl){
                v.push_back(Lexem("("));
                v.push_back(Lexem("-"));
                v.push_back(V[++i]);
                v.push_back(Lexem(")"));
            }
        }
        t.V = v;
        return t;
    }


    F& operator()(){
        iter = 0;
        for(int i = 0; i < V.size(); i++){
            if(V[i].type == "ident"){
                if(assoc.find(V[i].ident) != assoc.end()){
                    V[i].type = "value";
                    V[i].value = assoc[V[i].ident];
                }
            }
        }
        T parse = arith_expr();
        if(att){
            if(buff.size())
                buff.push_back(Lexem(op));
            buff.push_back(parse);
        }
        V = buff;
        buff.clear();

        return *this;
    }


    friend ostream& operator<< (ostream& os, const F &f){
        for(int i = 0 ; i < f.V.size(); i++) {
            cout << f.V[i];
        }
        //return os;
    }

    T arith_expr(){
        T acc = term();
        return add(acc);
    }

    T add(T acc){
        if(iter >= V.size())
            return acc;
        if(V[iter].type == "+"){
            iter++;
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("+"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return add(0);
            }
            att = true;
            op = "+";
            return add(acc + term());
        }
        else if(V[iter].type == "-"){
            iter++;
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("-"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return add(0);
            }
            att = true;
            op = "-";
            return add(acc - term());
        }
    }

    T term(){
        T acc = factor(false);
        return (lt ? mul(1) : mul(acc));
    }

    T mul(T acc){
        if(iter >= V.size())
            return acc;
        if(V[iter].type == "*"){
            iter++;
            T tm = term();
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("*"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return mul(1);
            }
            att = true;
            op = "*";
            return mul(acc * tm);
        }
        else if(V[iter].type == "/"){
            iter++;
            T tm = term();
            if(lt){
                buff.push_back(Lexem(acc));
                buff.push_back(Lexem("/"));
                if(min){
                    buff.push_back(Lexem("-"));
                    buff.push_back(Lexem("("));
                }
                buff.push_back(temp);
                if(min){
                    buff.push_back(Lexem(")"));
                    min = false;
                }
                lt = att = false;
                return mul(1);
            }
            att = true;
            op = "/";
            return mul(acc / term());
        } else {
            return acc;
        }
    }

    T factor(bool minus){

        if(iter >= V.size())
            return 0;

        if(V[iter].type == "ident"){
            if(minus){
                //iter++;
                //buff.push_back(Lexem("-"));
                temp = V[iter++];
                min = true;
                return 0;
            }
            else
                temp = V[iter++];
            lt = true;
            return 0;
        }
        else if (V[iter].type == "value"){
            if(minus)
                return -1 * V[iter++].value;
            return V[iter++].value;
        }
        else if(V[iter].type == "("){
            iter++;
            T acc = factor(minus);
            iter++;
            return acc;
        }
        else if(V[iter].type == "-"){
            iter++;
            return factor(true);
        }
    }



};



#endif //LABA3_FORMULA_H
