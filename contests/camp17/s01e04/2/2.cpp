#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1e5+7;
int n, g;
vector<int> adj[N];
int cl[N];

void dfs (int u, int c) {
	if (cl[u] != -1) return;
	cl[u] = c;
	for (int v : adj[u])
		dfs(v, !c);
}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &g);
	memset(cl, -1, sizeof cl);

	g--;

	for (int i = 0; i < n; i++) {
		int q;
		scanf("%d", &q);

		for (int j = 0; j < q; j++) {
			int a;
			scanf("%d", &a);
			a--;
			adj[i].push_back(a);
		}
	}

	dfs(g, 0);

	for (int i = 0; i < n; i++) {
		if (adj[i].size() > 1) continue;
		if (cl[i] == 0)
			printf("CW\n");
		else if (cl[i] == 1)
			printf("CCW\n");
		else
			printf("-\n");
	}
}
