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
const int N = 100009;
int so[N], pai[N];
vector<int> adj[N];

int dfs(int u, int p) {
	pai[u] = p;
	if(p != -1) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
	for(int v : adj[u])
		so[u] += dfs(v, u);
	return ++so[u];
}

int cur, all, BIT[5*N], tot[N], cs[N], vp[N], cv[N], ch[N], vc[N], *bit[N];
void hld(int u) {
	vp[u] = cs[cur]++;
	vc[u] = cur;
	if(vp[u] == 0) ch[cur] = u;
	cv[tot[cur] + vp[u]] = u;
	if(adj[u].empty()) {
		bit[cur] = BIT + all;
		all += cs[cur] + 4;
		tot[cur + 1] = tot[cur] + cs[cur];
		return;
	}
	int bi = adj[u].front();
	for(int v : adj[u])
		if(so[v] > so[bi])
			bi = v;
	hld(bi);
	for(int v : adj[u])
		if(bi != v) {
			cur++;
			hld(v);
		}
}

int get(int c, int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[c][i];
	return sum;
}
inline int get(int c, int i, int j) { return get(c, j) - get(c, i - 1); }

void add(int c, int i, int x) {
	for(i += 2; i < cs[c] + 4; i += (i & -i))
		bit[c][i] += x;
}

void tog(int u) {
	add(vc[u], vp[u], 1 - 2*get(vc[u], vp[u], vp[u]));
}

int solve(int u) {
	int g = -1;
	while(u != -1) {
		if(get(vc[u], vp[u])) g = u;
		u = pai[ch[vc[u]]];
	}
	if(g == -1) return -1;
	int l = 0, r = vp[g];
	while(l < r) {
		int m = (l + r) / 2;
		if(get(vc[g], m)) r = m;
		else l = m + 1;
	}
	return cv[tot[vc[g]] + l] + 1;
}

int main() {
	int i, n, q, a, b;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(0, -1);
	hld(0);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &a, &b); b--;
		if(a) printf("%d\n", solve(b));
		else tog(b);
	}
}
