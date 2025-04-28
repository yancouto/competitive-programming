#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }

ll solve_orig(int mx, int gcd) {
    assert(mx % gcd == 0);
    ll tot = 1;
    for(int i = 1; i < mx; i++)
        if(__gcd(i, gcd) < gcd)
            tot = mod(tot + 2 * solve_orig(i, __gcd(i, gcd)));
    return tot;
}


map<pii, ll> memo;

ll solve(int mx, int gcd) {
    if(memo.count(pii(mx, gcd))) return memo[pii(mx, gcd)];
    assert(mx % gcd == 0);
    ll tot = 1;
    for(int i = 1; i < mx; i++)
        if(__gcd(i, gcd) < gcd)
            tot = mod(tot + 2ll * solve(i, __gcd(i, gcd)));
    memo[pii(mx, gcd)] = tot;
    return tot;
}

int main() {
    ll tot = 0;
    for(int i = 1; i <= 100000; i++) {
        tot = mod(tot + solve(i, i));
        printf("%lld,", tot);
    }
    return 0;
    int m;
    for_tests(t, tt) {
        scanf("%d", &m);
        ll tot = 0;
        for(int i = 1; i <= m; i++)
            tot = mod(tot + solve(i, i));
        printf("%lld\n", tot);
    }

}