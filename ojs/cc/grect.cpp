#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
ll full(ll x, ll y) {
	if(x < 0 || y < 0) return 0;
	return x * y;
}
ll r(ll x, ll y) {
	return full(x, y) - full(x - 2, y - 2);
}

ld fexp(ld p, ll e) {
	ld r = 1;
	for(; e; e >>= 1) {
		if(e & 1) r *= p;
		p *= p;
	}
	return r;
}

int main() {
	int n, m, k, i, j;
	scanf("%d %d %d", &m, &n, &k);
	if(k == 1) {
		printf("%lld\n", ((ll(m) * ll(m + 1)) / 2ll) * ll(ll(ll(n) * ll(n + 1)) / 2ll));
		return 0;
	}
	ld k1 = 1. / k;
	ld all = 0;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++) {
			ld v = fexp(k1, r(i, j) - 1);
			ld vv = v * ld(n - i + 1) * ld(m - j + 1);
			if(abs(vv) <= 1e-12) break;
			all += vv;
		}
	double d = all;
	printf("%.0f\n", d);
}
