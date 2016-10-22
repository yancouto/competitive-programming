#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, m, k;

const int N = 2123456;
ll fat[N], fati[N];
const int K = 2123;

inline ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(r * x);
	return r;
}

inline ll inv(ll x) { return fexp(x, modn - 2); }

inline ll ways(int n, int m) {
	n--, m--;
	//printf("ways(%d, %d) = %lld * %lld * %lld\n", n, m, fat[n + m], fati[n],fati[m]);
	return mod(fat[n + m] * mod(fati[n] * fati[m]));
}
typedef pair<int, ll> pil;
vector<pil> adj[K];
pii a[K];

void pre(int i) {
	for(int j = i + 1; j < k; j++) {
		if(a[j].fst < a[i].fst || a[j].snd < a[i].snd) continue;
		adj[i].pb(pil(j, ways(a[j].fst - a[i].fst + 1, a[j].snd - a[i].snd + 1)));
		debug("(%d,%d)->(%d,%d) = %lld\n", a[i].fst, a[i].snd, a[j].fst, a[j].snd, adj[i].back().snd);
	}
	return;
	set<pii> par; // (r, c)
	par.insert(pii(-1e8, 1e8));
	par.insert(pii(1e8, -1e8));
	for(int j = i + 1; j < k; j++) {
		if(a[j].fst < a[i].fst || a[j].snd < a[i].snd) continue;
		if(par.count(a[j])) continue;
		auto it = par.upper_bound(a[j]);
		if(prev(it)->snd <= a[j].snd) continue;
		adj[i].pb(pil(j, ways(a[j].fst - a[i].fst + 1, a[j].snd - a[i].snd + 1)));
		it = par.insert(a[j]).fst;
		while(a[j].snd <= next(it)->snd) par.erase(next(it));
	}
}

ll memo[K][30];
ll solve(int i, int g) {
	if(g < 0) return 0;
	if(i == k - 1) return g == 0;
	ll &r = memo[i][g];
	if(r != -1) return r;
	r = 0;
	for(pil p : adj[i]) {
		r = mod(r + solve(p.fst, g - (i > 0)) * p.snd);
		//if(i > 0) r = mod(r + solve(p.fst, g) * p.snd);
		//debug("solve(%d, %d) [%d] += %lld * %lld\n", i, g, p.fst, solve(p.fst, g - (i > 0)), p.snd);
	}
	debug("solve(%d, %d) = %lld\n", i, g, r);
	return r;
}


int main() {
	int i, j, s;
	fat[0] = 1;
	for(i = 1; i < N; i++)
		fat[i] = mod(ll(i) * fat[i - 1]);
	fati[N - 1] = inv(fat[N - 1]);
	for(i = N - 2; i >= 0; i--)
		fati[i] = mod(ll(i + 1) * fati[i + 1]);
	scanf("%d %d %d %d", &n, &m, &k, &s);
	for(i = 0; i < k; i++) scanf("%d %d", &a[i].fst, &a[i].snd);
	a[k] = pii(1, 1);
	a[k + 1] = pii(n, m);
	k += 2;
	sort(a, a + k);
	for(i = 0; i < k; i++)
		pre(i);
	ll ans = 0;
	memset(memo, -1, sizeof memo);
	for(j = 0; (s >> j) > 0; j++)
		printf("solve(0, %d) = %lld\n", j, solve(0, j));
	for(j = 0; (s >> j) > 0; j++)
		ans = mod(ans + mod(solve(0, j) - solve(0, j + 1) + modn) * ll(s >> j));
	printf("sum %lld\n", ans);
	ans = mod(ans * inv(ways(n, m)));
	printf("%d\n", (int) ans);
}
