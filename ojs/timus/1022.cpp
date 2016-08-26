#include <bits/stdc++.h>
using namespace std;
#define pb push_back
vector<int> adj[105];
int f[105], tempo, seen[105];
void dfs(int u) {
	if(seen[u]) return;
	seen[u] = true;
	for(int v : adj[u])
		dfs(v);
	f[tempo++] = u;
}

int main() {
	int i, n, x;
	cin >> n;
	for(i = 0; i < n; i++) {
		while(true) {
			cin >> x;
			if(!x) break;
			adj[i].pb(x - 1);
		}
	}
	for(i = 0; i < n; i++)
		dfs(i);
	cout << f[n-1] + 1;
	for(i = n - 2; i >= 0; i--)
		cout << " " << f[i] + 1;
	cout << '\n';
}
