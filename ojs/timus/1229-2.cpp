#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int n, m;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }
const int MAXV = 11009, MAXE = MAXV * 6;

namespace f {
	const int maxv = 11009;
	const int maxe = maxv * 6 * 2;
	typedef int num;
	num inf = INT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s;
		while(a < b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i]) {
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					if(to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	int us[maxv], te, cr[maxv];
	num dfs(int u, int t, num mx) {
		if(u == t) return mx;
		for(int &i = cr[u]; i != -1; i = nx[i]) {
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1) {
				if(int a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i ^ 1] -= a;
					return a;
				}
			}
		}
		return 0;
	}


	num max_flow(int s, int t) {
		num fl = 0, a;
		while(bfs(s, t)) {
			te++;
			for(int i = 0; i < n; i++) cr[i] = es[i];
			while(a = dfs(s, t, inf))
				fl += a, te++;
		}
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flow(int m=maxe/2) { memset(fl, 0, sizeof(num) * m*2); }

	void add_edge(int a, int b, num c=1, num rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}

int g[102][102];
int main() {
	int i, j, d;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf("%d", &g[i][j]);
	f::reset_all();
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			int v = i * m + j + 2;
			bool left = !((i + j) & 1);
			if(left) f::add_edge(0, v);
			else f::add_edge(v, 1);
			if(!left) continue;
			for(d = 0; d < 4; d++) {
				int ni = i + dx[d], nj = j + dy[d];
				if(!valid(ni, nj) || g[i][j] == g[ni][nj]) continue;
				int w = ni * m + nj + 2;
				f::add_edge(v, w);
			}
		}
	int f = f::max_flow(0, 1);
	if(f != m * n / 2) { puts("-1"); return 0; }
	int sz = 0;
	memset(g, -1, sizeof g);
	using f::to;
	for(i = 0; i < f::en; i++) {
		if(f::fl[i] != 1) continue;
		if(to[i] == 1 || to[i ^ 1] == 0) continue;
		int u = (to[i] - 2) / m, v = (to[i] - 2) % m;
		g[u][v] = ++sz;
		u = (to[i ^ 1] - 2) / m; v = (to[i ^ 1] - 2) % m;
		g[u][v] = sz;
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++)
			printf("%d ", g[i][j]);
		putchar('\n');
	}
}
