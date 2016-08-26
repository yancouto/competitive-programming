#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000009;
vector<int> adj[MAX];
int deg[MAX], qu[MAX];

int main() {
	int i, n, m, a, b;
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		for(i = 0; i < n; i++) adj[i].clear(), deg[i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			adj[--a].push_back(--b);
			deg[b]++;
		}
		a = b = 0;
		for(i = 0; i < n; i++)
			if(!deg[i])
				qu[b++] = i;
		while(a < b) {
			for(i = 0; i < adj[qu[a]].size(); i++)
				if(!--deg[adj[qu[a]][i]])
					qu[b++] = adj[qu[a]][i];
			a++;
		}
		if(b < n) puts("IMPOSSIBLE");
		else
			for(i = 0; i < n; i++)
				printf("%d\n", qu[i]+1);
	}
}
