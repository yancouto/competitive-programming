#include <bits/stdc++.h>
using namespace std;
#define i first
#define j second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }


int n, m;
char g[10][10];
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }

ll num(vector<pii> &v) {
	ll x = 0;
	for(pii p : v) {
		x = mod(x * 23ll + p.i + 11ll);
		x = mod(x * 23ll + p.j + 11ll);
	}
	return x;
}

set<int> S[10];
vector<vector<pii>> bl[10];

void gen(vector<pii> &v, int n, int all) {
	for(int i = v.size() - 1; i >= 0; i--)
		v[i].i -= v[0].i, v[i].j -= v[0].j;
	ll id = num(v);
	if(!S[all].insert(id).j) return;
	if(n == 0) {
		for(int i = 0; i < all; i++) {
			vector<pii> w = v;
			swap(w[0], w[i]);
			for(int j = all - 1; j >= 0; j--)
				w[j].i -= w[0].i, w[j].j -= w[0].j;
			bl[all].pb(w);
		}
		return;
	}
	for(pii p : v) {
		for(int d = 0; d < 4; d++) {
			pii q(p.i + di[d], p.j + dj[d]);
			if(binary_search(v.begin(), v.end(), q)) continue;
			vector<pii> w = v;
			w.pb(q);
			for(int i = w.size() - 1; i > 0 && w[i] < w[i - 1]; i--)
				swap(w[i], w[i - 1]);
			gen(w, n - 1, all);
		}
	}
}

vector<int> p[10][10];
pii ord[100]; int sn;

int a[10][10];
int seen[10][10], t, all;
bool dfs(int i, int j) {
	all++;
	seen[i][j] = t;
	bool ok = false;
	for(int l = 0; l < 2 && !ok; l++)
		for(int c = 0; c < 2 && !ok; c++)
			if(!valid(i + l, j + c) || a[i + l][j + c])
				ok = true;
	if(!ok) return false;
	for(int d = 0; d < 4; d++) {
		int ni = i + di[d], nj = j + dj[d];
		if(valid(ni, nj) && !a[ni][nj] && seen[ni][nj] < t && !dfs(ni, nj)) return false;
	}
	return true;
}
bool check() {
	bool any = false; int ct = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			ct += (!a[i][j]);
			if(!any && !a[i][j]) {
				any = true;
				t++; all = 0;
				if(!dfs(i, j)) return false;
			}
		}
	if(!any) return true;
	return all == ct;
}

bool bt(int g) {
	if(g == sn) return check();
	int i = ord[g].i, j = ord[g].j, d;
	for(int k : p[i][j]) {
		bool bad = false;
		for(pii b : bl[::g[i][j] - '0'][k]) {
			int ni = i + b.i, nj = j + b.j;
			if(a[ni][nj]) { bad = true; break; }
			for(d = 0; d < 4; d++) {
				int i2 = ni + di[d], j2 = nj + dj[d];
				if(valid(i2, j2) && a[i2][j2])
					break;
			}
			if(d < 4) { bad = true; break; }
		}
		if(bad) continue;
		for(pii b : bl[::g[i][j] - '0'][k]) {
			int ni = i + b.i, nj = j + b.j;
			a[ni][nj] = 1;
		}
		if(bt(g + 1)) return true;
		for(pii b : bl[::g[i][j] - '0'][k]) {
			int ni = i + b.i, nj = j + b.j;
			a[ni][nj] = 0;
		}
	}
	return false;
}

int main() {
	int i, j, k, d;
	for(i = 1; i <= 9; i++) {
		vector<pii> v; v.pb(pii(0, 0));
		gen(v, i - 1, i);
	}
	bool fst = true;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		if(!fst) putchar('\n');
		fst = false;
		sn = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf(" %c", &g[i][j]);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				p[i][j].clear(); a[i][j] = 0;
				if(g[i][j] == '.') continue;
				for(int bi = 0; bi < bl[g[i][j] - '0'].size(); bi++) {
					vector<pii> &b = bl[g[i][j] - '0'][bi];
					for(k = 1; k < g[i][j] - '0'; k++) {
						int ni = i + b[k].i, nj = j + b[k].j;
						if(!valid(ni, nj) || g[ni][nj] != '.')  break;
						for(d = 0; d < 4; d++) {
							int i2 = ni + di[d], j2 = nj + dj[d];
							if(pii(i2, j2) != pii(i, j) && valid(i2, j2) && g[i2][j2] != '.')
								break;
						}
						if(d < 4) break;
					}
					if(k == g[i][j] - '0') p[i][j].pb(bi);
				}
				ord[sn++] = pii(i, j);
			}
		assert(bt(0));
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++)
				if(!a[i][j]) putchar('#');
				else putchar(g[i][j]);
			putchar('\n');
		}
	}
}
