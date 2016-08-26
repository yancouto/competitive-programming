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
	const int maxv = 20 * 41 * 4 + 60;
	const int maxe = (20 * 41 * 4 * 4 + 60) * 2;
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


struct part {
	int i, j;
	bool operator < (part o) const { return i + 42 * j < o.i + 42 * o.j; }
};
const int MAX = 41;
int pt[MAX];

int main() {
	int i, j, k, n, m, g, x, y; char op;
	while(true) {
		scanf("%d %d %d", &n, &m, &g);
		if(!n) return 0;
		multiset<part> s;
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++)
				for(k = 0; k < m; k++)
					s.insert({i, j});
		memset(pt, 0, sizeof pt);
		f::reset_all();
		for(i = 0; i < g; i++) {
			scanf("%d %c %d", &x, &op, &y);
			if(op == '=') pt[x]++, pt[y]++;
			else pt[y] += 2;
			s.erase(s.find({min(x, y), max(x, y)}));
		}
		for(i = 1; i < n; i++)
			pt[0] += 2 * s.erase({0, i});
		for(i = 1; i < n; i++)
			if(pt[0] <= pt[i])
				break;
		if(i < n) { puts("N"); continue; }
		i = 0;
		for(part p : s) {
			f::add_edge(0, ++i, 2);
			f::add_edge(i, f::maxv - p.i - 1, 2);
			f::add_edge(i, f::maxv - p.j - 1, 2);
		}
		for(i = 1; i < n; i++)
			f::add_edge(f::maxv - i - 1, f::maxv - 1, pt[0] - pt[i] - 1);
		if(f::max_flow(0, f::maxv - 1) == s.size() * 2)
			puts("Y");
		else puts("N");
	}
}
