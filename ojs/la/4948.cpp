#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int V;
int sn;

const int N = 1123456;
const int M = (N * 34);

int L[M], R[M]; ll tr[M];

int seg[N];

struct edge {
	int a, b, w;
	bool operator < (edge o) const { return w < o.w; }
} e[N];

int build(int l, int r) {
	int i = sn++;
	tr[i] = e[l].w; L[i] = R[i] = 0;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	tr[i] = tr[L[i]] + tr[R[i]];
	return i;
}

int copy(int i) {
	int j = sn++;
	tr[j] = tr[i];
	L[j] = L[i];
	R[j] = R[i];
	return j;
}

int add(int i, int l, int r, int p, ll x) {
	int j = copy(i);
	tr[j] += x;
	if(l == r) return j;
	int m = (l + r) / 2;
	if(p <= m) L[j] = add(L[j], l, m, p, x);
	else R[j] = add(R[j], m + 1, r, p, x);
	return j;
}

ll query(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return query(L[i], l, m, ql, qr) + query(R[i], m + 1, r, ql, qr);
}

int nx[N * 2], pr[N * 2], he[N], to[N * 2], ei[2 * N], we[2 * N];

int m;
int go(int u, int p, int v, int mn, int mnv) {
	if(u == v) return mn;
	for(int e = he[u]; e; e = nx[e]) {
		if(to[e] == p) continue;
		int mn2 = we[e] > mnv? u : mn;
		int a = go(to[e], u, v, mn2, max(mnv, we[e]));
		if(a == -1) continue;
		if(a == u) {
			seg[V] = add(seg[V], 0, m - 1, ei[e], -we[e]);
			pr[nx[e]] = pr[e];
			if(pr[e])
				nx[pr[e]] = nx[e];
			else
				he[u] = nx[e];
			pr[nx[e ^ 1]] = pr[e ^ 1];
			if(pr[e ^ 1])
				nx[pr[e ^ 1]] = nx[e ^ 1];
			else
				he[to[e]] = nx[e ^ 1];
		}
		return a;
	}
	return -1;
}

int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

inline bool join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return false;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	return true;
}

int en;
void add_edge(int a, int b, int w, int i) {
	to[en] = b; nx[en] = he[a]; pr[he[a]] = en; we[en] = w; pr[en] = 0; ei[en] = i; he[a] = en++;
	to[en] = a; nx[en] = he[b]; pr[he[b]] = en; we[en] = w; pr[en] = 0; ei[en] = i; he[b] = en++;
}

int main() {
	int i, n;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < m; i++)
			scanf("%d %d %d", &e[i].a, &e[i].b, &e[i].w), e[i].a--, e[i].b--;
		sort(e, e + m);
		for(i = 0; i < n; i++) S[i] = i, sz[i] = 1, he[i] = 0;
		en = 2;
		sn = 1;
		seg[m] = build(0, m - 1);
		for(i = m - 1; i >= 0; i--) {
			seg[i] = seg[i + 1];
			V = i;
			if(!join(e[i].a, e[i].b)) {
				go(e[i].a, -1, e[i].b, -1, INT_MIN);
			}
			add_edge(e[i].a, e[i].b, e[i].w, i);
		}
		int q; ll ql, qr;
		scanf("%d", &q);
		ll ans = 0;
		for(i = 0; i < q; i++) {
			scanf("%lld %lld", &ql, &qr);
			ql -= ans; qr -= ans;
			edge e2 = {-1, -1, (int) ql};
			int l = lower_bound(e, e + m, e2) - e;
			e2.w = qr;
			int r = upper_bound(e, e + m, e2) - e;
			ans = (l != r? query(seg[l], 0, m - 1, l, r - 1) : 0);
			printf("%lld\n", ans);
		}
	}
}
