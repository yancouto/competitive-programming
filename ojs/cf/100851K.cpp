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
const int N = 100090;
int seen[N], S[N], sp[N];
vector<int> adj[N];
int nv[N];
int dfs(int u, int nv) {
	::nv[u] = nv;
	seen[u] = true;
	int sons = 0;
	for(int v : adj[u])
		if(!seen[v])
			dfs(v, nv + 1);
		else
			sp[v] = true, sons++;
	if(sons > 0 || adj[u].size() > 1) sp[u] = true;
}

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(nv[a] < nv[b]) swap(a, b);
	S[b] = a;
}

void dfs2(int u) {
	if(seen[u] == 2) return;
	seen[u] = 2;
	for(int v : adj[u]) {
		dfs2(v);
		if(!sp[u] && !sp[v])
			join(u, v);
	}
}

clock_t c;
int used[N];
int st[N], sn, n, tot;
vector<int> path[N];
void bt(int u) {
	if(double(clock() - c) / CLOCKS_PER_SEC > 1.93) { puts("There is no route, Karl!"); exit(0); }
	if(sn == tot && u == 0) {
		for(int i = 0; i < sn; i++)
			for(int v : path[st[i]])
				printf("%d ", v + 1);
		printf("1\n");
		exit(0);
	}
	if(used[u]) return;
	used[u] = true;
	st[sn++] = u;
	for(int v : adj[u])
		bt(find(v));
	sn--;
	used[u] = false;
}

int p[N];
int main() {
	c = clock();
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);
	int m, a, b, i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		S[i] = i, p[i] = i;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
	}
	dfs(0, 0);
	dfs2(0);
	sort(p, p + n, [](int i, int j) { return nv[i] < nv[j]; });
	for(i = 0; i < n; i++)
		path[find(p[i])].pb(p[i]), tot += S[i] == i;
	if(S[0] == 0)
		bt(0);
	puts("There is no route, Karl!");
}
