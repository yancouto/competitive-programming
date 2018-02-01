#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 312345;
vector<int> adj[N];
int sz[N];

int dfs(int u, int p) {
	sz[u] = 1;
	for(int v : adj[u])
		if(v != p)
			sz[u] += dfs(v, u);
	return sz[u];
}

ll acc(int u, int p) {
	ll cur = sz[u] - 1;
	for(int v : adj[u]) {
		if(v == p) continue;
		cur += acc(v, u);
	}
	//printf("acc(%d, %d) = %lld\n", u, p, cur);
	return cur;
}

int freq[N];

int dp[2][N], n;

ll mx;
void go(int u) {
	memset(freq, 0, sizeof freq);
	dfs(u, u);
	ll cur = 0;
	vector<int> all;
	for(int v : adj[u]) {
		cur += acc(v, u);
		//printf("[%d]->%d cur %lld\n", u, v, cur);
		freq[sz[v]]++;
		all.pb(sz[v]);
		//printf("sz %d\n", sz[v]);
	}
	sort(all.begin(), all.end());
	all.resize(unique(all.begin(), all.end()) - all.begin());
	for(int S = 1; S <= n / 2; S++)
		dp[all.size() & 1][S] = -1;
	for(int i = all.size() - 1; i >= 0; i--)
		for(int S = 1; S <= n / 2; S++) {
			if(dp[!(i & 1)][S] != -1)
				dp[i & 1][S] = 0;
			else if(S >= all[i] && dp[i & 1][S - all[i]] != -1 && dp[i & 1][S - all[i]] < freq[all[i]])
				dp[i & 1][S] = dp[i & 1][S - all[i]] + 1;
			else
				dp[i & 1][S] = -1;
			//printf("[%d] dp[%d][%d] = %d\n", all[i], i, S, dp[i & 1][S]);
		}
	for(int S = 0; S <= n / 2; S++)
		if(dp[0][S] != -1 && cur + ll(S) * ll(n - S - 1) + n - 1 > mx) {
			mx = max(mx, cur + ll(S) * ll(n - S - 1) + n - 1);
			//printf("%d * %d + (%d - 1)\n", S, n - S - 1, n);
		}
}

inline void rd(int &x) {
	char c;
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int main() {
	rd(n);
	if(n == 1) { puts("0 0"); return 0; }
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		rd(a); rd(b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(0, 0);
	int u = 0;
	int p = 0;
	while(true) {
		int v = -1;
		for(int _v : adj[u])
			if(_v != p && sz[_v] * 2 > n)
				v = _v;
		assert(v != p);
		//printf("%d->%d\n", u, v);
		if(v != -1 && sz[v] * 2 > n) {
			p = u; u = v;
		} else
			break;
	}
	int v = -1;
	for(int _v : adj[u])
		if(_v != p && sz[_v] * 2 > n)
			v = _v;
	assert(v != p);
	go(u);
	if(v != -1) go(v);
	printf("%d %lld\n", n - 1, mx);
}
