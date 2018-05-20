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

int intersection(bool **set, int j, int i, int n){
    int count  = 0;
    for(int k = 0; k < n; k++){
        if(!set[j][k] && set[i][k]){
            set[j][k] = true;
            count++;
        };
    }
    return count;
}

int main() {

    int n, k, l = 0, r = 0;
    cin >> n >> k;
    int msg[n], count[n];
    bool **set = (bool**)malloc(n*sizeof(bool*));

    for(int i = 0; i < n; i++){
        set[i] = (bool*)malloc(n * sizeof(bool));
        for(int j = 0; j < n; j++){
            set[i][j] = false;
        }
    }

    for(int i = 0; i < n; i++){
        cin >> msg[i];
        count[i] = 0;
        l = max(i - k, 0);
        r = min(i + k, n - 1);
        for(int j = l; j <= r; j++){
            set[i][j] = true;
            count[i]++;
        }
        if(msg[i]){
            count[i] += intersection(set, i, msg[i] - 1, n);
        }
        cout << count[i] << " ";
    }
    cout << endl << endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << (set[i][j] ? 1 : 0) << " ";
        }
        cout << endl;
    }

    return 0;
}