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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;

const int N = 112345;
int sz[N], a[N], b[N], c[N], p[N];
vector<int> adj[N];

int dfs(int u, int p) {
	::p[u] = p;
	sz[u] = 1;
	if(p != -1) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
	for(int v : adj[u])
		sz[u] += dfs(v, u);
	return sz[u];
}

const int M = 5 * N;
int L[M], R[M], en = 1;
int mn[M], ct[M], lz[M];

int build(int l, int r) {
	int i = en++;
	mn[i] = 0; ct[i] = r - l + 1;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	return i;
}

void unlaze(int i, int l, int r) {
	if(lz[i] == 0) return;
	mn[i] += lz[i];
	if(l != r) {
		lz[L[i]] += lz[i];
		lz[R[i]] += lz[i];
	}
	lz[i] = 0;
}

void upd(int i) {
	mn[i] = mn[L[i]];
	ct[i] = ct[L[i]];
	if(mn[R[i]] < mn[i]) {
		mn[i] = mn[R[i]];
		ct[i] = ct[R[i]];
	} else if(mn[R[i]] == mn[i]) {
		ct[i] += ct[R[i]];
	}
}

void add(int i, int l, int r, int ql, int qr, int z) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = z;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(L[i], l, m, ql, qr, z);
	add(R[i], m + 1, r, ql, qr, z);
	upd(i);
}

int pi[N], pp[N], seg[N], val[N], all[N];
void go(int u, int pi, int pp) {
	all[pp]++;
	::pi[u] = pi; ::pp[u] = pp;
	if(adj[u].empty()) {
		seg[pp] = build(0, pi);
		val[pp] = all[pp];
		return;
	}
	int mx = adj[u].front();
	for(int v : adj[u])
		if(sz[v] > sz[mx])
			mx = v;
	go(mx, pi + 1, pp);
	for(int v : adj[u]) {
		if(v == mx) continue;
		go(v, 0, v);
	}
}

int cur;

void solve(int a, int b, int z) {
	//printf("[%d,%d,%d]\n", a+1, b+1, z);
	while(a != b) {
		if(sz[pp[b]] < sz[pp[a]] || (pp[a] == pp[b] && sz[b] < sz[a])) swap(a, b);
		//printf("upping %d\n", a+1);
		int r = pi[a];
		int l = pp[a] == pp[b]? pi[b] + 1 : 0;
		//printf("add %d to %d..%d\n", z, l, r);
		add(seg[pp[a]], 0, all[pp[a]] - 1, l, r, z);
		int nv = mn[seg[pp[a]]] == 0? ct[seg[pp[a]]] : 0;
		//printf("from %d to %d\n", val[pp[a]], nv);
		cur = cur - val[pp[a]] + nv;
		val[pp[a]] = nv;
		if(pp[a] == pp[b]) break;
		a = p[pp[a]];
	}
}

int main() {
	int i, m, q;
	rd(n); rd(m);
	for(i = 0; i < m; i++) {
		rd(a[i]); rd(b[i]); rd(c[i]); a[i]--; b[i]--;
		if(c[i] == 0) {
			adj[a[i]].pb(b[i]);
			adj[b[i]].pb(a[i]);
		}
	}
	dfs(0, -1);
	go(0, 0, 0);
	set<pii> ed;
	cur = n - 1;
	for(i = 0; i < m; i++)
		if(c[i])
			solve(a[i], b[i], 1), ed.insert(pii(min(a[i], b[i]), max(a[i], b[i])));
	printf("%d\n", cur);
	rd(q);
	while(q--) {
		int a, b;
		rd(a); rd(b); a--; b--;
		if(a > b) swap(a, b);
		if(ed.count(pii(a, b))) {
			ed.erase(pii(a, b));
			solve(a, b, -1);
		} else {
			ed.insert(pii(a, b));
			solve(a, b, 1);
		}
		printf("%d\n", cur);
	}
}
