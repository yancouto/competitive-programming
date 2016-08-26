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

int d[N], low[N], f[N], cut[N], seen[N], tempo;
vector<int> adj[N], so[N];
set<pii> bs;

void dfs(int u, int p) {
	int nf = 0; bool any = false;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	for(int v : adj[u])
		if(!seen[v]) {
			dfs(v, u); nf++;
			so[u].pb(v);
			any |= (low[v] >= d[u]);
			if(low[v] > d[u]) bs.insert(pii(u, v));
			low[u] = min(low[u], low[v]);
		} else if(v != p) low[u] = min(low[u], d[v]);
	cut[u] = (u? any : nf > 1);
	f[u] = tempo++;
}

inline bool desc(int a, int u) { return d[a] >= d[u] && f[a] <= f[u]; }

int id(int a, int u) {
	if(desc(a, u)) {
		int b = *prev(upper_bound(so[u].begin(), so[u].end(), a, [](int i, int j) { return d[i] < d[j]; }));
		if(low[b] >= d[u]) return b;
		else return -1;
	}
	else return -1;
}

int main() {
	int i, n, m, a, b, u, v, op;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(0, 0);
	for_tests(q, qq) {
		scanf("%d %d %d %d", &op, &a, &b, &u); a--; b--; u--;
		if(op == 1) {
			scanf("%d", &v); v--;
			if(d[v] < d[u]) swap(u, v);
			if(!bs.count(pii(u, v))) { puts("da"); continue; }
			if(desc(a, v) == desc(b, v)) puts("da");
			else puts("ne");
		} else {
			if(!cut[u]) { puts("da"); continue; }
			if(id(a, u) == id(b, u)) puts("da");
			else puts("ne");
		}
	}
}
