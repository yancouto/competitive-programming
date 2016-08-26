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

vector<int> adj[N], adj2[N];
int q[N], dist[N];
void bfs(int s) {
	int a = 0, b = 0;
	q[b++] = s;
	dist[s] = 0;
	while(a < b) {
		int u = q[a++];
		for(int v : adj[u])
			if(dist[v] >= dist[u] + 1) {
				if(dist[v] > dist[u] + 1) dist[v] = dist[u] + 1, q[b++] = v;
				adj2[v].pb(u);
			}
	}
}

int mrk[N], t;
void dfs(int u) {
	if(mrk[u] & t) return;
	mrk[u] |= t;
	for(int v : adj2[u])
		dfs(v);
}

int main() {
	int i, n, m, a, b, A, B, s;
	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &s, &A, &B); s--; A--; B--;
	for(i = 0; i < n; i++) dist[i] = INT_MAX;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	bfs(s);
	t++; dfs(A);
	t++; dfs(B);
	int mx = INT_MIN;
	for(i = 0; i < n; i++)
		if(mrk[i] == 3)
			mx = max(mx, dist[i]);
	printf("%d\n", mx);
}
