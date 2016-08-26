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
const int N = 312;
vector<vector<int>> pos[11];
vector<int> adj[N];
int sz[N], p[N], g[1124];
#define pc __builtin_popcount

void go(int n, vector<int> v, int i, int mn, int K) {
	if(i == 0) { pos[n].pb(v); return; }
	for(int k = 1; k <= K && k <= i; k++)
		for(int j = (k == K? mn : 0); j < pos[k].size(); j++) {
			vector<int> so = pos[k][j];
			vector<int> g = v;
			g.pb(0);
			int d = g.size();
			for(int x : so) g.pb(d + x);
			go(n, g, i - k, j, k);
		}
}
int K, bm;
vector<int> can;
vector<vector<vector<int>>> a;

bool solve(int, int, int);

bool memo2[N][12][9][1 << 6];
int seen2[N][12][9][1 << 6];
bool choose(int v, int m, int k, int vk, int bm) {
	if(m == adj[v].size()) return bm == ((1 << a[k][vk].size()) - 1);
	int u = adj[v][m];
	bool &r = memo2[u][k][vk][bm];
	if(seen2[u][k][vk][bm] == ::bm) return r;
	seen2[u][k][vk][bm] = ::bm;
	//if(u == 1) printf("%d && %d\n", choose(v, m + 1, k, vk, bm), solve(u, 9, 0));
	r = choose(v, m + 1, k, vk, bm) && solve(u, 9, 0);
	for(int i = 0; !r && i < a[k][vk].size(); i++) {
		if((bm >> i) & 1) continue;
		//if(::bm == 3) printf("(%d->%d) [%d][%d]->%d\n", v+1, u+1, k, vk, a[k][vk][i]);
		r = choose(v, m + 1, k, vk, bm | (1 << i)) && solve(u, k, a[k][vk][i]);
	}
	//printf("choose(%d->%d, %d, %d, %d) = %d\n", v+1, u+1, k, vk, bm, r);
	return r;
}



bool memo[N][13][9];
int seen[N][13][9];
bool solve(int v, int k, int vk) {
	bool &r = memo[v][k][vk];
	//if(bm == 3 && seen[v][k][vk] == bm) printf("[%d] solve(%d, %d, %d) = %d\n", bm, v+1, k, vk, r);
	if(seen[v][k][vk] == bm) return r;
	//if(bm == 3) printf("[%d] solve(%d, %d, %d)\n", bm, v+1, k, vk);
	seen[v][k][vk] = bm;
	if(k == 9) {
		for(int p : can)
			if(solve(v, p, 0))
				return r = true;
		return r = false;
	}
	//if(adj[v].empty() && (vk == 0 || a[k][vk].empty())) printf("(%d, %d, %d) BASE OK\n", v+1, k, vk);
	//else if(adj[v].empty()) printf("SHIET BASE (%d, %d, %d)\n", v+1, k, vk);
	if(adj[v].empty()) return r = (vk == 0 || a[k][vk].empty());
	if(a[k][vk].empty()) {
		bool all = true;
		for(int x : adj[v]) {
			if(!solve(x, 9, 0)) { all = false; break; }
		}
		return r = all;
	} else {
		return r = choose(v, 0, k, vk, 0);
	}
}


bool ok(int k, int bm) {
	K = k; ::bm = bm;
	can.clear(); a.clear();
	a.resize(sz[k]);
	for(int i = 0; i < sz[k]; i++)
		if((bm >> i) & 1) {
			can.pb(i);
			a[i] = (vector<vector<int>>(k));
			for(int j = 0; j < k-1; j++)
				a[i][pos[k][i][j]].pb(j+1);
		}
	assert(can.size() == pc(bm));
	return solve(0, 9, 0);
}

int main() {
	freopen("four.in", "r", stdin);
	freopen("four.out", "w", stdout);
	int i, n, k;
	pos[1].pb(vector<int>(0));
	for(i = 2; i <= 5; i++)
		go(i, vector<int>(0), i-1, 0, 100), sz[i] = pos[i].size();
	//for(i = 2; i <= 5; i++) {
	//	printf("%d\n", i);
	//	for(vector<int> v : pos[i]) {
	//		for(int x : v) printf("%d", x);
	//		printf("\n");
	//	}
	//}
	while(scanf("%d %d", &n, &k) != EOF && n) {
		memset(seen, 0, sizeof seen);
		memset(seen2, 0, sizeof seen2);
		for(i = 0; i < 103; i++) adj[i].clear();
		for(i = 1; i < n; i++) scanf("%d", &p[i]), p[i]--, adj[p[i]].pb(i);
		for(i = 0; i < (1 << sz[k]); i++) g[i] = i;
		sort(g, g + (1 << sz[k]), [](int i, int j) { return pc(i) < pc(j); });
		for(i = 1; i < (1 << sz[k]); i++)
			if(ok(k, i))
				break;
		//printf("right at %d\n======>  ", i);
		//int j = 31-__builtin_clz(i);
		//for(int x : pos[k][j]) printf("%d\n", x);
		//puts("------");
		if(i < (1 << sz[k])) printf("%d\n", pc(i));
		else printf("-1\n");
		//solve(1, 0, 0); solve(1, 9, 0); solve(2, 1, 1);
	}
}
