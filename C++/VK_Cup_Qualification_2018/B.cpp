//
// Created by alexey on 23.02.18.
//

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
typedef vector<int> VI;
typedef long double ld;
typedef unsigned uint;

const int inf = INT_MAX;
const ll linf = LLONG_MAX;
const int mod = 2;

inline int sign(ll val) { return val > 0 ? 1 : val == 0 ? 0 : -1; }
inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
inline int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
inline int mul(int a, int b) { return int(a * 1ll * b % mod); }

using namespace std;

int getNeighbours(char **arr, int i, int j){
    int count = 0;
    if(j == 0 || j == 4 || j == 9){
        if(arr[i][j+1] == 'S')
            return 1;
        else
            return 0;
    }
    else if(j == 2 || j == 7 || j == 11){
        if(arr[i][j-1] == 'S')
            return 1;
        else
            return 0;
    }
    else{
        if(arr[i][j-1] == arr[i][j+1] && arr[i][j-1] == 'S')
            return 2;
        else if(arr[i][j-1] == 'S' || arr[i][j+1] == 'S')
            return 1;
        else return 0;
    }
}

int main() {

    int n, k;
    cin >> n >> k;
    char **arr = (char**)malloc(n*sizeof(char*));

    for(int i = 0; i < n; i++){
        arr[i] = (char*)malloc(12*sizeof(char));
        cin >> arr[i];
    }
    bool flag = true;
    int count = 0;

    for(int i = 0; i < n && flag; i++){
        for(int j = 0; j < 12 && flag; j++){
            if(j == 3 || j == 8)
                continue;
            if(arr [i][j] == '.' && !getNeighbours(arr, i, j)) {
                arr[i][j] = 'x';
                k--;
            }
            if(k==0)
                flag = false;
        }
    }


    for(int i = 0; i < n && flag; i++){
        for(int j = 0; j < 12 && flag; j++){
            if(j == 3 || j == 8)
                continue;
            if(arr [i][j] == '.' && getNeighbours(arr, i, j) == 1) {
                arr[i][j] = 'x';
                k--;
            }
            if(k==0)
                flag = false;
        }
    }


    for(int i = 0; i < n && flag; i++){
        for(int j = 0; j < 12 && flag; j++){
            if(j == 3 || j == 8)
                continue;
            if(arr [i][j] == '.' && getNeighbours(arr, i, j) == 2) {
                arr[i][j] = 'x';
                k--;
            }
            if(k==0)
                flag = false;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 12; j++){
            if(j == 3 || j == 8)
                continue;
            if(arr [i][j] == 'S'){
                if(j != 0){
                    if(arr[i][j-1] != '.' && arr[i][j-1] != '-')
                        count++;
                }
                if(j != 11){
                    if(arr[i][j+1] != '.' && arr[i][j+1] != '-')
                        count++;
                }
            }

        }
    }
    cout << count << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i] << endl;

    return 0;
}