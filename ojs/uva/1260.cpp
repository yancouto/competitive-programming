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

int w, h;
const int MAX = 200;
inline int UP(int i) { return i; }
inline int RI(int i) { return i + w; }
inline int vtrue(int i) { return i << 1; }
inline int vfalse(int i) { return vtrue(i) + 1; }

vector<int> adj[MAX];
void or_both(int v, int a, int b) {
	adj[v ^ 1].pb(a);
	adj[v ^ 1].pb(b);
}

bool bad;
int d[MAX], low[MAX], seen[MAX], tempo;
int st[MAX], sn, comp[MAX];
void dfs(int u) {
	if(seen[u]) return;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u]) {
		dfs(v);
		low[u] = min(low[u], low[v]);
	}
	if(d[u] == low[u]) {
		int x;
		do {
			x = st[--sn];
			low[x] = INT_MAX;
			comp[x] = u;
			if(comp[x ^ 1] == u) bad = true;
		} while(x != u);
	}
}

int main() {
	int i, m, x1, y1, x2, y2;
	for_tests(t, tt) {
		scanf("%d %d %d", &w, &h, &m);
		tempo = sn = 0;
		for(i = 0; i < MAX; i++) {
			adj[i].clear();
			comp[i] = -1;
			seen[i] = 0;
		}
		for(i = 0; i < m; i++) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x1--; x2--; y1--; y2--;
			if(x1 == x2) {
				int v = ((y2 > y1)? vtrue : vfalse)(UP(x1));
				adj[v ^ 1].pb(v);
			} else if(y1 == y2) {
				int v = ((x2 > x1)? vtrue : vfalse)(RI(y1));
				adj[v ^ 1].pb(v);
			} else {
				int v1 = ((x2 > x1)? vtrue : vfalse)(RI(y1));
				int v2 = ((y2 > y1)? vtrue : vfalse)(UP(x2));
				int g1 = ((y2 > y1)? vtrue : vfalse)(UP(x1));
				int g2 = ((x2 > x1)? vtrue : vfalse)(RI(y2));
				or_both(v1, g1, g2);
				or_both(v2, g1, g2);
				or_both(g1, v1, v2);
				or_both(g2, v1, v2);
			}
		}
		bad = false;
		for(i = 0; i < MAX; i++)
			dfs(i);
		if(bad) puts("No");
		else puts("Yes");
	}
}
