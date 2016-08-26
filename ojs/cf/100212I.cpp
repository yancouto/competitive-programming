#include <bits/stdc++.h>
using namespace std;

namespace f {
	const int maxv = 700;
	const int maxe = 100000 * 2;
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
			for(int i = es[qu[a]]; i != -1; i = nx[i])
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					cr[to[i]] = es[to[i]];
					if(to[i] == t) return true;
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

	int add_edge(int a, int b, num c, num rc=0) {
		if(!c) return -1;
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
		return en - 2;
	}
}

void imp() { puts("-1"); exit(0); }
const int E = 100000;
int deg[1000], a[E], b[E], e[E];
int main() {
	freopen("trade.in", "r", stdin);
	freopen("trade.out", "w", stdout);
	int i, n, m, p;
	scanf("%d %d %d", &m, &n, &p);
	for(i = 0; i < p; i++) {
		scanf("%d %d", &a[i], &b[i]);
		a[i]--; b[i]--;
		//a[i] = rand() % m; b[i] = rand() % n;
		deg[a[i]]++; deg[b[i] + m]++;
	}
	for(i = 0; i < n + m; i++)
		if(deg[i] < 2)
			imp();
	f::reset_all();
	for(i = 0; i < m; i++)
		f::add_edge(f::maxv - 1, i, deg[i] - 2);
	for(i = 0; i < n; i++)
		f::add_edge(i + m, f::maxv - 2, deg[i + m] - 2);
	for(i = 0; i < p; i++)
		e[i] = f::add_edge(a[i], b[i] + m, 1);		
	int x = f::max_flow(f::maxv - 1, f::maxv - 2);
	int st[E], sn = 0;
	for(i = 0; i < p; i++)
		if(f::fl[e[i]] == 0)
			st[sn++] = i;
	printf("%d\n%d", sn, st[0] + 1);
	for(i = 1; i < sn; i++)
		printf(" %d", st[i] + 1);
	putchar('\n');
}
