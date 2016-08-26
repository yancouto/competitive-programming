#include <bits/stdc++.h>
using namespace std;
#define pb push_back

list<int> l;
vector<int> adj[100009];
typedef list<int>::iterator lit;
void dfs(int u, lit it) {
	lit it2 = it;
	if(it2 != l.end()) ++it2;
	it = l.insert(it2, u);
	while(!adj[u].empty()) {
		int x = adj[u].back(); adj[u].pop_back();
		dfs(x, it);
	}
}

int main() {
	int n, k, u, i, j, v;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &k);
		scanf("%d", &u);
		for(j = 0; j < k; j++) {
			scanf("%d", &v);
			adj[u-1].pb(v-1);
			u = v;
		}
	}
	dfs(0, l.begin());
	printf("%d", l.size() - 1);
	for(int x : l)
		printf(" %d", x + 1);
	putchar('\n');
}
