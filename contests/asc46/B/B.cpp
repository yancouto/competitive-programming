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
const ll modn = 175781251;
inline ll mod(ll x) { return x % modn; }
const int N = 109, M = 10009;

ll fexp(ll x, ll p) {
	ll ans = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			ans = mod(ans * x);
	return ans;
}

ll p2[M], fat[M], invf[M];
ll comb(int n, int p) {
	return mod(fat[n] * mod(invf[p] * invf[n - p]));
}

ll memo0[N];
ll dp0(int n) {
	if(n == 0) return 1;
	ll &r = memo0[n];
	if(r != -1) return r;
	r = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= i * (n - i); j++)
			r = mod(r + mod(comb(n - 1, i - 1) * comb(i * (n - i), j)) * p2[j]);
	return r;
}

ll dp2(int);
ll dp1(int n) { return mod(dp0(n) - dp2(n) + modn); }

ll memo2[N];
ll dp2(int n) {
	if(n == 0) return 1;
	ll &r = memo2[n];
	if(r != -1) return r;
	r = 0;
	for(int i = 1; i < n; i++)
		r = mod(r + mod(comb(n - 1, i - 1) * dp1(i)) * 2ll * dp0(n - i));
	return r;
}

ll memo3[N];
ll dp3(int n) {
	if(n == 0) return 1;
	ll &r = memo3[n];
	if(r != -1) return r;
	r = 0;
	for(int i = 1; i <= n; i++)
		r = mod(r + comb(n - 1, i - 1) * mod(dp1(i) * dp3(n - i)));
	return r;
}

int main() {
	freopen("bipartite.in", "r", stdin);
	freopen("bipartite.out", "w", stdout);
	memset(memo0, -1, sizeof memo0);
	memset(memo2, -1, sizeof memo2);
	memset(memo3, -1, sizeof memo3);
	p2[0] = 1;
	fat[0] = 1;
	invf[0] = 1;
	for(int i = 1; i < M; i++)
		p2[i] = mod(2ll * p2[i - 1]),
		fat[i] = mod(ll(i) * fat[i - 1]),
		invf[i] = fexp(fat[i], modn - 2);
	int n;
	while(scanf("%d", &n) != EOF && n) {
		printf("%d\n", (int) dp3(n));
	}
}
