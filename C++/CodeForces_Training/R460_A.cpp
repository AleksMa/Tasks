//
// Created by alexey on 10.02.18.
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

    int n, m;
    cin >> n >> m;
    double minC = 1.0*inf;

    for(int i = 0; i<n; i++){
        double a, b;
        cin >> a >> b;
        minC = min(minC*1.0, a/b);
    }
    double M = m*1.0;
    cout << setprecision(8) << minC*M;

    return 0;
}