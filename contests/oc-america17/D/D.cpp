#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back


const int N = 212345;

int sz[N], v[N], p[N], ci[N], cs[N], cp[N];
int mrk[N];
vector<int> adj[N], cv[N];

int per[N];

int dfs(int u) {
	sz[u] = 1;
	for(int v : adj[u]) sz[u] += dfs(v);
	return sz[u];
}

set<int> s[N];
const int M = N * 45;
int build[M], L[M], R[M], en = 1;
int seg[N];
int build_build(int l, int r) {
	int i = en++;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build_build(l, m);
	R[i] = build_build(m + 1, r);
	return i;
}

void add(int i, int l, int r, int ql, int qr, int x) {
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) { build[i] += x; return; }
	int m = (l + r) / 2;
	add(L[i], l, m, ql, qr, x);
	add(R[i], m + 1, r, ql, qr, x);
}

int query(int i, int l, int r, int p) {
	if(l == r) return build[i];
	int m = (l + r) / 2;
	if(p <= m) return build[i] + query(L[i], l, m, p);
	else return build[i] + query(R[i], m + 1, r, p);
}

void hld(int u, int pp) {
	ci[u] = cs[pp]++;
	cp[u] = pp;
	cv[pp].pb(u);
	if(adj[u].empty()) {
		// alguma merda
		seg[pp] = build_build(0, cs[pp] - 1);
		return;
	}
	int mx = adj[u].front();
	for(int v : adj[u])
		if(sz[v] > sz[mx])
			mx = v;
	hld(mx, pp);
	for(int v : adj[u])
		if(v != mx)
			hld(v, v);
}

int acc[N];
int dp[N];

int nx(int u, int add) {
	if(u == -1) return -1;
	auto it = s[cp[u]].upper_bound(ci[u]);
	//for(int x : s[cp[u]]) printf("%d ", x); putchar('\n');
	int a = (it == s[cp[u]].begin()? 0 : *prev(it));
	//printf("add(%d, %d, %d, %d, %d, %d)\n\n", seg[cp[u]], 0, cs[cp[u]] - 1, a, ci[u], add);
	::add(seg[cp[u]], 0, cs[cp[u]] - 1, a, ci[u], add);
	if(it == s[cp[u]].begin()) return nx(p[cp[u]], add);
	return cv[cp[u]][*prev(it)];
}

void go(int u) {
	//printf("get[%d]\n", ci[u]);
	dp[u] = query(seg[cp[u]], 0, cs[cp[u]] - 1, ci[u]) + 1;
	//printf("dp[%d] = %d\n", u, dp[u]);
	int add = 1, ou = u;
	while(true) {
		//printf("add(%d, %d, %d, %d, %d, %d)\n\n", seg[cp[u]], 0, cs[cp[u]] - 1, ci[u], ci[u], -add);
		::add(seg[cp[u]], 0, cs[cp[u]] - 1, ci[u], ci[u], -add);
		int v = nx(u, add);
		if(v == -1) break;
		int b = query(seg[cp[v]], 0, cs[cp[v]] - 1, ci[v]);
		if(b <= dp[v]) break;
		s[cp[v]].erase(ci[v]);
		add = b - dp[v];
		u = v;
	}
	s[cp[ou]].insert(ci[ou]);
}


int main () {
	int i, n;
	scanf("%d", &n);
	v[0] = 1000000009; p[0] = -1;
	for(i = 1; i <= n; i++) {
		scanf("%d %d", &v[i], &p[i]);
		adj[p[i]].pb(i);
		per[i] = i;
	}
	dfs(0);
	hld(0, 0);
	sort(per, per + n + 1, [](int i, int j) {
		if(v[i] != v[j]) return v[i] < v[j];
		return sz[i] > sz[j];
	});
	for(i = 0; i <= n; i++)
		go(per[i]);
	printf("%d\n", dp[0] - 1);
}
