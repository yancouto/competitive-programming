#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

int n, m;

inline int id(int i, int j) { return i * (m + 2) + j; }
inline int LR(int i, int j) { return 2 * id(i, j); }
inline int UD(int i, int j) { return LR(i, j) + 1; }
inline int VF(int u) { return 2 * u; }
inline int VT(int u) { return 2 * u + 1; }

const int N = 60 * 60 * 60;

vector<int> adj[N];

int st[N], sn = 0;
int comp[N], ct = 0;
int d[N], low[N], tempo, seen[N]; bool bad;
int val[N];

void go(int u, int v) {
	return;
	if(u & 1) printf("UD");
	else printf("LR");
	u /= 2;
	printf("(%d,%d) = %d\n", u / (m + 2), u % (m + 2), v);
}

void dfs(int u) {
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u])
		if(seen[v]) low[u] = min(low[u], d[v]);
		else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] == d[u]) {
		int a;
		ct++;
		vector<int> C;
		do {
			a = st[--sn];
			C.pb(a);
			comp[a] = ct;
			if(comp[a ^ 1] == ct) bad = true;
			d[a] = low[a] = INT_MAX;
		} while(a != u);
		int v = -1;
		for(int c : C)
			if(val[c / 2] != -1)
				v = ((c & 1) ^ val[c / 2]);
		if(v == -1) v = 0;
		for(int c : C) {
			val[c / 2] = ((c & 1) ^ v);
			if(c <= 74) go(c / 2, val[c / 2]);
		}
	}
}

char g[100][100];
int S[N], sz[N], has[N];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if(g[(b / 2) / (m + 2)][(b / 2) % (m + 2)] == '#') return;
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int main() {
	int i, j;
	for_tests(tn, tt) {
		// LIMPAR AS PORRA
		scanf("%d %d", &n, &m);
		for(i = 0; i <= n+1; i++)
			for(j = 0; j <= m+1; j++) {
				if(i && j && i <= n && j <= m) scanf(" %c", &g[i][j]);
				else g[i][j] = '#';
			}
		for(i = 0; i < N; i++) S[i] = i, sz[i] = 1, has[i] = 0, adj[i].clear(), seen[i] = 0, val[i] = -1;
		tempo = 0; bad = false;
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++) {
				if(g[i][j] != '.' && g[i][j] != '-' && g[i][j] != '|') continue;
				if(g[i][j - 1] == '\\') join(LR(i, j), UD(i - 1, j - 1));
				else if(g[i][j - 1] == '/') join(LR(i, j), UD(i + 1, j - 1));
				else join(LR(i, j), LR(i, j - 1));

				if(g[i][j + 1] == '/') join(LR(i, j), UD(i - 1, j + 1));
				else if(g[i][j + 1] == '\\') join(LR(i, j), UD(i + 1, j + 1));

				if(g[i - 1][j] == '.' || g[i - 1][j] == '-' || g[i - 1][j] == '|')
					join(UD(i, j), UD(i - 1, j));
			}
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++)
				if(g[i][j] == '-' || g[i][j] == '|')
					has[find(LR(i, j))]++, has[find(UD(i, j))]++;
		//for(i = 0; i < LR(n, m) + 14; i++)
		//	if(find(i) == i && has[i] != 1)
		//		adj[VT(i)].pb(VF(i)); // always false
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++) {
				if(g[i][j] != '.' && g[i][j] != '-' && g[i][j] != '|') continue;
				int a = find(LR(i, j));
				if(a == LR(i, j) && has[a] != 1) {
					adj[VT(a)].pb(VF(a));
					//printf("at %d,%d has %d\n", i, j);
				}
				a = find(UD(i, j));
				if(a == UD(i, j) && has[a] != 1) adj[VT(a)].pb(VF(a));
			}
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++)
				if(g[i][j] == '-' || g[i][j] == '|') {
					// LR xor UD
					for(int x = 0; x < 4; x++) {
						int a = find(LR(i, j)), b = find(UD(i, j));
						if(x & 1) swap(a, b);
						if(x & 2) adj[VT(a)].pb(VF(b));
						else adj[VF(a)].pb(VT(b));
					}
				} else if(g[i][j] == '.') {
					int a = find(LR(i, j)), b = find(UD(i, j));
					adj[VF(a)].pb(VT(b));
					adj[VF(b)].pb(VT(a));
				}
		for(i = 0; i < N; i++)
			for(int j : adj[i])
				if(i <= VT(UD(n, m)))
					;//printf("%d %d\n", i, j);
		for(i = 0; i < N; i++)
			if(!seen[i])
				dfs(i);
		printf("Case #%d: ", tt);
		if(bad) puts("IMPOSSIBLE");
		else {
			puts("POSSIBLE");
			for(i = 1; i <= n; i++) {
				for(j = 1; j <= m; j++)
					if(g[i][j] == '-' || g[i][j] == '|')
						putchar(val[find(LR(i, j))]? '-' : '|');
					else
						putchar(g[i][j]);
				putchar('\n');
			}
		}

	}
}
