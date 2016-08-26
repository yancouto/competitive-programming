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
namespace f {
	const int maxv = 100 * 100 + 100;
	const int maxe = (3 * 100 * 100 + 100) * 2;
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
		if(us[u] == te) return 0;
		us[u] = te;
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

	void add_edge(int a, int b, num c, num rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}
char g[102][102];
int sh[102][102], sv[102][102];
int main() {
	int i, j, k, n;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf(" %c", &g[i][j]);
		f::reset_all();
		memset(sv, 0, sizeof sv);
		memset(sh, 0, sizeof sh);
		int kv = 0, kh = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				if(g[i][j] == '.' && !sh[i][j]) {
					kh++; f::add_edge(0, kh, 1);
					for(k = j; k < n && g[i][k] == '.'; k++)
						sh[i][k] = kh;
				}
				if(g[i][j] == '.' && !sv[i][j]) {
					kv++; f::add_edge(f::maxv - 1 - kv, f::maxv - 1, 1);
					for(k = i; k < n && g[k][j] == '.'; k++)
						sv[k][j] = kv;
				}
			}
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(g[i][j] == '.')
					f::add_edge(sh[i][j], f::maxv - 1 - sv[i][j], 1);
		printf("%d\n", f::max_flow(0, f::maxv - 1));
	}
}
