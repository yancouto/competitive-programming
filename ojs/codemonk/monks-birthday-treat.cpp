#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 1009;
int n, d;
vector<int> adj[MAX];
int seen[MAX], tempo;

int dfs(int u) {
	if(seen[u] == tempo) return 0;
	seen[u] = tempo;
	int num = 1;
	for(int v : adj[u])
		num += dfs(v);
	return num;
}

int main() {
	int i, a, b;
	scanf("%d %d", &n, &d);
	for(i = 0; i < d; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].push_back(b);
	}
	int mx = 10000;
	for(i = 0; i < n; i++) {
		tempo++;
		mx = min(mx, dfs(i));
	}
	printf("%d\n", mx);
	return 0;
}