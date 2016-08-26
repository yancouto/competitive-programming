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

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int n, m;
int g[502][502];
vector<int> v[502][502];
inline bool valid(int i, int j) {
	return i >= 0 && j >= 0 && i < n && j < m && g[i][j] == -1;
}
const int MAX = 500 * 500 * 5;
vector<int> adj[MAX];
int seen[MAX], tempo2;
int d[MAX], low[MAX], tempo;
int co[MAX], cn;
bool ok;
int st[MAX], sn;
void dfs(int u) {
	if(seen[u] == tempo2) return;
	seen[u] = tempo2;
	low[u] = d[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u]) {
		dfs(v);
		low[u] = min(low[u], low[v]);
	}
	if(low[u] == d[u]) {
		int a; cn++;
		do {
			a = st[--sn];
			co[a] = cn;
			if(co[a ^ 1] == cn) ok = false;
			low[a] = INT_MAX;
		} while(a != u);
	}
}

int main() {
	int i, j, k; char c;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		int nb = 0, nw = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf(" %c", &c);
				if(c == 'B') g[i][j] = nb++;
				else if(c == 'W') g[i][j] = -1, nw++;
				else g[i][j] = -2;
				v[i][j].clear();
			}
		if(nw != 2 * nb) { puts("NO"); continue; }
		for(i = 0; i < nb * 4; i++) adj[i].clear();
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				if(g[i][j] < 0) continue;
				for(k = 0; k < 4; k++) {
					int ni = i + dx[k], nj = j + dy[k], id = g[i][j] * 4 + k;
					if(!valid(ni, nj)) adj[id].pb(id ^ 1);
					else {
						for(int x : v[ni][nj]) {
							adj[id].pb(x ^ 1);
							adj[x].pb(id ^ 1);
						}
						v[ni][nj].pb(id);
					}
				}
			}
		tempo2++; tempo = 0;
		cn = sn = 0; ok = true;
		memset(co, 0, sizeof co);
		for(i = 0; i < nb * 4; i++)
			dfs(i);
		if(ok) puts("YES");
		else puts("NO");
	}
}
