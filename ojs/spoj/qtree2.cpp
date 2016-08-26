//RE
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
const int N = 11009;
vector<pii> adj[N]; int so[N], pai[N][15], cost[N], c[N], ev[N], nv[N];
int dfs(int u, int p, int nv) {
	int i; int &f = so[u];
	::nv[u] = nv;
	pai[u][0] = p;
	for(i = 1; i < 15; i++)
		pai[u][i] = pai[pai[u][i - 1]][i - 1];
	if(u != p) {
		for(i = 0; adj[u][i].fst != p; i++);
		ev[adj[u][i].snd] = u;
		cost[u] = c[adj[u][i].snd];
		adj[u].erase(adj[u].begin() + i);
	}
	for(pii p : adj[u])
		f += dfs(p.fst, u, nv + 1);
	return f;
}

int lca(int u, int v) {
	if(nv[u] > nv[v]) swap(u, v);
	for(int i = 14; i >= 0; i--)
		if(nv[pai[v][i]] >= nv[u])
			v = pai[v][i];
	if(u == v) return u;
	for(int i = 14; i >= 0; i--)
		if(pai[u][i] != pai[v][i])
			u = pai[u][i], v = pai[v][i];
	return pai[u][0];
}

int tr[N << 2], val[N];
inline int L(int i) { return i << 1; }
inline int R(int i) { return (i << 1) + 1; }
void build(int *tr, int i, int l, int r) {
	if(l == r) return (void) (tr[i] = val[l]);
	int m = (l + r) / 2;
	build(tr, L(i), l, m);
	build(tr, R(i), m + 1, r);
	tr[i] = max(tr[L(i)], tr[R(i)]);
}

int query(int *tr, int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return INT_MIN;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return max(query(tr, L(i), l, m, ql, qr), query(tr, R(i), m + 1, r, ql, qr));
}

void update(int *tr, int i, int l, int r, int x, int val) {
	if(l == r) return (void) (tr[i] = val);
	int m = (l + r) / 2;
	if(x <= m) update(tr, L(i), l, m, x, val);
	else update(tr, R(i), m + 1, r, x, val);
	tr[i] = max(tr[L(i)], tr[R(i)]);
}

int cur, tot, vc[N], vp[N], ch[N], cs[N];
int *ct[N];

void hld(int u) {
	tot++;
	vc[u] = cur;
	val[vp[u] = cs[cur]++] = cost[u];
	if(vp[u] == 0) ch[cur] = u;
	if(adj[u].empty()) return build(ct[cur] = tr + (tot - cs[cur]) * 4 - 1, 1, 0, cs[cur] - 1);
	int bi = adj[u].front().fst;
	for(pii p : adj[u])
		if(so[p.fst] > so[bi])
			bi = p.fst;
	hld(bi);
	for(pii p : adj[u])
		if(p.fst != bi) {
			cur++;
			hld(p.fst);
		}
}

int path(int u, int v) {
	int mx = 0;
	while(u != v) {
		int c = vc[u];
		if(c == vc[v]) return max(mx, query(ct[c], 1, 0, cs[c] - 1, vp[v] + 1, vp[u]));
		mx = max(mx, query(ct[c], 1, 0, cs[c] - 1, 0, vp[u]));
		u = pai[ch[c]][0];
	}
	return mx;
}

char s[100];
int main() {
	int i, n, a, b;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) cs[i] = 0, adj[i].clear(), so[i] = 1;
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d %d", &a, &b, &c[i]); a--; b--;
			adj[a].pb(pii(b, i));
			adj[b].pb(pii(a, i));
		}
		dfs(0, 0, 0);
		tot = cur = 0;
		hld(0);
		while(true) {
			scanf("%s", s);
			if(s[0] == 'D') break;
			scanf("%d %d", &a, &b);
			if(s[0] == 'C') update(ct[vc[ev[a-1]]], 1, 0, cs[vc[ev[a-1]]] - 1, vp[ev[a-1]], b);
			else {
				int l = lca(a - 1, b - 1);
				printf("%d\n", max(path(a - 1, l), path(b - 1, l)));
			}
		}
	}
}
