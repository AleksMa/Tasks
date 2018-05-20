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

using namespace std;

int main()
{
    int n, k;
    cin >> k >> n;
    int arr[k];
    cin >> arr[0];
    for (int i = 1; i < k; i++) {
        cin >> arr[i];
        if (arr[i] - arr[i - 1] > n) {
            cout << -1;
            return 0;
        }
    }
    int count = 1;
    int l = n;
    for (int i = 1; i < k; i++) {
        if (l < arr[i] - arr[i - 1]) {
            count++;
            l = n;
        }
        l -= arr[i] - arr[i - 1];
    }

    cout << count;
    return 0;
}