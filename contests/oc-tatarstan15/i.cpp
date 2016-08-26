#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

unordered_map<ll, ll> mp[1005];
ll comb(ll n, int p) {
	if(p < 0 || p > n) return 0;
	if(n == 0) return 1;
	if(mp[p].count(n)) return mp[p][n];
	return mp[p][n] = comb(n - 1, p - 1) + comb(n - 1, p);
}

int main() {
	ll n; int i, j, m;
	scanf("%lld %d", &n, &m);
	for(i = m; i > 2; i--) {
		for(j = i; comb(j, i) <= n; j++);
		printf("%d ", j - 1);
		n -= comb(j - 1, i);
	}
	ll l = 0, r = 1000000000;
	while(l < r) {
		ll m = (l + r + 1) / 2;
		if(((m * (m - 1)) / 2) <= n) l = m;
		else r = m - 1;
	}
	printf("%d", (int) l);
	n -= (l * (l - 1)) / 2;
	printf(" %d\n", (int) n);
}
