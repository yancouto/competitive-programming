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
#define max_v 210
#define max_e 30000
using namespace std;

namespace f {
	const int maxv = 100009;
	const int maxe = 300009 * 2;
	typedef int num;
	num inf = INT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv], cr[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s;
		while(a < b) {
			cr[qu[a]] = es[qu[a]];
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


int n; double d;
struct nest {
	int x, y, n, m;
	void read() { scanf("%d %d %d %d", &x, &y, &n, &m); }
	bool reach(nest &o) {
		return ((o.x-x)*(o.x-x)+(o.y-y)*(o.y-y)) <= d*d;
	}
}ns[102];

int inf = 100000000;
int main() {
	int i, j;
	for_tests(tt, ttt) {
		scanf("%d %lf", &n, &d);
		int tot = 0;
		f::reset_all();
		for(i = 1; i <= n; i++) {
			ns[i].read();
			tot += ns[i].n;
			f::add_edge(2*i, 2*i+1, ns[i].m);
			if(ns[i].n)
				f::add_edge(0, 2*i, ns[i].n);
		}
		for(i = 1; i <= n; i++)
			for(j = 1; j<= n; j++) {
				if(i == j) continue;
				if(!ns[i].reach(ns[j])) continue;
				f::add_edge(i*2+1, j*2, f::inf);
				f::add_edge(j*2+1, i*2, f::inf);
			}
		int qt = 0;
		for(i = 1; i <= n; i++) {
			f::reset_flow(f::en + 3);
			int mf = f::max_flow(0, 2 * i);
			if(mf == tot) {
				if(qt) printf(" %d", i - 1);
				else printf("%d", i - 1);
				qt++;
			}
		}
		if(qt) putchar('\n');
		else puts("-1");
	}
	return 0;
}
