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

    int n, d;
    cin >> n >> d;
    int x[n], a[n][n], count[n], max = 0, maxI = 0, k = 0;
    bool flag = true;
    for(int i = 0; i < n; i++){
        cin >> x[i];
        count[i] = 0;
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = abs(x[i] - x[j]);
            if (a[i][j] > d) {
                flag = false;
                count[i]++;
                count[j]++;
            }
        }
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
     */

    while(!flag){
        k++;
        flag = true;


        max = 0;
        for (int i = 0; i < n; i++) {
            if (max < count[i]) {
                max = count[i];
                maxI = i;
            }
        }

        /*
        if(k < 30){
            cout << endl;
            for (int i = 0; i < n; i++)
                cout << count[i] << " ";
            cout << endl;
            cout << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << a[i][j] << " ";
                }
                cout << endl;
            }
        }*/


        for (int j = 0; j < n; j++) {
            a[maxI][j] = 0;
            a[j][maxI] = 0;
            count[j] = 0;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] > d) {
                    flag = false;
                    count[i]++;
                    count[j]++;
                }
            }
        }


    }

    cout << k << endl;

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    */
    return 0;
}