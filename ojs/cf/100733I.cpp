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
	const int maxv = 2009;
	const int maxe = 510000 * 2;
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

	int seen[maxv], tempo, cr[maxv];
	int dfs(int u, int t, num mx) {
		if(u == t) return mx;
		if(seen[u] == tempo) return 0;
		seen[u] = tempo;
		for(int &i = cr[u]; i != -1; i = nx[i]) {
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1) {
				if(int a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					//printf("cam through %d->%d\n", u, to[i]);
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
			tempo++;
			for(int i = 0; i < n; i++) cr[i] = es[i];
			while(a = dfs(s, t, inf))
				fl += a, tempo++;
		}
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flux(int m=maxe/2) { memset(fl, 0, sizeof(num) * m*2); }

	void add_edge(int a, int b, int c, int rc=0) {
		//printf("add %d->%d\n", a, b);
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}
int m, n[2], t, h[2][509];
inline int vin(int i) { return i << 1; }
inline int vout(int i) { return vin(i) + 1; }
inline int fix(int i, int c) { return i + c*n[0]; }
int d[2] = {f::maxv - 1, f::maxv - 2};
int s[2] = {f::maxv - 3, f::maxv - 4};
void init(int c, int ff) {
	for(int i = 0; i < n[c]; i++)
		f::add_edge(vin(fix(i, c)), vout(fix(i, c)), 1);
	for(int i = 0; i < m; i++) {
		if(c != ff) f::add_edge(vout(fix(i, c)), d[c], 1);
		else f::add_edge(s[c], vin(fix(n[c]-1-i, c)), 1);
	}
}

void fromto(int c, int ff) {
	int i, j;
	for(i = 0; i < n[c]; i++)
		for(j = 0; j < n[!c]; j++) {
			if(c != ff && (i < m || j >= (n[ff] - m))) continue;
			if(abs(h[c][i] - h[!c][j]) < t)
				f::add_edge(vout(fix(i, c)), vin(fix(j, !c)), 1);
		}
}

int main() {
	int i, j;
	scanf("%d %d %d %d", &m, &n[0], &n[1], &t);
	for(j = 0; j < 2; j++) {
		for(i = 0; i < n[j]; i++)
			scanf("%d", &h[j][i]);
		sort(h[j], h[j] + n[j]);
	}
	d[0] = vout(fix(n[1]-1, 1)) + 1;
	d[1] = d[0] + 1;
	s[0] = d[1] + 1;
	s[1] = s[0] + 1;
	for(j = 0; j < 2; j++) {
		f::reset_all(2*(n[0]+n[1]) + 4);
		init(0, j); init(1, j);
		fromto(0, j); fromto(1, j);
		if(f::max_flux(s[j], d[!j]) >= m) { puts("S"); return 0; }
	}
	puts("N");
	return 0;
}
