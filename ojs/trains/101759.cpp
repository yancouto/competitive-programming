#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000021;
inline ll mod(ll x) { return x % modn; }
const ll modn2 = 1000000033;
inline ll mod2(ll x) { return x % modn2; }
const int N = 300109;
inline int he(int u) { return u + 200020; }

int sz[N], L[N], R[N], p[N], val[N], y[N], root, sn = 1;
ll hs[N], hs2[N], p2[N], p5[N];
vector<int> adj[N];

int nx[N], pr[N];

//ll mult(ll a, ll b) {
//	ll r = 0;
//	for(; b; b >>= 1, a = mod(a + a))
//		if(b & 1)
//			r = mod(r + a);
//	return r;
//}

int calc(int u) {
	if(!u) return 0;
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	hs[u] = mod(hs[L[u]] + (mod(ll(val[u]) + hs[R[u]] * 3ll) * p2[sz[L[u]]]));
	hs2[u] = mod2(hs2[L[u]] + (mod2(ll(val[u]) + hs2[R[u]] * 5ll) * p5[sz[L[u]]]));
	p[L[u]] = p[R[u]] = u;
	p[u] = 0;
	return u;
}

int merge(int l, int r) {
	if(!l || !r) return l + r;
	int u;
	if(y[l] > y[r]) u = l, R[u] = merge(R[u], r);
	else u = r, L[u] = merge(l, L[u]);
	return calc(u);
}

void split(int u, int s, int &l, int &r) {
	if(!u) return (void) (l = r = 0);
	if(s > sz[L[u]]) split(R[u], s - sz[L[u]] - 1, l, r), R[u] = l, l = u;
	else split(L[u], s, l, r), L[u] = r, r = u;
	calc(u);
}

void add_end(int u, int sn) {
	nx[sn] = he(u); pr[sn] = pr[he(u)];
	pr[nx[sn]] = sn; nx[pr[sn]] = sn;
}

int left(int u) {
	if(!u) return 0;
	int all = sz[L[u]];
	for(; p[u]; u = p[u])
		if(R[p[u]] == u)
			all += 1 + sz[L[p[u]]];
	return all;
}

void add(int u, int v) {
	sz[sn] = 1;
	val[sn] = v; hs[sn] = hs2[sn] = v;
	root = merge(root, sn);
	add_end(u, sn);
	sn++;
}

void dfs(int u) {
	add(u, 0);
	for(int v : adj[u]) { dfs(v); add(u, 1); }
}

void test(int u) {
	if(!u) return;
	test(L[u]);
	printf("%d ", val[u]);
	test(R[u]);
}

inline int getnum() {
	char c;
	while(isspace(c = getchar_unlocked()));
	int x = c - '0';
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + c - '0';
	return x;
}

int main() {
	int i, a, b, n, m, k, x;
	root = 0;
	p2[0] = p5[0] = 1;
	for(i = 1; i < N; i++)
		p2[i] = mod(p2[i - 1] * 3ll),
		p5[i] = mod2(p5[i - 1] * 5ll);
	for(i = 0; i < N; i++)
		y[i] = i;
	random_shuffle(y, y + N);
	n = getnum(), m = getnum();
	//scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) nx[he(i)] = pr[he(i)] = he(i);
	for(i = 0; i < n; i++) {
		//scanf("%d", &k);
		k = getnum();
		while(k--) { x = getnum(); /*scanf("%d", &x);*/ adj[i].pb(x - 1); }
	}
	dfs(0);
	map<pii, int> s;
	s[pii(hs[root], hs2[root])] = 0;
	for(i = 0; i < m; i++) {
		a = getnum() - 1; b = getnum() - 1;
		//scanf("%d %d", &a, &b); a--; b--;
		int t1, t2, t3, t4;
		int fst = left(nx[he(a)]), lst = left(pr[he(a)]);
		split(root, fst, t1, t2);
		split(t2, lst - fst + 1, t2, t3);
		split(t3, 1, t3, t4);
		pr[nx[t3]] = pr[t3]; nx[pr[t3]] = nx[t3];
		root = merge(t1, t4);
		split(root, left(pr[he(b)]) + 1, t1, t4);
		add_end(b, t3);
		root = merge(merge(t1, t2), merge(t3, t4));
		pii p(hs[root], hs2[root]);
		if(s.count(p)) { printf("%d %d\n", s[p], i + 1); return 0; }
		s[p] = i + 1;
	}
	puts("-1");
}
