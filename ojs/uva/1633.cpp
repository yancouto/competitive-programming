// ERROU
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

int fexp(int n, int p, int mod) {
	int r = 1 % mod; n %= mod;
	for(; p; p >>= 1, n = (n * n) % mod)
		if(p & 1)
			r = (n * r) % mod;
	return r;
}

const int N = 11234;
vector<int> ps[N], g[N], k[N], X[N];
int n;
int a[1123], phi[11234];
int go(int i, int mod) {
	if(i == n - 1) return a[i] % mod;
	if(i == n - 2) return fexp(a[i], a[i + 1], mod);
	int ans = 1 % mod;
	int n = a[i];
	//printf("a[%d] = %d\n", i, n);
	for(int j = 0; j < ps[mod].size(); j++) {
		if(n % ps[mod][j]) continue;
		int ct = 0, p = ps[mod][j];
		//printf("%d | %d g %d k %d X %d\n", p, n, g[mod][j], k[mod][j], X[mod][j]);
		while(!(n % p)) ct++, n /= p;
		int mid = (go(i + 1, k[mod][j]) - g[mod][j] + 100 * mod) % mod;
		//printf("%d * %d ^ %d\n", X[mod][j], p, mid);
		ans *= fexp((fexp(p, mid, mod) * X[mod][j]) % mod, ct, mod);
		ans %= mod;
	}
	ans *= (fexp(n, go(i + 1, phi[mod]), mod));
	ans %= mod;
	return ans;
}

int seen[N], tempo, dist[N];

int main() {
	int i, m, t = 0, j;
	for(i = 0; i < N; i++) phi[i] = i;
	for(i = 2; i < N; i++)
		if(phi[i] == i)
			for(j = i; j < N; j += i)
				phi[j] = (phi[j] / i) * (i - 1), ps[j].pb(i);
	int mxg = 0;
	for(i = 2; i <= 10000; i++)
		for(int p : ps[i]) {
			tempo++;
			int x = p % i;
			for(t = 1; seen[x] < tempo; t++, x = (x * p) % i)
				seen[x] = tempo, dist[x] = t;
			g[i].pb(dist[x]);
			k[i].pb(t - dist[x]);
			X[i].pb(x);
			mxg = max(mxg, dist[x]);
		}
	t = 0;
	while(scanf("%d %d", &m, &n) == 2) {
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		while(n > 1 && fexp(a[n - 2], a[n - 1], 1001) == fexp(a[n - 2], a[n - 1], 3433) && fexp(a[n-2], a[n-1], 1212) == fexp(a[n-2],a[n-1], 3131)) {
			a[n - 2] = fexp(a[n - 2], a[n - 1], 1001);
			n--;
		}
		//for(i = 0; i < n; i++) printf("%d ", a[i]); puts("");
		printf("Case #%d: %d\n", ++t, go(0, m) % m);
	}
}
