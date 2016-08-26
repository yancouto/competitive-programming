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

namespace f {
	const int maxv = 2000;
	const int maxe = 2000 * 4 * 2;
	typedef short num;
	num inf = SHRT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv], cr[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s; cr[s] = es[s];
		while(a < b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i]) {
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					cr[to[i]] = es[to[i]];
					if(to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	num dfs(int u, int t, num mx) {
		if(u == t) return mx;
		for(int &i = cr[u]; i != -1; i = nx[i])
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1)
				if(num a = dfs(to[i], t, min(mx, num(cp[i] - fl[i])))) {
					fl[i] += a;
					fl[i ^ 1] -= a;
					return a;
				}
		return 0;
	}


	num max_flow(int s, int t) {
		num fl = 0, a;
		while(bfs(s, t))
			while(a = dfs(s, t, inf))
				fl += a;
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	void add_edge(int a, int b, num c, num rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}
int n, m;
int vi[50][50];
int vo[50][50];
inline int vin(int i, int j) { return vi[i][j]; }
inline int vout(int i, int j) { return vo[i][j]; }

char g[50][50];
int di[] = {1, -1, 0, 0};
int dj[] = {0, 0, 1, -1};
int main() {
	int i, j, d;
	while(scanf("%s", g[0]) != EOF) {
		m = strlen(g[0]);
		getchar();
		for(i = 1; (g[i][0] = getchar()) != '\n' && !feof(stdin); i++, getchar())
			if(m > 1)
				scanf("%s", g[i] + 1);
		n = i;
		int en = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				if(g[i][j] == 'W') vo[i][j] = en++;
				else if(g[i][j] == 'I') vi[i][j] = en++, vo[i][j] = en++;
				else vi[i][j] = en++;
		f::reset_all(en + 2);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				if(g[i][j] == 'N') { f::add_edge(vin(i, j), f::n - 1, 1); continue; }
				char nx = 'I';
				if(g[i][j] == 'I') nx = 'N', f::add_edge(vin(i, j), vout(i, j), 1);
				else f::add_edge(f::n - 2, vout(i, j), 1);
				for(d = 0; d < 4; d++) {
					int ni = i + di[d], nj = j + dj[d];
					if(ni < 0 || nj < 0 || ni >= n || nj >= m || g[ni][nj] != nx) continue;
					f::add_edge(vout(i, j), vin(ni, nj), f::inf);
				}
			}
		printf("%d\n", (int)f::max_flow(f::n - 2, f::n - 1));
	}
}
