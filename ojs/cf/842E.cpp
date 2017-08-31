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

const int N = 312345;
int lc[N][20], h[N];
int p[N];

int dist(int a, int b) {
	int d = h[a] + h[b];
	if(h[a] < h[b]) swap(a, b);
	for(int i = 19; i >= 0; i--)
		if(h[lc[a][i]] >= h[b])
			a = lc[a][i];
	if(a != b) {
		for(int i = 19; i >= 0; i--)
			if(lc[a][i] != lc[b][i])
				a = lc[a][i], b = lc[b][i];
		a = lc[a][0];
	}
	return d - 2 * h[a];
}

int sz[N], ds[N][20];
int pc[N], ch[N];

vector<int> adj[N];

int dfs(int u, int p) {
	sz[u] = 1;
	for(int v : adj[u])
		if(v != p && !ch[v])
			sz[u] += dfs(v, u);
	return sz[u];
}

void mrk(int u, int p, int d, int lvl) {
	//printf("ds[%d][%d] = %d\n", u, lvl, d);
	ds[u][lvl] = d;
	for(int v : adj[u])
		if(v != p && !ch[v])
			mrk(v, u, d + 1, lvl);
}

void go(int u, int pc, int lvl) {
	dfs(u, -1);
	int n = sz[u];
	int c = u; int p = -1;
	while(true) {
		bool any = false;
		for(int v : adj[c])
			if(v != p && !ch[v] && sz[v] > n / 2) {
				p = c;
				c = v;
				any = true;
				break;
			}
		if(!any) break;
	}
	::pc[c] = pc;
	ch[c] = lvl;
	//printf("c %d ch %d pc %d\n", c, ch[c], pc);
	for(int v : adj[c])
		if(!ch[v])
			mrk(v, -1, 1, lvl);
	for(int v : adj[c])
		if(!ch[v])
			go(v, c, lvl + 1);
}

struct cmp {
	bool operator()(pii a, pii b) {
		int lvl = a.snd;
		assert(lvl == b.snd);
		int u = a.fst, v = b.fst;
		if(ds[u][lvl] != ds[v][lvl]) return ds[u][lvl] < ds[v][lvl];
		return u < v;
	}
};

set<pii, cmp> s[N];

int main() {
	int i, j;
	rd(n);
	int a = 0, b = 0;
	int mxd = 0;
	for(i = 1; i <= n; i++) {
		rd(p[i]); p[i]--;
		h[i] = h[p[i]] + 1;
		lc[i][0] = p[i];
		for(int b = 1; b < 20; b++)
			lc[i][b] = lc[lc[i][b-1]][b-1];
		adj[p[i]].pb(i);
		adj[i].pb(p[i]);
	}
	go(0, -1, 1);
	set<int> nds;
	nds.insert(0);
	i = 0;
	for(int x = i; x != -1; x = pc[x]) {
		//printf("s[%d].i (%d, %d) [%d]\n", x, i, ch[x], ds[i][ch[x]]);
		s[x].insert(pii(i, ch[x]));
	}
	for(i = 1; i <= n; i++) {
		int da = dist(i, a);
		int db = dist(i, b);
		//printf("[%d] a %d[%d] b %d[%d]\n", i, a, da, b, db);
		if(da < mxd && db < mxd) {
			// nada
		} else if(da <= mxd && db <= mxd) {
			nds.insert(i);
		} else {
			mxd = max(da, db);
			if(da >= db) {
				b = i;
			} else {
				a = i;
			}
			nds.insert(i);
			for(int x = i; x != -1; x = pc[x]) {
				while(!s[x].empty()) {
					int j = s[x].begin()->fst;
					//printf("[%d] x %d j %d ds %d + %d < %d\n", i, x, j, ds[i][ch[x]], ds[j][ch[x]], mxd);
					if(ds[i][ch[x]] + ds[j][ch[x]] < mxd) {
						nds.erase(j);
						for(int k = j; k != -1; k = pc[k])
							s[k].erase(pii(j, ch[k]));
					} else break;
				}
			}
		}
		if(nds.count(i))
			for(int x = i; x != -1; x = pc[x]) {
				//printf("s[%d].i (%d, %d) [%d]\n", x, i, ch[x], ds[i][ch[x]]);
				s[x].insert(pii(i, ch[x]));
			}
		//for(int x : nds) printf("%d ", x); printf(" == %d\n", mxd);
		printf("%d\n", int(nds.size()));
	}
}
