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

const int N = 512345;
const int M = N * 5;
int a[N], en = 2;
int seg[N];

int tr[M], L[M], R[M];
int lz[M], on[M];

int build(int l, int r) {
	int i = en++;
	tr[i] = lz[i] = on[i] = 0;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	return i;
}

vector<int> top;
int p[N];
int tempo = 0;
int l[N], r[N];
int l2[N], r2[N];
vector<int> adj[N];
int n;
void go(int u, int p) {
	//l[u] = ++tempo;
	//top.pb(u);
	//for(int v : adj[u])
	//	if(v != p)
	//		go(v, u);
	//r[u] = tempo - 1;
	//return;
	stack<int> st;
	st.push(0);
	for(int i = 0; i < n; i++) r[i] = l[i] = -10;
	while(!st.empty()) {
		u = st.top(); st.pop();
		assert(l[u] == -10);
		l[u] = ++tempo;
		top.pb(u);
		for(int v : adj[u])
			if(l[v] == -10)
				st.push(v);
	}
	for(int i = n - 1; i >= 0; i--) {
		int j = top[i];
		r[j] = l[j] - 1;
		for(int v : adj[j]) {
			if(r[v] != -10)
				r[j] = max(r[j], r[v]);
		}
	}
}
void go2(int u, int p) {
	//l2[u] = ++tempo;
	//top.pb(u);
	//for(int v : adj[u])
	//	if(v != p)
	//		go2(v, u);
	//r2[u] = tempo - 1;
	//return;
	stack<int> st;
	st.push(0);
	for(int i = 0; i < n; i++) r2[i] = l2[i] = -10;
	while(!st.empty()) {
		u = st.top(); st.pop();
		l2[u] = ++tempo;
		top.pb(u);
		for(int v : adj[u])
			if(l2[v] == -10)
				st.push(v);
	}
	for(int i = n - 1; i >= 0; i--) {
		int j = top[i];
		r2[j] = l2[j] - 1;
		for(int v : adj[j])
			if(r2[v] != -10)
				r2[j] = max(r2[j], r2[v]);
	}
}

void unlaze(int i, int l, int r) {
	if(lz[i] == 0) return;
	if(!on[i]) { lz[i] = 0; return; }
	if(l == r) tr[i] += lz[i];
	else {
		if(on[L[i]] > 0) lz[L[i]] += lz[i];
		if(on[R[i]] > 0) lz[R[i]] += lz[i];
	}
	lz[i] = 0;
}

void add(int i, int l, int r, int ql, int qr, int x) {
	unlaze(i, l, r);
	if(l > qr || r < ql || !on[i]) return;
	if(l >= ql && r <= qr) {
		lz[i] = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(L[i], l, m, ql, qr, x);
	add(R[i], m + 1, r, ql, qr, x);
}

void turn_on(int i, int l, int r, int p) {
	unlaze(i, l, r);
	if(l == r) return (void) (on[i] = 1);
	int m = (l + r) / 2;
	if(p <= m) turn_on(L[i], l, m, p);
	else turn_on(R[i], m + 1, r, p);
	on[i] = on[L[i]] + on[R[i]];
}

int query(int i, int l, int r, int p) {
	unlaze(i, l, r);
	if(l == r) return tr[i];
	int m = (l + r) / 2;
	if(p <= m) return query(L[i], l, m, p);
	else return query(R[i], m + 1, r, p);
}

// somar g em todos os caras com valor <= k entre l e r
struct qu {
	int g, k, l, r;
	bool operator < (qu o) const { return k < o.k; }
};
int ans[N], p2[N];


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

int main() {
	int i, k, a, b;
	for_tests(t, tt) {
		en = 2;
		rd(n);
		for(i = 0; i < n; i++) adj[i].clear();
		top.clear(); tempo = 0;
		for(i = 0; i < n - 1; i++) {
			rd(a); rd(b);
			a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		go(0, -1);
		for(i = 0; i < n; i++)
			p[top[i]] = i;
		vector<int> otop = top;
		top.clear();
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < n - 1; i++) {
			rd(a); rd(b);
			a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		tempo = 0;
		go2(0, -1);
		for(i = 0; i < n; i++) top[i] = p[top[i]];
		for(i = 0; i < n; i++) p2[top[i]] = i;
		//seg[0] = build(0, N - 1);
		//for(i = 1; i <= n; i++)
		//	seg[i] = add1(seg[i - 1], 0, N - 1, top[i - 1]);
		vector<qu> vq;
		for(i = 0; i < n; i++) {
			if(l[i] > r[i] || l2[i] > r2[i]) continue;
			//ans += query(seg[r2[i] + 1], 0, N - 1, l[i], r[i]);
			vq.pb({1, r[i], l2[i], r2[i]});
			if(l[i])
				vq.pb({-1, l[i] - 1, l2[i], r2[i]});
			//ans -= query(seg[l2[i]], 0, N - 1, l[i], r[i]);
		}
		sort(vq.begin(), vq.end());
		int seg = build(0, n - 1);
		int ck = -1;
		for(qu q : vq) {
			while(ck < q.k)
				turn_on(seg, 0, n - 1, p2[++ck]);
			add(seg, 0, n - 1, q.l, q.r, q.g);
		}
		for(i = 0; i < n; i++)
			ans[otop[top[i]]] = query(seg, 0, n - 1, i);
		for(i = 0; i < n; i++) printf("%d ", ans[i]);
		putchar('\n');
	}
}
