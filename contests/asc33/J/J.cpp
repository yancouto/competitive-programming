#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 2e3+7;
const ll MOD = 1e9;

int n;
vector<int> adj[N];
ll memo[N][N][2];
int hd[N], nx[N], to[N], es;

inline ll mod (ll x) {
	return x%MOD;
}

ll pd (int ed, int k, int b) {
	if (k < 0)
		return 0;
	if (ed == 0)
		return (k == 0);

	ll & me = memo[ed][k][b];
	if (me != -1)
		return me;

	int u = to[ed];
	me = 0;

	for (int i = 0; i <= k; i++) {
		if (b)
			me = mod(me + mod(pd(hd[u], i, 1)*pd(nx[ed], k-i, b)));
		me = mod(me + mod(pd(hd[u], i-1, 1)*pd(nx[ed], k-i, b)));
		me = mod(me + mod(pd(hd[u], i, 0)*pd(nx[ed], k-i, b)));
	}

	//printf("%d %d %d: %lld\n", u+1, k, b, me);
	return me;
}

int dfs (int u, int p) {
	for (int v : adj[u]) {
		if (v == p) continue;
		nx[es] = hd[u]; to[es] = v; hd[u] = es++;
		dfs(v, u);
	}
}

int main () {
	freopen("subtrees.in", "r", stdin);
	freopen("subtrees.out", "w", stdout);
	scanf("%d", &n);
	memset(memo, -1, sizeof memo);
	
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	es = 2;
	dfs(0,0);
	to[1] = 0;
	nx[1] = 0;
	for (int k = 1; k <= n; k++)
		printf("%lld\n", pd(1, k, 0));
}
