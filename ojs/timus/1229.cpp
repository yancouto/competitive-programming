#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int n, m;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }
const int MAXV = 11009, MAXE = MAXV * 6;
int head[MAXV], to[MAXE], nx[MAXE], cur[MAXV], f[MAXE], c[MAXE], en;
int dist[MAXV];

void add_edge(int u, int v) {
	to[en] = v; nx[en] = head[u]; c[en] = 1; head[u] = en++;
	to[en] = u; nx[en] = head[v]; head[v] = en++;
}

int q[MAXV];
bool bfs(int s, int t) {
	memset(dist, -1, sizeof dist);
	int a = 0, b = 0;
	q[b++] = s; dist[s] = 0;
	while(a != b) {
		int x = q[a++];
		cur[x] = head[x];
		for(int e = head[x]; e != -1; e = nx[e]) {
			if(c[e] - f[e] && dist[to[e]] == -1) {
				dist[to[e]] = dist[x] + 1;
				q[b++] = to[e];
				if(to[e] == t) return true;
			}
		}
	}
	return false;
}

bool dfs(int u, int t) {
	if(u == t) return 1;
	for(int &e = cur[u]; e != -1; e = nx[e]) {
		if(dist[to[e]] == dist[u] + 1 && c[e] - f[e] && dfs(to[e], t)) {
			f[e]++;
			f[e ^ 1]--;
			return 1;
		}
	}
	return 0;
}

int max_flow(int s, int t) {
	int fl = 0;
	while(bfs(s, t))
		while(dfs(s, t))
			fl++;
	return fl;
}

int g[102][102];

int main() {
	int i, j, d;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf("%d", &g[i][j]);
	memset(head, -1, sizeof head);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			int v = i * m + j + 2;
			bool left = !((i + j) & 1);
			if(left) add_edge(0, v);
			else add_edge(v, 1);
			if(!left) continue;
			for(d = 0; d < 4; d++) {
				int ni = i + dx[d], nj = j + dy[d];
				if(!valid(ni, nj) || g[i][j] == g[ni][nj]) continue;
				int w = ni * m + nj + 2;
				add_edge(v, w);
			}
		}
	int f = max_flow(0, 1);
	if(f != m * n / 2) { puts("-1"); return 0; }
	int sz = 0;
	memset(g, -1, sizeof g);
	for(i = 0; i < en; i++) {
		if(::f[i] != 1) continue;
		if(to[i] == 1 || to[i ^ 1] == 0) continue;
		int u = (to[i] - 2) / m, v = (to[i] - 2) % m;
		g[u][v] = ++sz;
		u = (to[i ^ 1] - 2) / m; v = (to[i ^ 1] - 2) % m;
		g[u][v] = sz;
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++)
			printf("%d ", g[i][j]);
		putchar('\n');
	}
}
