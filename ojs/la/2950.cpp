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
	const int maxv = 500;
	const int maxe = 500 * 500 * 2;
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

inline int vin(int i) { return (i + 1) << 1; }
inline int vout(int i) { return vin(i) + 1; }
char adj[102][102];
int a[102], bad[102], n, badn;

bool pos(int w) {
	int i, j;
	f::reset_all();
	for(i = 0; i < n; i++)
		if(a[i] > 0) {
			f::add_edge(0, vout(i), a[i] - 1);
			f::add_edge(vin(i), vout(i), 1);
			if(bad[i]) {
				f::add_edge(vin(i), f::maxv - 1 - i, f::inf);
				f::add_edge(vout(i), f::maxv - 1 - i, f::inf);
				f::add_edge(f::maxv - 1 - i, 1, w - 1);
			}
		}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(adj[i][j] == 'Y' && a[i] > 0 && a[j] > 0)
				f::add_edge(vout(i), vin(j), f::inf);
	int fl = f::max_flow(0, 1);
	return fl == badn * (w - 1);
}

int main() {
	int i, j;
	for_tests(tn, tc) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]), bad[i] = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				scanf(" %c", &adj[i][j]);
				if(adj[i][j] == 'Y' && a[i] && !a[j]) { bad[i] = 1; continue; }
			}
		badn = accumulate(bad, bad + n, 0);
		int l = 1, r = 10001;
		while(l < r) {
			int m = (l + r + 1) / 2;
			if(pos(m)) l = m;
			else r = m - 1;
		}
		printf("%d\n", l);
	}
}
