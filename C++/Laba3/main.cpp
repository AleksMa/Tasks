#include <bits/stdc++.h>
#include "formula.h"

using namespace std;




int main() {

    F <string, int> f(10);
    F <string, int> g("a");
    F <string, int> h(14);

    f+=h;

    cout << endl;

    cout << f;

    cout << endl;

    f*=g;
    cout << f;

    cout << endl;

    f.addMap(pair<string, int>("a", 5));

    cout << f();

    f += h;

    cout << endl;

    cout << f;

    cout << endl;

    //f.print();

    cout << f();

    cout << endl;

    cout << -f;

    f *= g;

    f = -f;

    cout << endl;

    cout << f;


    return 0;
}