#include <bits/stdc++.h>
using namespace std;

namespace f {
	const int maxv = 5000;
	const int maxe = 10000 * 2;
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
				if(num a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
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



int main() {
	int n, p, a, b, c, i;
	scanf("%d %d %d %d %d", &n, &p, &a, &b, &c);
	int s = n + 1000, t = n + 1001;
	f::reset_all();
	for(i = 0; i < 256; i++)
		f::add_edge(s, i, a);
	for(i = 0; i < 256; i++)
		f::add_edge(s, i + 256, b);
	for(i = 0; i < 256; i++)
		f::add_edge(s, i + 512, c);
	for(i = 0; i < n; i++) {
		f::add_edge(1000 + i, t, p);
		scanf("%d %d %d", &a, &b, &c);
		f::add_edge(a, 1000 + i, f::inf);
		f::add_edge(b + 256, 1000 + i, f::inf);
		f::add_edge(c + 512, 1000 + i, f::inf);
	}
	printf("%d\n", n * p - f::max_flow(s, t));
}
