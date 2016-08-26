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
	const int maxv = 508;
	const int maxe = (253 * 253 + 508) * 2;
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


int main() {
	int i, j, c, d, v, x, y, dn, cn; char cc;
	pii dl[502], cl[502];
	for_tests(t, tt) {
		scanf("%d %d %d", &c, &d, &v);
		f::reset_all(v + 5); dn = cn = 0;
		for(i = 0; i < v; i++) {
			scanf(" %c%d %*c%d", &cc, &x, &y);
			if(cc == 'D') {
				f::add_edge(0, dn + 1, 1);
				dl[dn++] = pii(x, y);
			}
			else {
				f::add_edge(v - cn, v + 1, 1);
				cl[cn++] = pii(x, y);
			}
		}
		for(i = 0; i < dn; i++)
			for(j = 0; j < cn; j++)
				if(dl[i].fst == cl[j].snd || dl[i].snd == cl[j].fst)
					f::add_edge(i + 1, v - j, f::inf);
		printf("%d\n", v - f::max_flux(0, v + 1));
	}
}
