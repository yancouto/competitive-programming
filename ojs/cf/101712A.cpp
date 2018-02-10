#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int N = 502;
const int M = (250 * 250 + 500) * 2 + 2;

struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M];
	num fl[M], cp[M];
	int en = 2;
	int tempo = 0;

	// Reset the whole graph
	void reset(int n=N) { en = 2; memset(hd, 0, sizeof(int) * n); }
	// Reset only the flow
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	// edge from a to b with cap c and edge from b to a with cap rc
	void add_edge(int a, int b, int c, int rc=0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] =  c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}

	bool bfs(int s, int t) {
		seen[t] = ++tempo;
		lv[t] = 0;
		int ql = 0, qr = 0;
		qu[qr++] = t;
		while(ql != qr) {
			t = qu[ql++];
			ei[t] = hd[t];
			if(s == t) return true;
			for(int e = hd[t]; e; e = nx[e])
				if(seen[to[e]] != tempo && cp[e ^ 1] - fl[e ^ 1] > 0) {
					seen[to[e]] = tempo;
					lv[to[e]] = lv[t] + 1;
					qu[qr++] = to[e];
				}
		}
		return false;
	}

	num dfs(int s, int t, num f) {
		if(s == t) return f;
		for(int &e = ei[s]; e; e = nx[e])
			if(ei[to[e]] && cp[e] - fl[e] > 0 && lv[to[e]] == lv[s] - 1)
				if(num rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
					fl[e] += rf;
					fl[e ^ 1] -= rf;
					return rf;
				}
		return 0;
	}

	num max_flow(int s, int t) {
		num fl = 0;
		while(bfs(s, t))
			while(num f = dfs(s, t, numeric_limits<num>::max()))
				fl += f;
		return fl;
	}
} d;

int main() {
	int n, m, x;
	scanf("%d %d", &n, &m);
	int s = n + m, t = n + m + 1;
	for(int i = 0; i < n; i++)
		d.add_edge(s, i, 1);
	for(int i = 0; i < m; i++)
		d.add_edge(i + n, t, 1);
	for(int i = 0; i < n; i++)
		while(scanf("%d", &x) != EOF && x)
			d.add_edge(i, x - 1 + n, INT_MAX);
	printf("%d\n", d.max_flow(s, t));
	for(int i = 0; i < n; i++)
		for(int e = d.hd[i]; e; e = d.nx[e])
			if(d.fl[e] == 1 && d.to[e] != s)
				printf("%d %d\n", i + 1, d.to[e] - n + 1);
}
