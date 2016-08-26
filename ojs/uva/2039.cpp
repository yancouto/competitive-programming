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
int x[302], y[302], r[302], e[302];
bool collide(int i, int j) {
	return ll(e[i] + r[i] + r[j]) * ll(e[i] + r[i] + r[j]) >= ll(x[i] - x[j]) * ll(x[i] - x[j]) + ll(y[i] - y[j]) * ll(y[i] - y[j]);
}

int S[302], sz[302];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

vector<int> adj[302];
bool seen[302];
int d[302], low[302], best[302], f[302], tempo;
int st[302], sn;
void dfs(int u) {
	if(seen[u]) return;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u]) {
		dfs(v);
		low[u] = min(low[u], low[v]);
	}
	f[u] = tempo++;
	if(low[u] == d[u]) {
		int x, mi = u;
		do {
			x = st[--sn];
			join(x, u);
			low[x] = INT_MAX;
			if(e[x] < e[mi]) mi = x;
		} while(x != u);
		best[find(u)] = mi;
		f[mi] = f[u];
	}
}
int degin[302];

int main() {
	int i, j, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d %d %d %d", &x[i], &y[i], &r[i], &e[i]);
			S[i] = i; sz[i] = 1;
			adj[i].clear();
		}
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(collide(i, j)) {
					adj[i].pb(j);
				}
		memset(seen, 0, sizeof seen);
		sn = 0; tempo = 0;
		for(i = 0; i < n; i++)
			dfs(i);
		memset(degin, 0, sizeof degin);
		set<pii> s;
		for(i = 0; i < n; i++)
			for(int v : adj[i])
				if(find(v) != find(i))
					degin[find(v)]++;
		ll tot = 0, tn = 0;
		vector<int> v; vector<pii> c;
		for(i = 0; i < n; i++) {
			if(S[i] != i) continue;
			if(degin[i]) c.pb(pii(e[best[i]], best[i]));
			else {
				tot += e[best[i]]; tn++;
				v.pb(best[i]);
			}
		}
		sort(c.begin(), c.end());
		for(pii g : c) {
			if(tot * (tn + 1) <= tn * ll(tot + g.fst)) continue;
			tot += g.fst; tn++;
			v.pb(g.snd);
		}
		sort(v.begin(), v.end(), [](int i, int j) { return f[i] < f[j]; });
		printf("Case #%d:", tt);
		for(int x : v)
			printf(" %d", x);
		putchar('\n');
	}
}
