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
const int N = 270000;
ll f[N], fi[N], v[N], a[N];
int n;

ll fexp(ll x, ll p) {
	ll resp = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			resp = mod(resp * x);
	return resp;
}

inline ll comb(int p, int n) {
	if(p > n || p < 0) return 0ll;
	return mod(f[n] * mod(fi[p] * fi[n - p]));
}
inline ll invcomb(int p, int n) {
	if(p > n || p < 0) return 0ll;
	return mod(fi[n] * mod(f[p] * f[n - p]));
}

inline ll F(int i, int m) {
	return mod(comb(m - 1, n - i - 1) * invcomb(m, n));
}

inline ll G(int i, int m) {
	return mod(comb(m - 1, n - i - m - 1) * invcomb(m, n - m));
}

int main() {
	int i, j, k;
	scanf("%d", &k); n = (1 << k);
	for(i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	f[0] = 1;
	for(i = 1; i <= n; i++)
		f[i] = mod(ll(i) * f[i - 1]);
	fi[n] = fexp(f[n], modn - 2);
	for(i = n - 1; i >= 0; i--)
		fi[i] = mod(fi[i + 1] * ll(i + 1));
	int m = 1, on = n;
	ll tot = 0;
	for(i = 0; i < k; i++, m *= 2, on /= 2) {
		for(j = 0; j < n; j++) {
			v[j] = mod(G(j, m) * a[j]);
			if(j) v[j] = mod(v[j - 1] + v[j]);
		}
		ll t = 0;
		for(j = 1; j < n; j++)
			t = mod(t + mod(F(j, m) * a[j]) * v[j - 1]);
		tot = mod(tot + t * ll(on));
	}
	printf("%lld\n", tot);
}
