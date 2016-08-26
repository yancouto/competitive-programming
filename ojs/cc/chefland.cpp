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

vector<int> adj[N];

int st[N], g[N], sn;
int d[N], low[N], f[N], tempo, h[N], p[N], seen[N], ok[N];

void dfs(int u, int p, int nv) {
	h[u] = nv;
	::p[u] = p;
	seen[u] = true;
	low[u] = d[u] = tempo++;
	for(int v : adj[u]) {
		if(v == p) { p = -1; continue; }
		if(seen[v]) {
			low[u] = min(low[u], d[v]);
		} else {
			dfs(v, u, nv + 1);
			low[u] = min(low[u], low[v]);
			if(low[v] > d[u])
				st[sn++] = v;
		}
	}
	f[u] = tempo++;
}

int main() {
	int i, j, a, b, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(0, -1, 0);
	sort(st, st + sn, [](int i, int j) { return d[i] < d[j]; });
	for(i = 0; i < n; i++)
		if(!seen[i]) {
			puts("NO");
			return 0;
		}
	j = 0;
	for(i = 0; i < sn; i++)
		if(i == sn - 1 || f[st[i]] < d[st[i + 1]])
			g[j++] = st[i];
	sn = j;
	if(sn <= 1) puts("YES");
	else if(sn > 2) puts("NO");
	else {
		a = g[0], b = g[1];
		if(h[a] < h[b]) swap(a, b);
		while(h[a] > h[b]) {
			ok[a] = true;
			a = p[a];
		}
		while(a != b) {
			ok[a] = ok[b] = true;
			a = p[a]; b = p[b];
		}
		for(i = 0; i < sn; i++)
			if(!ok[st[i]]) {
				puts("NO");
				return 0;
			}
		puts("YES");
	}
}
