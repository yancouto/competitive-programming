#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 209;
const int M = (102 * 102 + 205) << 1;

int fl[M], to[M], en;
vector<int> adj[N];

void reset_all() {
	en = 0;
	for(int i = 0; i < N; i++)
		adj[i].clear();
	memset(fl, 0, sizeof fl);
}

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

int a[N];
int main() {
	int t, i, j, b, n, m, tt = 0;
	scanf("%d", &t);
	while(t--) {
		reset_all();
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%d", &b);
			for(j = 0; j < n; j++)
				if(a[j] == b || (a[j] && !(b % a[j])))
					add_edge(j, i + n);
		}
		for(i = 0; i < n; i++)
			add_edge(n + m, i);
		for(i = 0; i < m; i++)
			add_edge(i + n, n + m + 1);
		printf("Case %d: %d\n", ++tt, max_flow(n + m, n + m + 1));
	}
}
