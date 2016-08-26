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
int P[N];
ll W[N], sum[N], val[N], V[N], all;
vector<pii> adj[N];

void dfsd(int u, int p, int c) {
	P[u] = p;
	W[u] = c;
	val[u] = 0;
	for(pii e : adj[u])
		if(e.fst != p) {
			int v = e.fst;
			dfsd(v, u, e.snd);
			sum[u] += sum[v];
			val[u] += val[v] + sum[v] * ll(e.snd);
		}
}

ll memo[N];
ll solve(int u) {
	ll &r = memo[u];
	if(r != -1) return r;
	if(u == 0) return r = val[u];
	r = solve(P[u]) - W[u] * sum[u] + W[u] * (all - sum[u]);
	return r;
}

int main() {
	freopen("house.in", "r", stdin);
	freopen("house.out", "w", stdout);
	int i, n, a, b, l;
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%I64d", &sum[i]);
		V[i] = sum[i];
		all += sum[i];
	}
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &l); a--; b--;
		adj[a].pb(pii(b, l));
		adj[b].pb(pii(a, l));
	}
	dfsd(0, -1, 0);
	ll best = LLONG_MAX; int bi;
	for(i = 0; i < n; i++)
		if(solve(i) < best) {
			best = solve(i);
			bi = i;
		}
	printf("%d %I64d\n", bi + 1, best);
}
