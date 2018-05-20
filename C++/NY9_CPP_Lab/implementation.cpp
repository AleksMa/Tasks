//Mamaev 35

#include <bits/stdc++.h>
#include "declaration.h"

using namespace std;

StringSet::StringSet() {
    a = new string[11];
}

StringSet::StringSet(int n) {
    a = new string[n];
}

StringSet::~StringSet() {
    delete [] a;
}

StringSet::StringSet(string *a, int n) {
    //this->a = a;
    this->a = new string[n];
    copy(a, a + n, this->a);
    this->n = n;
    this->orderedSet();
}

StringSet::StringSet(const StringSet &str) {
    n = str.n;
    a = new string[n];
    copy(str.a, str.a + n, a);
}

string& StringSet::operator[](int i) {
    return a[i];
}

StringSet& StringSet::operator= (StringSet src){
    swap(n, src.n);
    swap(a, src.a);
    return *this;
}

StringSet StringSet::add(StringSet &str) {
    string *s = new string [n + str.n];
    copy(a, a + n, s);
    copy(str.a, str.a + str.n, s + n);
    swap(a, s);
    //a = s;
    n += str.n;
    this->orderedSet();
    return *this;
}

StringSet StringSet::mul(StringSet &str) {
    StringSet src(n * str.n);
    //string *s = new string[n * str.n];
    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < str.n; j++){
            src.a[k++] = a[i]+str.a[j];
        }
    }
    n*=str.n;
    swap(this->a, src.a);

    this->orderedSet();
    return *this;
}


void StringSet::orderedSet() {
    sort(a, a + n);
    int k = 0;
    for(int i = 0; i < n; i++){
        k = 0;
        int l = i;
        while(i + k < n - 1 && a[i + k] == a[i + k + 1]){
            k++;
        }
        copy(a + l + k, a + n, a + l);
        /*
        for(int j = l; j < n - k; j++){
            a[j] = a[]
        }*/
        /*
        string *s = new string [n - k];
        copy(a, a + n - k, s);
        swap(a, s);*/
        n -= k;
    }
}

size_t StringSet::getN(){
    return n;
}

Matrix::Matrix(size_t n) : n(n) {
    a = new StringSet* [n];
    for(int i = 0; i < n; i++)
        a[i] = new StringSet[n];
}

Matrix::~Matrix() {


    for(int i = 0; i < n; i++){
        delete [] a[i];
    }


    delete [] a;

}

Matrix::Matrix(const Matrix &m): n(m.n){
    a = new StringSet* [n];
    for(int i = 0; i < n; i++){
        a[i] = new StringSet[n];
        for(int j = 0; j < n; j++)
            a[i][j] = m.a[i][j];
    }

}

Matrix& Matrix::operator= (Matrix m) {
    swap(n, m.n);
    swap(a, m.a);
    return *this;
}

StringSet& Matrix::getLink(int i, int j){
    return this->a[i][j];
}

/*
StringSet mullable(StringSet s1, StringSet s2){
    s1.mul(s2);
    return s1;
}

StringSet addable(StringSet s1, StringSet s2){
    s1.add(s2);
    return s1;
}
 */

void Matrix::square(){

    Matrix t = *this;

    /*

    Matrix t(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            t.a[i][j] = a[i][j];
    }
     */



    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            a[i][j] = t[i][0];
            a[i][j].mul(t[0][j]);
            for(int k = 1; k < n; k++){
                StringSet S = t[i][k];
                S.mul(t[k][j]);
                a[i][j].add(S);
            }
        }
    }
}

size_t Matrix::getN(){
    return n;
}


