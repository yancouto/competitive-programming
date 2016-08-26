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

vector<pii> adj[N];
ll sum[N], val[N], d[N], all;

ll dfs1(int u, int p) {
	for(pii e : adj[u])
		if(e.fst != p) {
			sum[u] += dfs1(e.fst, u);
			d[u] += d[e.fst] + sum[e.fst] * ll(e.snd);
		}
	return sum[u];
}

void dfs2(int u, int p, ll w) {
	if(u) val[u] = val[p] + w * (all - 2ll*sum[u]);
	else val[u] = d[u];
	for(pii e : adj[u])
		if(e.fst != p)
			dfs2(e.fst, u, e.snd);
}

int main() {
	freopen("house.in", "r", stdin);
	freopen("house.out", "w", stdout);
	int i, n, a, b, l;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%I64d", &sum[i]);
	all = accumulate(sum, sum + n, 0ll);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &l);
		a--; b--;
		adj[a].pb(pii(b, l));
		adj[b].pb(pii(a, l));
	}
	dfs1(0, 0);
	dfs2(0, 0, 0);
	i = min_element(val, val + n) - val;
	printf("%d %I64d\n", i + 1, val[i]);
}
