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

int ord[N], on;
vector<int> adj[N], q[N];
int st[N], sn, low[N], d[N], seen[N], tempo, cmp[N];
pii g[N]; int gn;

void dfs(int u) {
	st[sn++] = u;
	low[u] = d[u] = tempo++;
	seen[u] = true;
	for(int v : adj[u])
		if(seen[v]) low[u] = min(low[u], d[v]);
		else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] == d[u]) {
		for(int i = sn - 1; st[i] != u; i--) cmp[st[i]] = u;
		cmp[u] = u;
		for(int &v : adj[u]) v = cmp[v];
		int a = -1;
		while(a != u) {
			a = st[--sn];
			d[a] = INT_MAX;
			if(a != u) for(int v : adj[a]) adj[u].pb(cmp[v]);
		}
		sort(adj[u].begin(), adj[u].end());
		adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
		for(int v : adj[u]) if(u != v) g[gn++] = pii(u, v);
		ord[on++] = u;
	}
}

const int K = 64;
ull val[N];

vector<int> adj2[N];

inline int get() {
	char c;
	while(isspace(c = getchar_unlocked()));
	int x = c - '0';
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
	return x;
}

int main() {
	int i, n, k, a, b, g;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	n = get();
	k = get();
	for(i = 0; i < k; i++) {
		a = get(); b = get();
		adj[a].pb(b);
	}
	for(i = 1; i <= n; i++) for(int v : adj[i]) adj2[i].pb(v);
	int m = k;
	for(i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i);
	k = get();
	for(i = 0; i < k; i++) {
		a = get(); b = get();
		a = cmp[a]; b = cmp[b];
		q[b].pb(a);
	}
	for(g = 1; g <= n; g += K) {
		for(i = 1; i <= n; i++) val[i] = 0;
		for(i = g; i < g + K && i <= n; i++) if(cmp[i] == i) val[i] = (1ull << (i - g));
		for(i = 0; i < gn; i++)
			val[::g[i].fst] |= val[::g[i].snd];
		for(i = g; i < g + K && i <= n; i++)
			for(int v : q[i])
				if((val[v] >> (i - g)) & 1ull) {
					puts("NO");
					return 0;
				}
	}
	puts("YES");
	printf("%d\n", m);
	for(i = 1; i <= n; i++)
		for(int v : adj2[i])
			printf("%d %d\n", i, v);
}
