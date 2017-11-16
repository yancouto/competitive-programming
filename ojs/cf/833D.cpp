#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, ll> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
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

inline ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(x * r);
	return r;
}

inline ll inv(ll x) { return fexp(x, modn - 2); }

#define ct first
#define ml second

const int MN = -212345, MX = 212345;

const int M = 112345 * 40;
int n;

vector<int> adj[N];
map<int, int> cl[N], co[N];

int cn_sz[N];
int cn_dep[N]; // depth on cent tree
int cn_dist[20][N]; // distance to centroid antecessor with given depth
vector<int> cn_adj[N];

int c1[20][N], c2[20][N];
ll ml[20][N];

int cn_getsz (int u, int p) {
	cn_sz[u] = 1;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_sz[u] += cn_getsz(v,u);
	}
	return cn_sz[u];
}

void cn_setdist (int u, int p, int depth, int dist, int A, int B, ll ml) {
	::ml[depth][u] = ml;
	c1[depth][u] = 2 * B - A;
	c2[depth][u] = B - 2 * A;
	cn_dist[depth][u] = dist;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_setdist(v, u, depth, dist+1);
	}
}

int cn_build (int u, int depth) {
	int siz = cn_getsz(u,u);
	int w = u;
	do {
		u = w;
		for (int v : adj[u]) {
			if (cn_sz[v] == -1 || cn_sz[v] >= cn_sz[u] || cn_sz[v] + cn_sz[v] < siz)
				continue;
			w = v;
		}
	} while (u != w);

	cn_setdist(u,u,depth,0);
	cn_sz[u] = -1;
	cn_dep[u] = depth;

	for (int v : adj[u]) {
		if (cn_sz[v] == -1) continue;
		int w = cn_build(v, depth+1);
		cn_adj[u].pb(w);
		cn_adj[w].pb(u);
	}
	return u;
}

vector<pii> seg[N];
deque<int> all[N];
int ch;

struct cmp {
	bool operator()(int i, int j) {
		return c1[ch][all[i].front()] < c1[ch][all[j].front()];
	}
};

vector<int> c[N];

ll ans = 1;
int sz[N];

int go(int u, int p, int h) {
	ch = h;
	int sz = 1;
	priority_queue<int, cmp> pq;
	c[u].pb(c2[ch][u]);
	for(int v : cn_adj[u]) {
		if(v == p) continue;
		sz += go(v, u, h + 1);
		pq.push(v);
		for(int w : all[v])
			c[u].pb(c2[ch][w]);
		for(auto &e : seg[v])
			e = pii(0, 1);
	}
	sort(c[u].begin(), c[u].end());
	c[u].erase(unique(c[u].begin(), c[u].end()), c[u].end());
	assert(c[u].size() <= sz);
	seg[u].resize(4 * sz, pii(0, 1));
	while(!pq.empty()) {
		int x = pq.top(); pq.pop();
		int v = all[x].front(); all[x].pop_front();
		if(!all[x].empty()) pq.push(x);
		all[u].push_front(v);
		int cu = lower_bound(c[u].begin(), c[u].end(), c2[ch][v]) - c[u].begin();
		int cx = lower_bound(c[x].begin(), c[x].end(), c2[ch][v]) - c[x].begin();
		pii al = query(seg[u], 1, 0, sz - 1, cu);
		pii rm = query(seg[x], 1, 0, sz[x] - 1, cx);
		al.ct -= rm.ct;
		al.ml = mod(al.ml * inv(rm.ml));
		ans = mod(ans * al.ml);
		ans = mod(ans * fexp(ml[ch][v], al.ct));
		add(seg[u], 1, 0, sz - 1, cu, ml[ch][v]);
		add(seg[x], 1, 0, sz[x] - 1, cx, ml[ch][v]);
	}
	for(int v : cn_adj[u]) seg[v].clear();
	::sz[u] = sz;
	return sz;
}

int main() {
	init();
	int i;
	rd(n);
	for(i = 0; i < n - 1; i++) {
		int a, b, cl, c;
		rd(a); rd(b); rd(cl); rd(c);
		cl[a][b] = mp[b][a] = cl;
		co[a][b] = co[b][a] = c;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	int r = cn_build(0, 0, 0);
	go(r, r);
	printf("%lld\n", ans);
}
