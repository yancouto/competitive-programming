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
#define left saijdalsijd

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

const int mx = 100009;
const int N = 1000009, M = 4 * N;
ll tr[M]; int sz[M], L[M], R[M], seg[N];
int en = 1;

vector<int> left;
void clear(int u) {
	if(!u) return;
	clear(L[u]);
	clear(R[u]);
	L[u] = R[u] = sz[u] = tr[u] = 0;
	left.pb(u);
}

void add(int &s, int l, int r, int p, ll val) {
	if(!s) {
		if(left.empty()) s = en++;
		else { s = left.back(); left.pop_back(); }
	}
	sz[s]++;
	if(l == r) {
		tr[s] += val;
		return;
	}
	int m = (l + r) / 2;
	if(p <= m) add(L[s], l, m, p, val);
	else add(R[s], m + 1, r, p, val);
	tr[s] = tr[L[s]] + tr[R[s]];
}

ll query(int &s, int l, int r, int ql, int qr) {
	if(!s || l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return tr[s];
	int m = (l + r) / 2;
	return query(L[s], l, m, ql, qr) + query(R[s], m + 1, r, ql, qr);
}

int n;

vector<int> S[N];
int p[N], c[N]; ll ans[N];
vector<int> adj[N];

void dfs(int u) {
	S[u].pb(u);
	add(seg[u], 1, mx, p[u], c[u]);
	for(int v : adj[u]) {
		dfs(v);
		if(sz[seg[v]] > sz[seg[u]]) swap(seg[u], seg[v]), S[u].swap(S[v]);
		for(int x : S[v]) add(seg[u], 1, mx, p[x], c[x]), S[u].pb(x);
		S[v].clear();
		clear(seg[v]);
	}
	if(p[u] > 1) ans[u] = query(seg[u], 1, mx, 1, p[u] - 1);
	else ans[u] = 0;
}

int main() {
	int i, j, a, r;
	rd(n);
	for(i = 0; i < n; i++) {
		scanf("%d %d %d", &a, &p[i], &c[i]);
		if(a == -1) r = i;
		else adj[a - 1].pb(i);
	}
	dfs(r);
	for(i = 0; i < n; i++) printf("%lld\n", ans[i]);
}
