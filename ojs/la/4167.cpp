#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

namespace f {
const int maxv = 10009;
const int maxe = 30009 * 2;
typedef int num;
int n = maxv;

int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv];
num cp[maxe], fl[maxe];
num inf = INT_MAX;


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

int dfs(int u, int t, num mx) {
	if(u == t) return mx;
	for(int i = es[u]; i != -1; i = nx[i]) {
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


int max_flux(int s, int t) {
	int fl = 0, a;
	while(bfs(s, t)) {
		while(a = dfs(s, t, inf))
			fl += a;
	}
	return fl;
}

void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
void reset_flux(int m=maxe/2) { memset(fl, 0, sizeof(num) * m*2); }

void add_edge(int a, int b, int c, int rc=0) {
	fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
	fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
}
}

int n, m, p, w, e;
int pi[10009], pj[10009];
int grid[102][102];
int g2[102][102];
int g3[102][102];
int main() {
	int i, j, k, x, y;
	for_tests(t, tt) {
		memset(grid, 0, sizeof grid);
		memset(g2, 0, sizeof g2);
		memset(g3, 0, sizeof g3);
		scanf("%d %d %d", &n, &m, &p);
		for(i = 0; i < p; i++)
			scanf("%d %d", &pi[i], &pj[i]);
		scanf("%d", &w);
		for(i = 0; i < w; i++) {
			scanf("%d %d", &x, &y);
			grid[--x][--y] = 1;
		}
		f::reset_all(); e = 2;
		for(i = 0; i < n; i++) {
			for(j = 0; j < m;) {
				while(j < m && grid[i][j]) j++;
				for(k = j; k < m && !grid[i][k]; k++) g2[i][k] = e;
				if(k > j) f::add_edge(0, e++, 1);
				j = k;
			}
		}
		for(j = 0; j < m; j++)
			for(i = 0; i < n;) {
				for(; i < n && grid[i][j]; i++);
				for(k = i; k < n && !grid[k][j]; k++) g3[k][j] = e;
				if(k > i) f::add_edge(e++, 1, 1);
				i = k;
			}
		for(i = 0; i < p; i++) {
			int ii = pi[i] - 1, jj = pj[i] - 1;
			f::add_edge(g2[ii][jj], g3[ii][jj], INT_MAX);
		}
		printf("%d\n", f::max_flux(0, 1));
	}
}
