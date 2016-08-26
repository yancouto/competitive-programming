#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 100009;
set<int> s[N];
int ans[N], c[N];
vector<int> adj[N];
void dfs(int u) {
	s[u].insert(c[u]);
	for(int v : adj[u]) {
		dfs(v);
		if(s[u].size() < s[v].size()) s[u].swap(s[v]);
		for(int x : s[v])
			s[u].insert(x);
	}
	ans[u] = s[u].size();
}

int main() {
	int i, n, k, x;
	scanf("%d %d", &n, &k);
	for(i = 1; i < n; i++) {
		scanf("%d", &x); x--;
		adj[x].pb(i);
	}
	for(i = 0; i < n; i++)
		scanf("%d", &c[i]);
	dfs(0);
	ll acc = 0;
	for(i = 0; i < n; i++)
		acc += ans[i];
	printf("%lld\n", acc);
}
