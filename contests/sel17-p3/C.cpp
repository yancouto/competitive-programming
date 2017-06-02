#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
const int N = 1123456;
vector<int> adj[N];
int seen[N], a[N];

int dfs(int u) {
	seen[u] = 1;
	int mx = u;
	for(int v : adj[u])
		if(seen[v] == 0)
			mx = max(mx, dfs(v));
	return mx;
}

int main() {
	int i, n;
	while(scanf("%d", &n) != EOF && n) {
		map<int, vector<int>> mp;
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]), adj[i].clear(), seen[i] = 0;
		for(i = n - 1; i >= 0; i--) {
			for(int j : mp[-a[i] - i])
				adj[i].pb(j), adj[j].pb(i);
			mp[a[i] - i].pb(i);
		}
		printf("%d\n", dfs(0));
	}
}
