#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

const int N = 512;
vector<int> adj[N];
int madj[N][N];
int c[N][N];

void imp() {
	puts("Plan failed");
	exit(0);
}

void dfs(int ref, int u, int co) {
	if(c[ref][u] != -1 && c[ref][u] != co) imp();
	if(c[ref][u] != -1) return;
	//printf("c[%d][%d] = %d\n", ref, u, co);
	c[ref][u] = co;
	for(int v : adj[u]) {
		//printf("%d->%d [%d]\n", u, v, ref);
		if(madj[ref][v]) {
			//printf("%d->%d [%d]\n", u, v, ref);
			dfs(ref, v, !co);
		}
	}
}

int fc[N];
int seen[N];
void go(int u) {
	if(seen[u]) return;
	seen[u] = true;
	int g[2] = {-1, -1};
	//printf("go %d\n", u);
	for(int v : adj[u])
		if(fc[v] != -1) {
			if(g[c[u][v]] != -1 && g[c[u][v]] != fc[v]) imp();
			g[c[u][v]] = fc[v];
			//printf("g[%d] = %d (%d)\n", c[u][v], fc[v], v);
		}
	assert(g[0] != -1 && g[1] != -1);
	for(int v : adj[u])
		fc[v] = g[c[u][v]];
	for(int v : adj[u])
		go(v);
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("mayors.in", "r", stdin);
	freopen("mayors.out", "w", stdout);
#endif
	int i, j, m;
	scanf("%d %d", &n, &m);
	memset(c, -1, sizeof c);
	memset(fc, -1, sizeof fc);
	for(i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
		madj[a][b] = madj[b][a] = 1;
		//printf("(%d, %d)\n", a, b);
	}
	if(n <= 3) {
		puts("Plan OK");
		for(i = 0; i < n; i++)
			printf("%c", "RGB"[i]);
		putchar('\n');
		return 0;
	}
	for(i = 0; i < n; i++)
		dfs(i, adj[i].front(), 0);
	fc[0] = 2;
	for(int v : adj[0])
		fc[v] = c[0][v];

	for(int v : adj[0])
		go(v);
	puts("Plan OK");
	for(i = 0; i < n; i++)
		putchar("RGB"[fc[i]]);
	putchar('\n');
}
