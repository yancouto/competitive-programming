#include <bits/stdc++.h>
using namespace std;
#define pb push_back
int ok[2000], p[2000];
vector<int> adj[2000], adj2[2000];
void dfs(int u) {
	ok[u] = 1;
	for(int v : adj[u])
		dfs(v);
}

void dfs2(int u) {
	ok[u] = 1;
	for(int v : adj2[u])
		dfs2(v);
}

int main() {
	int a, b, i, n;
	scanf("%d", &n);
	while(scanf("%d %d", &a, &b)) {
		adj[b].pb(a);
		adj2[a].pb(b);
	}
	scanf("%*s");
	while(scanf("%d", &a) != EOF) {
		dfs(a);
		dfs2(a);
	}
	bool any = false;
	for(i = 1; i <= n; i++)
		if(!ok[i])
			printf("%d ", i), any = true;
	if(!any) puts("0");
	else putchar('\n');
}
