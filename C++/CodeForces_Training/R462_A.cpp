//
// Created by alexey on 14.02.18.
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

int main(int argc, char **argv) {
    int m, n;
    cin >> n >> m;
    ll a[n], b, c[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        c[i] = -linf;
    }

    for (int i = 0; i < m; i++) {
        cin >> b;
        for(int j = 0; j < n; j++){
            c[j]=max(c[j], a[j] * b);
        }
    }
    sort(c, c+n);
    cout << c[n-2];

}
