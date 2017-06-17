#include <bits/stdc++.h>
using namespace std;

#define pb push_back
const int N = 312345;
typedef long long ll;

int mx;
vector<int> adj[N];
int seen[N], d[N], low[N], C[N], cn, sn, st[N], dp[N], tempo;
int mq;
void dfs(int u) {
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u])
		if(seen[v])
			low[u] = min(low[u], d[v]);
		else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] == d[u]) {
		int ct = 0, a = -1; cn++;
		while(a != u) {
			a = st[--sn];
			ct++;
			C[a] = cn;
			low[a] = d[a] = INT_MAX;
		}
		int ans = 0;
		for(int i = 0; i < ct; i++) {
			a = st[sn + i];
			for(int v : adj[a])
				if(C[v] != C[a])
					ans = max(ans, dp[v]);
		}
		ans += ct;
		for(int i = 0; i < ct; i++) dp[st[sn + i]] = ans;
		if(ans > mx) mx = ans, mq = 0;
		if(ans == mx) mq += ct;
	}
}

int main() {
	int i, n, m, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
	}
	for(i = 0; i < n; i++)
		if(!seen[i])
			dfs(i);
	printf("%d %d\n", mx, mq);
}
