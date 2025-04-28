#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int main() {
    ll x, m;
    for_tests(t, tt) {
        scanf("%lld %lld", &x, &m);
        int count = 0;
        for(ll y = x / 2; y <= 2 * x; y++)
            if(y >= 1 && y <= m && x != y && ((x % (x ^ y) == 0) || (y % (x ^ y) == 0))) {
                count++;
            }
        printf("%d\n", count);
    }
}