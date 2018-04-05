#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 112345;
const int M = 5003;
vector<int> adj[4*M];
int fst[N], lst[N], a[N];
int st[N], sn, val[N];
ll w[M];
int wn;
int ac[N];
ll res;
ll dp[M][M];
int ct[M][M];

void go () {
	ac[0] = 0; int n = wn;
	if (n == 0) return;
	//cout << "go for";
	for (int i = 0; i < n; i++) { ac[i+1] = ac[i] + w[i]; }
	for (int i = 0; i < n; i++) { dp[i][i] = w[i]; ct[i][i] = i; }
	wn = 0;
	for (int d = 1; d < n; d++) {
		for (int i = 0; i + d < n; i++) {
			int j = i + d;
			dp[i][j] = max(dp[i][j-1],dp[i+1][j]) + ac[j+1] - ac[i];
		}
	}
	//cout << " gets " << dp[0][n-1] << endl;
	res += dp[0][n-1];
}

int main() {
	int i, n, m;
	scanf("%d %d", &n, &m);
	memset(fst, -1, sizeof fst);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if(fst[a[i]] == -1) fst[a[i]] = i;
		lst[a[i]] = i;
	}
	st[sn++] = 0;
	for(i = 0; i < n; i++) {
		if(fst[a[i]] == i) {
			adj[st[sn - 1]].pb(a[i]);
			val[a[i]] = lst[a[i]] - fst[a[i]] + 1;
			st[sn++] = a[i];
		}
		if(i != fst[a[i]] && i != lst[a[i]] && a[i] == st[sn - 1] && (adj[a[i]].empty() || adj[a[i]].back() != -1))
			adj[a[i]].pb(-1);
		if(lst[a[i]] == i) {
			sn--;
		}
	}
	for (int u = 0; u <= m; u++) {
		for (int v : adj[u]) {
			if (v == -1) go();
			else w[wn++] = val[v];
		}
		go();
	}
	//for (int v : adj[u]) if (v != -1) dfs(v);
	printf("%u\n", res);
}
