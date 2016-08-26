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
const int N = 112345;

ll a[N], ac[N];

map<ll, int> mp[40];
ll e(ll i, int m) {
	if(m == 0) return a[i];
	if(mp[m].count(i)) return mp[m][i];
	if(i & 1) return mp[m][i] = mod(e(i / 2, m - 1) + e((i + 1) / 2, m - 1));
	else return mp[m][i] = e(i / 2, m - 1);
}

map<ll, int> mg[40];
ll g(ll i, int m) {
	if(m == 0) return ac[i];
	if(mg[m].count(i)) return mg[m][i];
	if(i & 1) return mg[m][i] = mod(g(i - 1, m) + e(i, m));
	else return mg[m][i] = mod(3ll * g(i / 2, m - 1) - mod(a[0] + e(i / 2, m - 1)) + modn);
}

int main() {
	int i, n, m; ll x, y;
	for_tests(t, tt) {
		scanf("%d %d %lld %lld", &n, &m, &x, &y); x--; y--;
		for(i = 0; i <= 33; i++) mp[i].clear(), mg[i].clear();
		for(i = 0; i < n; i++)
			scanf("%lld", &a[i]);
		ac[0] = a[0];
		for(i = 1; i < n; i++) ac[i] = a[i] + ac[i - 1];
		ll ans = g(y, m);
		if(x > 0) ans = mod(ans - g(x - 1, m) + modn);
		printf("%lld\n", ans);
	}
}
