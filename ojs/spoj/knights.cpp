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
const int MAX = 1002;
bool adj[MAX][MAX];
bool ok[MAX]; int seen[MAX], co[MAX], cn;
int d[MAX], low[MAX], tempo, n;
int st[MAX], sn;
int color[MAX];

bool dfs2(int u, int c) {
	if(seen[u] == 2) return c != color[u];
	color[u] = c;
	seen[u] = 2;
	for(int v = 0; v < n; v++)
		if(adj[u][v] && co[v] == co[u] && dfs2(v, !c))
			return true;
	return false;
}

void dfs(int u, int p) {
	if(seen[u]) return;
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v = 0; v < n; v++) {
		if(adj[u][v] && v != p && !seen[v]) {
			int x = d[u];
			swap(x, low[u]);
			int k = sn;
			dfs(v, u);
			if(low[v] >= d[u]) {
				int a; cn++; int sz = 0;
				st[sn++] = u;
				do {
					a = st[--sn];
					co[a] = cn;
					sz++;
					seen[a] = 1;
				} while(sn != k);
				bool good = dfs2(u, 0);
				for(int i = 0; i < sz; i++)
					ok[st[sn + i]] |= good;
			}
			swap(x, low[u]);
		}
		if(v != p && adj[u][v]) low[u] = min(low[u], low[v]);
	}
}

int main() {
	int i, m, a, b;
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		memset(adj, 1, sizeof adj);
		memset(ok, 0, sizeof ok);
		memset(seen, 0, sizeof seen);
		memset(co, 0, sizeof co);
		memset(color, 0, sizeof color);
		for(i = 0; i < n; i++) adj[i][i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a][b] = adj[b][a] = 0;
		}
		cn = sn = 0; tempo = 0;
		for(i = 0; i < n; i++)
			dfs(i, -1);
		printf("%d\n", n - accumulate(ok, ok + n, 0));
	}
}
