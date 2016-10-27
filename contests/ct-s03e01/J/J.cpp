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
const int N = 1123, M = (512 * 512 + 512 * 2) * 2;
vector<int> adj[N];
int tempo;
int seen[N], en;
int xh[N], yh[N], xv[N], yv[N], szv[N], szh[N];
char sh[N][N], sv[N][N];

int f[M], to[M];

int dfs(int s, int t) {
	if(s == t) return true;
	seen[s] = tempo;
	for(int e : adj[s])
		if(seen[to[e]] < tempo && (e & 1) - f[e] > 0 && dfs(to[e], t)) {
			f[e]++;
			f[e ^ 1]--;
			return true;
		}
	return false;
}

int max_flow(int s, int t) {
	int f = 0; tempo++;
	while(dfs(s, t)) f++, tempo++;
	return f;
}

void add_edge(int a, int b) {
	to[en] = a; f[en] = 0; adj[b].pb(en++);
	to[en] = b; f[en] = 0; adj[a].pb(en++);
}

int main() {
	int i, j, t, h, v;
	scanf("%d", &t);
	while(t--) {
		en = 2;
		scanf("%d %d", &h, &v);
		for(i = 0; i < h; i++) scanf("%d %d %s", &xh[i], &yh[i], sh[i]), szh[i] = strlen(sh[i]);
		for(i = 0; i < v; i++) scanf("%d %d %s", &xv[i], &yv[i], sv[i]), szv[i] = strlen(sv[i]);
		for(i = 0; i < h; i++)
			for(j = 0; j < v; j++) {
				int x = xv[j], y = yh[i];
				if(x >= xh[i] && x < xh[i] + szh[i] && y >= yv[j] && y < yv[j] + szv[j] && sh[i][x - xh[i]] != sv[j][y - yv[j]]) {
					//printf("%d->%d\n", i, j);
					add_edge(i, h + j);
				}
			}
		for(i = 0; i < h; i++) add_edge(N - 1, i);
		for(i = 0; i < v; i++) add_edge(i + h, N - 2);
		printf("%d\n", h + v - max_flow(N - 1, N - 2));
		for(i = 0; i < N; i++) adj[i].clear();
	}
}
