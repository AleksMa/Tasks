//Mamaev 35

#include <bits/stdc++.h>
#include "declaration.h"

using namespace std;

std::ostream& operator<< (std::ostream& os, StringSet& str){
    for(int i = 0 ; i < str.getN(); i++) {
        os << str[i] << (i == str.getN() - 1 ? "; " : ", ");
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, Matrix& matr){
    for(int i = 0 ; i < matr.getN(); i++) {
        for ( int j = 0 ; j < matr.getN() ; j++) {
            os << matr[i][j] << ' ';
        }
        os << std::endl;
    }
    return os;
}

/*
StringSet mullable(StringSet s1, StringSet s2){
    s1.mul(s2);
    return s1;
}
 */

void mWrite(Matrix m){
    string k[] = {"0"};
    m[0][0] = StringSet(k, 1);
    for(int i = 0; i < m.getN(); i++)
        cout << m[i][i] << " ";
    cout << endl;
}

int main() {

    /*

    Matrix m(1);
    Matrix &n = m;
    std::string *s = new std::string[3];
    s[0] = "lol";
    s[1] = "kek";
    s[2] = "ahha";
    StringSet str(s, 3);

    std::cout << str.n;
    cout << endl;
    std::cout << str;
    cout << endl;

    //str.mul(str);
    //str.orderedSet();

    StringSet S = mullable(str, str);

    std::cout << S;
    cout << endl;
    std::cout << str;

    */



    string s1[][1] = { {"a"}, {"b"}, {"c"}, {"d"} };

    Matrix m(2);

    m[0][0] = StringSet(s1[0], 1);

    StringSet &t = m.getLink(0, 1);
    t = StringSet(s1[1], 1);

    m[1][0] = StringSet(s1[2], 1);
    m[1][1] = StringSet(s1[3], 1);

    cout << m << endl;

    mWrite(m);

    cout << endl;

    m.square();
    m.square();

    cout << m;




    return 0;
}