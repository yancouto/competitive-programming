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
	const int maxv = 200;
	const int maxe = (81 * 91 + 200) * 2;
	typedef int num;
	num inf = INT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv], cr[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s; cr[s] = es[s];
		while(a < b) {
			cr[qu[a]] = es[qu[a]];
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
				if(int a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
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

	int add_edge(int a, int b, num c, num rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
		return en - 2;
	}
}

int gt[100], gp[100];
int grid[100][100];
int main() {
	bool first = true;
	int i, j, x, T, P;
	while(scanf("%d %d", &T, &P) != EOF && T) {
		if(!first) putchar('\n');
		else first = false;
		int tt = 0, tp = 0;
		f::reset_all();
		int s = T + P, t = T + P + 1;
		for(i = 0; i < T; i++) {
			scanf("%d", &x); tt += x;
			gt[i] = f::add_edge(s, i, x);
		}
		for(i = 0; i < P; i++) {
			scanf("%d", &x); tp += x;
			gp[i] = f::add_edge(i + T, t, x);
		}
		for(i = 0; i < T; i++)
			for(j = P - 1; j >= 0; j--) {
				f::add_edge(i, j + T, 1);
			}
		x = f::max_flow(s, t);
		if(x != tt || x != tp) { puts("Impossible"); continue; }
		memset(grid, 0, sizeof grid);
		for(i = 0; i < T; i++) {
			using namespace f;
			for(int e = es[i]; e != -1; e = nx[e]) {
				if(fl[e] == 0 && to[e] != s) cp[e] = 0;
				if(to[e] == s || fl[e] == 0) continue;
				assert(fl[e] == 1 && fl[e ^ 1] == -1);
				cp[gt[i]]++; cp[gp[to[e] - T]]++;
				if(!f::max_flow(s, t)) {
					cp[gt[i]]--; cp[gp[to[e] - T]]--;
					grid[i][to[e] - T] = 1;
				}
			}
		}
		for(i = 0; i < T; i++) {
			for(j = 0; j < P; j++)
				putchar(grid[i][j]? 'Y' : 'N');
			putchar('\n');
		}
	}
}
