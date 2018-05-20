#include <bits/stdc++.h>

#define fi first
#define se second
#define pb push_back
#define sqr(x) ((x) * (x))
#define all(x) (x).begin(), (x).end()

using namespace std;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned uint;

const int inf = (int)1e9;
const ll linf = LLONG_MAX;

using namespace std;

ull combination(ull n, ull k) {
    if (k > n) return 0;

    ull res = 1, i = n - k + 1, counter = 1;
    while(i <= n) {
        ull j = i;
        if (j % counter == 0) j /= counter;
        else res /= counter;
        res *= j;
        i++;
        counter++;
    }
    return res;
}

int main(int argc, char **argv) {
    int g, d, f;
    cin >> g >> d >> f;


    ull prefixG[100001];
    ull prefixD[100001];
    ull prefixF[100001];

    for (int i = 0; i < 100001; i++) {
        prefixG[i] = 0;
        prefixD[i] = 0;
        prefixF[i] = 0;
    }

    int x;
    for (int i = 0; i < g; i++) {
        cin >> x;
        prefixG[x] = 1;
    }

    for (int i = 0; i < d; i++) {
        cin >> x;
        prefixD[x] = 1;
    }

    for (int i = 0; i < f; i++) {
        cin >> x;
        prefixF[x] = 1;
    }

    for (int i = 1; i < 100001; i++) {
        prefixG[i] += prefixG[i - 1];
    }

    for (int i = 1; i < 100001; i++) {
        prefixD[i] += prefixD[i - 1];
    }
    for (int i = 1; i < 100001; i++) {
        prefixF[i] += prefixF[i - 1];
    }

    ull res = 0, i = 1;
    while(i <= 50000) {
        ull numsG = prefixG[2 * i] - prefixG[i - 1];
        ull numsD = prefixD[2 * i] - prefixD[i - 1];
        ull numsF = prefixF[2 * i] - prefixF[i - 1];

        res += combination(numsG, 1) * combination(numsD, 2) * combination(numsF, 3);

        if (i != 50000) {
            numsG = prefixG[2 * i] - prefixG[i];
            numsD = prefixD[2 * i] - prefixD[i];
            numsF = prefixF[2 * i] - prefixF[i];
            res -= combination(numsG, 1) * combination(numsD, 2) * combination(numsF, 3);
        }
        i++;
    }

    cout << res;
    return 0;
}



