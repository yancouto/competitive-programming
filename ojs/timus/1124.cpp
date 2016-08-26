#include <bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> adj[502];
int tot;
int dfs(int u) {
	while(!adj[u].empty()) {
		int x = adj[u].back(); adj[u].pop_back();
		dfs(x); tot++;
	}
}

int main() {
	int i, j, n, m, x;
	scanf("%d %d", &m, &n);
	for(i = 0; i < m; i++)
		for(j = 0; j < n; j++) {
			scanf("%d", &x); x--;
			if(x != i) adj[i].pb(x);
		}
	tot = -1;
	for(i = 0; i < m; i++)
		if(adj[i].size())
			dfs(i), tot++;
	if(tot == -1) tot = 0;
	printf("%d\n", tot);
}
