#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 2e6;
const ll INF = 1e16;

int n;
ll v[N][3];
int t[N];
ll res;
ll memo[N][3];

vector<pii> adj[N];

ll dfs (int u, int v, int k) {
	if (!k)
		k = t[u];
	if (t[u] && k != t[u])
		return INF;
	
	ll & me = memo[u][k];
	if (me != -1)
		return me;
	me = 0;
	for (pii w : adj[u]) {
		if (w.first == v) continue;
		me += min({dfs(w.first, u, k), dfs(w.first, u, 1) + w.second, dfs(w.first, u, 2) + w.second});
	}
	return me;
}

int main () {
	memset(memo, -1, sizeof memo);
	cin >> n;
	for (int i = 0; i < n -1; i++) {
		cin >> v[i][0] >> v[i][1] >> v[i][2];
		v[i][0]--; v[i][1]--;

		adj[v[i][0]].push_back(pii(v[i][1], v[i][2]));
		adj[v[i][1]].push_back(pii(v[i][0], v[i][2])); 
	}
	
	for (int j = 0; j < 2; j++) {
		int m;
		cin >> m;
		int a;
		for (int i = 0; i < m; i++) {
			cin >> a;
			t[a-1] = j+1;
		}
	}

	cout << min(dfs(0, 0, 1), dfs(0,0,2)) << endl;
}
