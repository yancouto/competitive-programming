#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int N = 112345;
const int M = 112345 * 2 + 2;

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

int g[100][100];

typedef pair<int, int> pii;
#define i first
#define j second
#define pb push_back

int main() {
	int n, p;
	scanf("%d %d", &n, &p);
	int des = n * n - p;
	while(p--) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a - 1][b - 1] = 1;
	}
	int s = n * n, t = n * n + 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			if(g[i][j]) continue;
			if((i + j) & 1) {
				d.add_edge(s, i * n + j, 1);
				if(i > 0 && !g[i - 1][j]) d.add_edge(i * n + j, (i - 1) * n + j, INT_MAX);
				if(i < n - 1 && !g[i + 1][j]) d.add_edge(i * n + j, (i + 1) * n + j, INT_MAX);
				if(j < n - 1 && !g[i][j + 1]) d.add_edge(i * n + j, i * n + (j + 1), INT_MAX);
				if(j > 0 && !g[i][j - 1]) d.add_edge(i * n + j, i * n + (j - 1), INT_MAX);
			} else
				d.add_edge(i * n + j, t, 1);
		}
	if(!(des & 1) && d.max_flow(s, t) == des / 2) {
		puts("Yes");
		vector<pii> vert, hor;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++) {
				if(g[i][j] || !((i + j) & 1)) continue;
				for(int e = d.hd[i * n + j]; e; e = d.nx[e])
					if(d.fl[e] && d.to[e] != s) {
						int ni = d.to[e] / n;
						int nj = d.to[e] % n;
						if(ni > i) vert.pb(pii(i, j));
						if(ni < i) vert.pb(pii(ni, nj));
						if(nj < j) hor.pb(pii(ni, nj));
						if(nj > j) hor.pb(pii(i, j));
					}
			}
		for(auto &v : {vert, hor}) {
			printf("%d\n", int(v.size()));
			for(pii p : v)
				printf("%d %d\n", p.i + 1, p.j + 1);
		}
	} else puts("No");
}
