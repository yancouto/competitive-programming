#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
#define move alejlekj

struct move {
	int i, j, vi, vj, e;
};

const int N = 112;
int g[N][N], bk[N][N], seen[N][N], t;
int n;

void apply(move m) {
	//printf("n = %d\n", n);
	t++;
	seen[m.i][m.j] = t;
	bk[m.i][m.j] = g[m.i][m.j];
	while(m.e--) {
		int i = m.i + m.vi, j = m.j + m.vj;
		if((i == -1 || i == n + 1) && (j == -1 || j == n + 1)) { g[m.i][m.j] = 0; return; }
		if(i < 0) i = 1, m.vi = 1;
		if(i > n) i = n - 1, m.vi = -1;
		if(j < 0) j = 1, m.vj = 1;
		if(j > n) j = n - 1, m.vj = -1;
		if(seen[i][j] != t) {
			seen[i][j] = t;
			bk[i][j] = g[i][j];
		}
		if(i != m.i || j != m.j) {
			g[i][j] += g[m.i][m.j];
			g[m.i][m.j] = 0;
			//printf("g[%d][%d] = 0\n", m.i, m.j);
		}
		//printf("d[%d,%d]\n", m.vi, m.vj);
		//printf("(%d,%d) -> (%d,%d) %d\n", m.i, m.j, i, j, g[i][j]);
		m.i = i; m.j = j;
	}
	//puts(">>>>");
}

void restore(move m) {
	g[m.i][m.j] = bk[m.i][m.j];
	while(m.e--) {
		int i = m.i + m.vi, j = m.j + m.vj;
		if((i == -1 || i == n + 1) && (j == -1 || j == n + 1)) return;
		if(i < 0) i = 1, m.vi = 1;
		if(i > n) i = n - 1, m.vi = -1;
		if(j < 0) j = 1, m.vj = 1;
		if(j > n) j = n - 1, m.vj = -1;
		g[i][j] = bk[i][j];
		m.i = i; m.j = j;
	}
}


void try_mv(int j, move &mv, int &best, move m) {
	if(m.e == 0) return;
	apply(m);
	if(g[j][j] > best) {
		best = g[j][j];
		mv = m;
	}
	restore(m);
}

void deb() {
	int i, j;
	for(i = 0; i <= n; i++)
		for(j = 0; j <= n; j++)
			printf("%d%c", g[i][j], " \n"[j == n]);
	puts("------------");
}

int main() {
	int m, i, j, x, y, z;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i <= n; i++)
			for(j = 0; j <= n; j++)
				g[i][j] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &z);
			g[x][y] += z;
		}
		//deb();
		int mv = -1, mt, tot = 0;
		for(i = n; i >= 0; i--) {
			tot += g[i][i];
			if(tot < 0 && (mv == -1 || mt > tot)) mv = i, mt = tot;
		}
		vector<move> mvs;
		if(mv != -1 && mt < -1 && mv != n) {
			mvs.pb({mv, mv, 1, 1, n - mv});
			apply(mvs.back());
		}
		for(j = 0; j <= n; j++) {
			move mv; int best = g[j][j];
			for(i = 0; i <= n; i++) {
				if(g[i][j] <= 0) continue;
				try_mv(j, mv, best, {i, j, -1, 0, i + j});
				try_mv(j, mv, best, {i, j, 1, 0, n - i + n - j});
				if(i < j) try_mv(j, mv, best, {i, j, 1, 0, j - i});
				if(i > j) try_mv(j, mv, best, {i, j, -1, 0, i - j});
			}
			//printf("best %d of %d\n", best, g[j][j]);
			if(best != g[j][j]) { mvs.pb(mv); apply(mv); }
			//deb();
		}
		//deb();
		mv = -1; tot = 0;
		for(i = 0; i <= n; i++) {
			tot += g[i][i];
			if(g[i][i] && tot > 0 && (mv == -1 || tot > mt)) mv = i, mt = tot;
		}
		if(mv != -1) {
			mvs.pb({mv, mv, -1, -1, mv + 1});
			//printf("heya %d\n", mv);
		} else mvs.clear();
		printf("%d\n", int(mvs.size()));
		for(move m : mvs)
			printf("%d %d %d %d %d\n", m.i, m.j, m.vi, m.vj, m.e);
	}
}
