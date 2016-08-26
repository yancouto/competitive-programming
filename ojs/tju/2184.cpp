#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 509;
const int M = (502 * 502 + 2 * N) << 1;
int to[M], cp[M], fl[M], en;
vector<int> adj[N];

void reset_all() {
	en = 0;
	for(int i = 0; i < N; i++)
		adj[i].clear();
	memset(fl, 0, sizeof fl);
}

void add_edge(int a, int b) {
	to[en] = b; cp[en] = 1;
	adj[a].pb(en++);
	to[en] = a; cp[en] = 0;
	adj[b].pb(en++);
}

int seen[N], tempo;
int dfs(int u, int t) {
	if(seen[u] == tempo) return 0;
	seen[u] = tempo;
	if(u == t) return 1;
	for(int i = 0; i < adj[u].size(); i++) {
		int e = adj[u][i];
		if(cp[e] - fl[e] && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return 1;
		}
	}
	return 0;
}

int max_flow(int s, int t) {
	int f = 0; tempo++;
	while(dfs(s, t))
		f++, tempo++;
	return f;
}


int a[N];
int main() {
	int n, k, i, j;
	while(true) {
		scanf("%d %d", &n, &k);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		reset_all();
		for(i = 0; i < n; i++)
			if(a[i] & 1)
				for(j = 0; j < n; j++)
					if(!(a[j] & 1) && max(a[j] - a[i], a[i] - a[j]) <= k)
						add_edge(i, j);
		for(i = 0; i < n; i++)
			if(a[i] & 1)
				add_edge(n, i);
			else
				add_edge(i, n + 1);
		printf("%d\n", max_flow(n, n + 1));
	}
}
