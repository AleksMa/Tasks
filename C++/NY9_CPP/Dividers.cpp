//
// Created by alexey on 19.02.18.
//

#include <bits/stdc++.h>

typedef unsigned uint;

using namespace std;

int main(int argc, char **argv) {

    uint number;
    cin >> number;
    vector<uint> Arr;
    uint i = 1;
    for(; i <= sqrt(number); i++){
        if(number % i == 0){
            Arr.push_back(i);
        }
    }
    uint size = Arr.size();
    for(int j = (i-1 == sqrt(number)?size-2: size-1); j >= 0; j--){
        //cout << "lol " << j << endl;
        if(number == 1)
            break;
        Arr.push_back(number/Arr[j]);
        //cout << Arr[j] << " " << number/Arr[j] << endl;
        //cout << Arr.size() << endl;
    }



    uint n = Arr.size() + 1;
    uint **Matrixx = (uint**)malloc(n*sizeof(uint*));
    for(int i = 0; i<n; i++){
        Matrixx[i] = (uint*)malloc(n*sizeof(uint));
    }


    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Matrixx[i][j] = 0;
        }
    }

    for(int i = 1; i < n; i++){
        Matrixx[0][i] = Arr[i-1];
        Matrixx[i][0] = Arr[i-1];
    }

    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            if(Matrixx[0][i] % Matrixx[j][0] == 0 && i!=j)
                Matrixx[i][j] = 1;
        }
    }

    for(int i = n-1; i > 0; i--){
        for(int j = n-1; j > 0; j--){
            if(Matrixx[i][j] == 1){
                for(int k = j; k > 0; k--){
                    if(Matrixx[j][k] == 1){
                        if(Matrixx[i][k] == 1)
                            Matrixx[i][k] = 0;
                    }
                }
            }
        }
    }

    /*
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << Matrixx[i][j] << " ";
        }
        cout << endl;
    }
    */

    cout << "graph {" << endl;
    for(int i = 0; i < n-1; i++){
        cout << "    " << Arr[i] << endl;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != 0 && j != 0 && Matrixx[i][j] == 1)
                cout << "    " << Arr[i-1] << " -- " << Arr[j-1] << endl;
        }
    }
    cout << "}";
    for(int i = 0; i < n; i++){
        free(Matrixx[i]);
    }
    free(Matrixx);
}