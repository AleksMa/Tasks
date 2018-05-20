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

int main() {

    ll n, k, A, B;
    cin >> n >> k >> A >> B;
    ll x = n, sum = 0;

    while(x > 1){
        if(x % k == 0){
            if(A*(x - x / k) >= B){
                x /= k;
                sum += B;
            }
            else{
                sum += A*(x - 1);
                break;
            }
        }
        else{
            ll next = x > k ? x - x / k * k : x - 1;
            x-= next;
            sum += A * next;
        }
    }

    cout << sum;


    return 0;
}