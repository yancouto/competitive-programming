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

const int MAXV = 105 * 105 * 4;
vector<int> adj[MAXV];
int seen[MAXV], has[MAXV >> 1];
int d[MAXV], low[MAXV], tempo;
int st[MAXV], sn;

void dfs(int u) {
	if(seen[u]) return;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u]) {
		dfs(v);
		low[u] = min(low[u], low[v]);
	}
	if(low[u] == d[u]) {
		int x, sz = 0;
		bool was_set = false;
		do {
			x = st[--sn];
			low[x] = INT_MAX;
			if(has[x >> 1]) was_set = true;
			sz++;
		} while(x != u);
		if(!was_set)
			for(int i = 0; i < sz; i++)
				has[st[sn + i] >> 1] = 1 + !(st[sn + i] & 1);
	}
}

char g[102][102];
int r, s;
inline int id(int i, int j) { return i * 100 + j; }
inline int UP(int i, int j) { return id(i, j) << 1; }
inline int RI(int i, int j) { return UP(i, j) + 1; }
inline int vtrue(int v) { return v << 1; }
inline int vfalse(int v) { return (v << 1) + 1; }
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < r && j < s && g[i][j] != '#'; }
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, -1, 1};


void do_enemy(int i, int j) {
	int d, k;
	int x[4] = {-1, -1, -1, -1};
	for(d = 0; d < 4; d++)
		for(k = 1; k < 100; k++) {
			int ni = i + di[d] * k, nj = j + dj[d] * k;
			if(!valid(ni, nj)) break;
			if(g[ni][nj] == 'T') {
				x[d] = ((d & 1)? vfalse : vtrue)((d <= 1? UP : RI)(ni, nj));
				break;
			}
		}
	int y[2];
	for(i = 0; i < 4; i += 2) {
		if(x[i] != -1 && x[i + 1] != -1) x[i] = x[i + 1] = -1;
		y[i/2] = max(x[i], x[i + 1]);
	}
	if(y[0] != -1 && y[1] != -1) {
		adj[y[0] ^ 1].pb(y[1]); // y[0] ou y[1]
		adj[y[1] ^ 1].pb(y[0]);
	} else {
		k = max(y[0], y[1]);
		adj[k ^ 1].pb(k); // k == true
	}
}

void do_tower(int i, int j) {
	int d, k;
	for(d = 0; d < 4; d++)
		for(k = 1; k < 100; k++) {
			int ni = i + di[d] * k, nj = j + dj[d] * k;
			if(!valid(ni, nj)) break;
			if(g[ni][nj] == 'T') {
				int val = ((d & 1)? vfalse : vtrue)((d <= 1? UP : RI)(ni, nj));
				adj[val].pb(val ^ 1); // val == false
				break;
			}
		}
}

int main() {
	int i, j;
	scanf("%d %d", &r, &s);
	for(i = 0; i < r; i++)
		for(j = 0; j < s; j++)
			scanf(" %c", &g[i][j]);
	for(i = 0; i < r; i++)
		for(j = 0; j < s; j++) {
			if(g[i][j] == 'n') do_enemy(i, j);
			else if(g[i][j] == 'T') do_tower(i, j);
		}
	for(i = 0; i < MAXV; i++)
		dfs(i);
	for(i = 0; i < r; i++)
		for(j = 0; j < s; j++) {
			if(g[i][j] == 'T') {
				if(has[RI(i, j)] == 1) {
					if(has[UP(i, j)] == 2) g[i][j] = '4';
					else g[i][j] = '1';
				} else {
					if(has[UP(i, j)] == 2) g[i][j] = '3';
					else g[i][j] = '2';
				}
			}
			putchar(g[i][j]);
			if(j == s - 1) putchar('\n');
		}
}
