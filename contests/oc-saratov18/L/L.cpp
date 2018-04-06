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

struct no {
	int u; ll d; int p;
	bool operator < (no o) const { return d > o.d; }
};

const int N = 212345;
vector<int> adj[N], rev[N];
vector<pii> adj_[N];
ll d[N];
int low[N], sz[N];
map<pii, int> mrk;
int ans[N], seen[N];
int h[N];

const int M = 212345 * 4;
int tr[M], qt[M], lz[M];

void build(int i, int l, int r) {
	qt[i] = r - l + 1;
	if(l == r) return;
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

void unlaze(int i, int l, int r) {
	if(lz[i] == 0) return;
	tr[i] += lz[i];
	if(l != r) {
		lz[2 * i] += lz[i];
		lz[2 * i + 1] += lz[i];
	}
	lz[i] = 0;
}

void add(int i, int l, int r, int ql, int qr, int x) {
	//if(i == 1) printf("(%d, %d) += %d\n", ql, qr, x);
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
	qt[i] = qt[2 * i];
	tr[i] = tr[2 * i];
	if(tr[2 * i + 1] < tr[i]) {
		tr[i] = tr[2 * i + 1];
		qt[i] = qt[2 * i + 1];
	} else if(tr[2 * i + 1] == tr[i])
		qt[i] += qt[2 * i + 1];
}

int get(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return (tr[i]? 0 : qt[i]);
	int m = (l + r) / 2;
	int ans = get(2 * i, l, m, ql, qr) + get(2 * i + 1, m + 1, r, ql, qr);
	//if(i == 1) printf("get (%d, %d) = %d\n", ql, qr, ans);
	return ans;
}

int tempo = 0;
int p[N];
int n;
int f[N];

void go(int u, int p) {
	::p[u] = p;
	d[u] = tempo++;
	seen[u] = 2;
	for(int v : adj[u]) {
		if(seen[v] == 2) continue;
		go(v, u);
	}
	f[u] = tempo - 1;
	//printf("%d: [%d, %d]\n", u + 1, d[u], f[u]);
}

void go2(int u) {
	//printf("enter %d\n", u + 1);
	seen[u] = 3;
	for(int v : adj[u]) {
		if(seen[v] == 3) {
			if(seen[v] == p[u]) continue;
			add(1, 0, n - 1, d[v], f[v], -1);
		} else
			go2(v);
	}
	for(int v : rev[u]) {
		if(v == p[u]) continue;
		add(1, 0, n - 1, d[u], f[u], 1);
	}
	if(u) {
		ans[mrk[pii(u, p[u])]] = get(1, 0, n - 1, d[u], f[u]);
	}
	//printf("exit %d\n", u + 1);
}


int main() {
	int i, m, a, b, c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		adj_[a].pb(pii(b, c));
		adj_[b].pb(pii(a, c));
		mrk[pii(a, b)] = mrk[pii(b, a)] = i;
	}
	priority_queue<no> pq;
	pq.push(no{0, 0, -1});
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(seen[x.u]) {
			if(x.d == d[x.u] && x.p != -1) {
				adj[x.p].pb(x.u);
				rev[x.u].pb(x.p);
				//adj[x.u].pb(x.p);
			}
			continue;
		} else {
			if(x.p != -1) {
				adj[x.p].pb(x.u);
				rev[x.u].pb(x.p);
				//adj[x.u].pb(x.p);
			}
			seen[x.u] = 1, d[x.u] = x.d;
		}
		for(pii e : adj_[x.u])
			pq.push(no{e.fst, x.d + e.snd, x.u});
	}
	go(0, 0);
	build(1, 0, n - 1);
	go2(0);
	for(i = 0; i < m; i++)
		printf("%d\n", ans[i]);
}
