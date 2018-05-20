#include <bits/stdc++.h>
#include "pqueue.h"

using namespace std;


int main(int argc, char **argv) {

    PQueue <string, 10> Q;

    Q.insert("aaa");
    Q.insert("bbb");
    Q.insert("aba");
    Q.insert("abc");

    cout << Q.extractMax() << endl;
    cout << Q.extractMin() << endl;
    Q.insert("acab");
    cout << Q.extractMin() << endl;
    cout << Q.extractMax() << endl;

    //Q.deleteEverything();

    PQueue <bool, 10> spec;

    spec.insert(true);
    spec.insert(true);
    spec.insert(true);

    cout << spec.extractMin() << " " << spec.extractMax() << endl;

    spec.insert(false);

    cout << spec.extractMin() << " " << spec.extractMax();


    return 0;
}
