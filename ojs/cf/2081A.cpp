#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1e9 + 7;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;

char s[N];
ll dp[N][2];
int pr[N];
ll inv2 = 500000004;

ll solve(int i, bool force1) {
    if (force1) assert(s[i] == '0');
    ll &r = dp[i][force1];
    if(r != -1) return r;
    if (s[i] == '0' && !force1)
        return r = 1 + solve(i - 1, false);
    if(i == 0) return r = 0;
    r = 1 + solve(i - 1, false); // floor
    // ceil
    if(pr[i - 1] == 0) r += 1 + i;
    else r += (i - pr[i - 1]) + solve(pr[i - 1], true);
    return r = mod(r * inv2);
}

int main() {
    int n;
    for_tests(t, tt) {
        scanf("%d", &n);
        scanf(" %s", s);
        for(int i = 0; i < n; i++) dp[i][0] = dp[i][1] = -1;
        for(int i = 1; i < n; i++)
            if(s[i] == '1')
                pr[i] = pr[i - 1];
            else
                pr[i] = i;
        printf("%lld\n", solve(n - 1, false));
    }
}