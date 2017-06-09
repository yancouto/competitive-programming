#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

const int N = 112345;
vector<int> adj[N];
int v[10][1123];
int d[N], low[N], c[N], mrk[N], dp[N][1 << 5], tempo, seen[N], st[N], sn, cn;

void go(int u) {
	low[u] = d[u] = tempo++;
	seen[u] = true;
	st[sn++] = u;
	for(int v : adj[u])
		if(seen[v])
			low[u] = min(low[u], d[v]);
		else {
			go(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] == d[u]) {
		int a = -1, ct = 0; cn++;
		while(a != u) {
			a = st[--sn];
			d[a] = low[a] = INT_MAX;
			c[a] = cn;
			ct++;
		}
		assert(ct <= 5);
		int i, j;
		for(i = 0; i < ct; i++) mrk[st[sn + i]] = i;
		for(j = 0; j < (1 << ct); j++)
			for(i = 0; i < ct; i++) {
				int u = st[sn + i];
				int b = v[ct][j];
				if(!((b >> i) & 1)) { dp[u][b] = dp[u][b | (1 << i)]; continue; }
				dp[u][b] = 1;
				for(int v : adj[u])
					if(c[v] != cn)
						dp[u][b] = max(dp[u][b], dp[v][0] + 1);
					else {
						if(!((b >> mrk[v]) & 1)) {
							dp[u][b] = max(dp[u][b], dp[v][b | (1 << mrk[v])] + 1);
						}
					}
			}
	}
}

int main() {
	int i, j, a, b, n, m;
	for(i = 0; i <= 5; i++) {
		for(j = 0; j < (1 << i); j++)
			v[i][j] = j;
		sort(v[i], v[i] + (1 << i), [](int a, int b) { return __builtin_popcount(a) > __builtin_popcount(b); });
	}
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
	}
	for(i = 0; i < n; i++)
		if(!seen[i])
			go(i);
	int mx = 0;
	for(i = 0; i < n; i++)
		mx = max(mx, dp[i][0]);
	printf("%d\n", mx);
}
