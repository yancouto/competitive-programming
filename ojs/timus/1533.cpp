#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 209;
const int M = (102 * 102 + 205) << 1;

int fl[M], to[M], en;
vector<int> adj[N];

void add_edge(int a, int b) {
	to[en] = a;	adj[b].pb(en++);
	to[en] = b; adj[a].pb(en++);
}

int seen[N], tempo;
int dfs(int u, int t) {
	if(seen[u] == tempo) return 0;
	seen[u] = tempo;
	if(u == t) return 1;
	for(int e : adj[u])
		if((e & 1) - fl[e] && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return 1;
		}
	return 0;
}

int max_flow(int s, int t) {
	int f = 0; tempo++;
	while(dfs(s, t))
		f++, tempo++;
	return f;
}

int mrk[N], n;
void dfs2(int u) {
	mrk[u] = 1;
	if(seen[u] == tempo) return;
	seen[u] = tempo;
	for(int e : adj[u])
		if((e & 1) - fl[e])
			dfs2(to[e]);
}

int cov[N];
int a[N][N];
int main() {
	int i, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(a[i][k] && a[k][j])
					a[i][j] = 1;
	for(i = 0; i < n; i++)
		add_edge(2 * n, i), add_edge(i + n, 2 * n + 1);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(i != j && a[i][j])
				add_edge(i, j + n);
	max_flow(2 * n, 2 * n + 1);
	tempo++;
	dfs2(2 * n);
	int st[N], sn = 0;
	for(i = 0; i < n; i++)
		if(!mrk[i] || mrk[i + n])
			cov[i] = 1;
	printf("%d\n", n - accumulate(cov, cov + n, 0));
	for(i = 0; i < n; i++)
		if(!cov[i])
			printf("%d ", i + 1);
	putchar('\n');
}
