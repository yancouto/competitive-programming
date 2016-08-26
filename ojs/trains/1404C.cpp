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
const int N = 400009;
int root = 0, tn = 0;
int fst[N], lst[N];
int L[N], R[N], sz[N], lazy[N], par[N], mn[N], h[N], y[N], val[N], mh[N];

int acc(int u) {
	if(!u) return 0;
	h[u] += lazy[u];
	mh[u] += lazy[u];
	lazy[L[u]] += lazy[u];
	lazy[R[u]] += lazy[u];
	lazy[u] = 0;
	return u;
}

void calc(int u) {
	acc(u); acc(L[u]); acc(R[u]);
	mn[u] = u; mh[u] = h[u];
	if(mh[L[u]] < mh[u]) mn[u] = mn[L[u]], mh[u] = mh[L[u]];
	if(mh[R[u]] < mh[u]) mn[u] = mn[R[u]], mh[u] = mh[R[u]];
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	par[L[u]] = par[R[u]] = u; par[u] = 0;
}

int up(int u) {
	int tot = sz[L[u]];
	while(u && par[u]) {
		if(R[par[u]] == u) tot += 1 + sz[L[par[u]]];
		u = par[u];
	}
	return tot;
}

void split(int u, int s, int &l, int &r) {
	if(!acc(u)) return (void) (l = r = 0);
	if(s > sz[L[u]]) split(R[u], s - sz[L[u]] - 1, l, r), R[u] = l, l = u;
	else split(L[u], s, l, r), L[u] = r, r = u;
	calc(u);
}

int merge(int l, int r) {
	if(!acc(l) || !acc(r)) return max(l, r);
	int u;
	if(y[l] > y[r]) R[l] = merge(R[l], r), u = l;
	else L[r] = merge(l, L[r]), u = r;
	calc(u);
	return u;
}

vector<int> adj[N];
void show(int root) {
	if(!root) return;
	show(L[root]);
	printf("%d ", val[root]);
	show(R[root]);
	if(L[root]) assert(par[L[root]] == root);
	if(R[root]) assert(par[R[root]] == root);
}

int node(int x, int hh, int v) {
	//printf("new node %d val %d\n", x, v);
	sz[x] = 1; h[x] = hh;
	val[x] = v; mn[x] = x; mh[x] = hh;
	return x;
}

void dfs(int u, int hh) {
	root = merge(root, node(++tn, hh, u));
	//printf("after %d: ", u); show(root); putchar('\n');
	fst[u] = tn;
	for(int v : adj[u]) {
		dfs(v, hh + 1);
		root = merge(root, node(++tn, hh, u));
		//printf("after %d: ", u); show(root); putchar('\n');
	}
	root = merge(root, node(++tn, hh, u));
	//printf("after %d: ", u); show(root); putchar('\n');
	lst[u] = tn;
}

inline int get_h(int &root, int u) {
	int t1, t2, t3;
	split(root, up(u), t1, t2);
	split(t2, 1, t2, t3);
	int ans = h[t2];
	root = merge(t1, merge(t2, t3));
	return ans;
}

int main() {
	freopen("lca.in", "r", stdin);
	freopen("lca.out", "w", stdout);
	int i, u, v, x, n; char q;
	for(i = 0; i < N; i++) y[i] = i, sz[N] = 1;
	sz[0] = 0; mh[0] = h[0] = INT_MAX;
	random_shuffle(y, y + N);
	scanf("%d", &n);
	for(i = 1; i < n; i++) {
		scanf("%d", &x);
		adj[x - 1].pb(i);
	}
	dfs(0, 0);
	//show(root); putchar('\n');
	for_tests(qn, qi) {
		scanf(" %c %d %d", &q, &u, &v); u--; v--;
		if(q == 'Q') {
			int l = up(fst[u]), r = up(fst[v]), t1, t2, t3;
			if(l > r) swap(l, r);
			//printf("query from %d to %d\n", l, r);
			split(root, l, t1, t2);
			split(t2, r - l + 1, t2, t3);
			printf("%d\n", val[mn[t2]] + 1);
			root = merge(merge(t1, t2), t3);
		} else {
			int l = up(fst[u]), r = up(lst[u]), t1, t2, t3;
			//printf("l[%d] = %d r[%d] = %d\n", u, l, u, r);
			split(root, l, t1, t2);
			split(t2, r - l + 1, t2, t3);
			root = merge(t1, t3);
			int o = up(fst[v]);
			split(root, o + 1, t1, t3);
			lazy[t2] += get_h(t1, fst[v]) - get_h(t2, mn[t2]) + 1;
			root = merge(merge(t1, t2), merge(node(++tn, h[fst[v]], v), t3));
			//show(root); putchar('\n');
		}
	}
}
