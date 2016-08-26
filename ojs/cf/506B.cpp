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

int S[N], sz[N], low[N], d[N], st[N], sn, tempo, comp[N], seen[N], bad[N];
vector<int> adj[N];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int tot = 0;

void dfs(int u) {
	seen[u] = 1;
	for(int v : adj[u])
		if(!seen[v]) {
			dfs(v);
		} else if(seen[v] == 1) {
			bad[find(u)] = 1;
		}
	seen[u] = 2;
}

int main() {
	int i, n, m, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		join(a, b);
	}
	for(i = 0; i < n; i++)
		if(!seen[i])
			dfs(i);
	for(i = 0; i < n; i++)
		if(find(i) == i) {
			tot += sz[i] - 1 + bad[i];
		}
	printf("%d\n", tot);
}
