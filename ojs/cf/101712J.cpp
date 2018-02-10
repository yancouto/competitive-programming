#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef ll num;
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

int n, m;
inline int vin(int i, int j) { return 2 * (i * m + j); }
inline int vout(int i, int j) { return 2 * (i * m + j) + 1; }

int main() {
	scanf("%d %d", &n, &m);
	int a, b, a2, b2;
	int k, l; scanf("%d %d", &k, &l);
	while(k--) {
		scanf("%d %d", &a, &b);
		g[a - 1][b - 1] = 1;
	}
	while(l--) {
		scanf("%d %d", &a, &b);
		g[a - 1][b - 1] = 2;
	}
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			if(g[i][j] == 1) continue;
			d.add_edge(vin(i, j), vout(i, j), g[i][j]? 1 : INT_MAX);
			if(i < n - 1 && g[i + 1][j] != 1) {
				d.add_edge(vout(i, j), vin(i + 1, j), INT_MAX);
				d.add_edge(vout(i + 1, j), vin(i, j), INT_MAX);
			}
			if(j < m - 1 && g[i][j + 1] != 1) {
				d.add_edge(vout(i, j), vin(i, j + 1), INT_MAX);
				d.add_edge(vout(i, j + 1), vin(i, j), INT_MAX);
			}
		}
	scanf("%d %d %d %d", &a, &b, &a2, &b2); a--; b--; a2--; b2--;
	ll ans = d.max_flow(vout(a, b), vin(a2, b2));
	if(ans < INT_MAX) {
		printf("%d\n", int(ans));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(g[i][j] == 2 && (d.seen[vin(i, j)] == d.tempo) != (d.seen[vout(i, j)] == d.tempo))
					printf("%d %d\n", i + 1, j + 1);
	} else printf("-1\n");
}
