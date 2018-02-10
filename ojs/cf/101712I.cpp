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

char g[100][100];
int want[256];

typedef pair<int, int> pii;
#define i first
#define j second
#define pb push_back

int main() {
	int n = 0, m;
	for(char c : "HONC") want[c] = ++n;
	scanf("%d %d", &n, &m);
	int des = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			scanf(" %c", &g[i][j]);
			des += want[g[i][j]];
		}
	int s = n * m, t = n * m + 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			if(g[i][j] == '.') continue;
			if((i + j) & 1) {
				d.add_edge(s, i * m + j, want[g[i][j]]);
				if(i > 0 && g[i - 1][j] != '.') d.add_edge(i * m + j, (i - 1) * m + j, 1);
				if(i < n - 1 && g[i + 1][j] != '.') d.add_edge(i * m + j, (i + 1) * m + j, 1);
				if(j < m - 1 && g[i][j + 1] != '.') d.add_edge(i * m + j, i * m + (j + 1), 1);
				if(j > 0 && g[i][j - 1] != '.') d.add_edge(i * m + j, i * m + (j - 1), 1);
			} else
				d.add_edge(i * m + j, t, want[g[i][j]]);
		}
	if(des && !(des & 1) && d.max_flow(s, t) == des / 2) {
		puts("Valid");
	} else puts("Invalid");
}
