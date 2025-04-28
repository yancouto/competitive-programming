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

const int N = 112345;

int t;
ll n, m, h;
ll fat[N];

ll fexp(ll x, ll p) {
    ll ans = 1;
    for (ll pot = x; p > 0; p >>= 1, pot = mod(pot * pot))
        if (p & 1)
            ans = mod(ans * pot);
    return ans;
}

ll inv(ll x) {
    return fexp(x, modn - 2);
}

// n spaces total, m trees, >=k spaces >= h but they all must be to the right of the first tree
ll inner_solve(ll n, ll m, ll k) {
    //printf("inner_solve(%lld, %lld, %lld) = %lld\n", n, m, k, mod(fat[n - k * h] * inv(mod(mod(fat[k] * fat[m - k]) * fat[n - k * h - m]))));
    return mod(fat[n - k * h] * inv(mod(mod(fat[k] * fat[m - k]) * fat[n - k * h - m])));
}

// n spaces total, m trees, >=k spaces >= h
ll solve(ll n, ll m, ll k) {
    ll ans = 0;
    if(k > 0) {
        // First space between any trees is >= h
        ans = inner_solve(n - h, m, k - 1);
    }
    return mod(ans + inner_solve(n, m, k));
}

int main() {
    scanf("%d", &t);
    fat[0] = 1;
    for(ll i = 1; i < N; i++)
        fat[i] = mod(fat[i - 1] * i);
    while(t--) {
        scanf("%lld %lld %lld", &n, &m, &h);
        ll tot = solve(n, m, 0);
        ll pos = 0;
        for(int k = 1; k * h + m <= n; k++) {
            ll sign = (k & 1)? 1 : -1;
            pos = mod(pos + sign * solve(n, m, k) + modn);
        }
        //printf("tot %lld pos %lld\n", tot, pos);
        ll ans = mod(pos * inv(tot));
        printf("%lld\n", ans);
    }
}