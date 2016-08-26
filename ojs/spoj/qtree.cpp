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
const int N = 10009;

vector<pii> adj[N];
int nv[N], c[N], so[N], pai[N];

int dfs(int u, int p, int c, int nv) {
	::nv[u] = nv; ::c[u] = c; so[u] = 1; pai[u] = p;
	if(p != -1) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, pii(p, c)));
	for(int i = 0; i < adj[u].size(); i++)
		so[u] += dfs(adj[u][i].fst, u, adj[u][i].snd, nv + 1);
	return so[u];
}

int L[N << 2], R[N << 2], tr[N << 2], pr[N], tn;

void build(int i, int l, int r) {
	if(l == r) return (void)(tr[i] = pr[l]);
	int m = (l + r) / 2;
	build(L[i] = ++tn, l, m);
	build(R[i] = ++tn, m + 1, r);
	tr[i] = max(tr[L[i]], tr[R[i]]);
}

void upd(int i, int l, int r, int x, int val) {
	if(l == r) return (void)(tr[i] = val);
	int m = (l + r) / 2;
	if(x <= m) upd(L[i], l, m, x, val);
	else upd(R[i], m + 1, r, x, val);
	tr[i] = max(tr[L[i]], tr[R[i]]);
}

int get(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return INT_MIN;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return max(get(L[i], l, m, ql, qr), get(R[i], m + 1, r, ql, qr));
}

int vc[N], ct[N], cs[N], vp[N];

void hld(int u, int cur) {
	vc[u] = cur;
	vp[u] = cs[cur]++;
	pr[vp[u]] = c[u];
	if(adj[u].empty()) return build(ct[cur] = ++tn, 0, cs[cur] - 1);
	int bi = adj[u].front().fst;
	for(int i = 0; i < adj[u].size(); i++)
		if(so[adj[u][i].fst] >= so[bi])
			bi = adj[u][i].fst;
	hld(bi, cur);
	for(int i = 0; i < adj[u].size(); i++)
		if(adj[u][i].fst != bi)
			hld(adj[u][i].fst, adj[u][i].fst);
}

int query(int a, int b) {
	int r = INT_MIN;
	while(vc[a] != vc[b]) {
		if(nv[vc[a]] < nv[vc[b]]) swap(a, b);
		r = max(r, get(ct[vc[a]], 0, cs[vc[a]] - 1, 0, vp[a]));
		a = pai[vc[a]];
	}
	if(vp[a] > vp[b]) swap(a, b);
	if(a != b) r = max(r, get(ct[vc[a]], 0, cs[vc[a]] - 1, vp[a] + 1, vp[b]));
	return r;
}

int a[N], b[N];
char s[100];
int main() {
	int i, n, c, x, y;
	for_tests(t, tt) {
		scanf("%d", &n);
		tn = 0;
		for(i = 0; i < n; i++) adj[i].clear();
		memset(cs, 0, sizeof cs);
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d %d", &a[i], &b[i], &c); a[i]--; b[i]--;
			adj[a[i]].pb(pii(b[i], c));
			adj[b[i]].pb(pii(a[i], c));
		}
		dfs(0, -1, 0, 0);
		hld(0, 0);
		while(true) {
			scanf("%s", s);
			if(s[0] == 'D') break;
			scanf("%d %d", &x, &y); x--;
			if(s[0] == 'C') {
				int u = a[x];
				if(nv[b[x]] > nv[u]) u = b[x];
				upd(ct[vc[u]], 0, cs[vc[u]] - 1, vp[u], y);
			} else
				printf("%d\n", query(x, y - 1));
		}
	}
}
